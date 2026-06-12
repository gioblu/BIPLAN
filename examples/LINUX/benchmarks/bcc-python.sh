#!/bin/bash

SCRIPT_PATH=$(realpath "$0")
SCRIPT_DIR=$(dirname "$SCRIPT_PATH")

declare -a tests=(
    "hello-world" "for-loop" "for-if" "print" "while"
    "increment-break" "millis" "size" "numeric" "math"
    "bitwise" "bitshift" "function-call" "function-call-function"
    "function-leap-year" "write-string" "read-string" "prime"
    "fib" "factorial" "pipes"
)

declare -a descs=(
    "Hello world!                    "
    "For loop incrementing global    "
    "For loop nested if              "
    "For prints index                "
    "While loop incrementing global  "
    "While increment and break       "
    "Read elapsed time cyclically    "
    "Get size of string              "
    "Check if numeric                "
    "Basic math operations           "
    "Bitwise operations              "
    "Bitshift operations             "
    "Function call within condition  "
    "Function calls another function "
    "Function leap year              "
    "Write character of string       "
    "Read character of string        "
    "For computing prime numbers     "
    "Non-recursive fibonacci         "
    "Factorial 20                    "
    "Pipes                           "
)

iterations=2
tests_length=${#tests[@]}
total_bcc=0
total_py=0

if ! command -v biplan >/dev/null 2>&1 ; then
    echo "biplan not found, please install bcc!"
    exit 1
fi

if ! command -v python3 >/dev/null 2>&1 ; then
    echo "python3 not found, please install python3!"
    exit 1
fi

# Cross-platform microsecond timestamp generator
get_time_us() {
    python3 -c 'import time; print(int(time.time() * 1000000))'
}

format_ms() {
    local us=$1
    local ms
    ms=$(awk "BEGIN {printf \"%.2fms\", $us/1000}")
    printf "%-9s" "$ms"
}

echo " ___________________________________________________________________"
echo "|                                       |             |             |"
echo "| Benchmark: Compilation time           |     bcc     |   python3   |"
echo "|_______________________________________|_____________|_____________|"
echo "|                                       |             |             |"

# Set up global scratch environment safely outside the execution loop
tmp_pycache=$(mktemp -d)

for ((i=1; i<=tests_length; i++)); do
    biplan_test="${tests[$i - 1]}"
    biplan_src="$SCRIPT_DIR/programs/${biplan_test}.biplan"
    biplan_out="/tmp/${biplan_test}.bip"
    py_src="$SCRIPT_DIR/programs/${biplan_test}.py"

    # Profile bcc
    start_bcc=$(get_time_us)
    for ((it=0; it<iterations; it++)); do
        biplan -c "$biplan_src" "$biplan_out" > /dev/null 2>&1
    done
    end_bcc=$(get_time_us)
    duration_bcc=$((end_bcc - start_bcc))

    # Profile Python (I/O structures isolated)
    start_py=$(get_time_us)
    for ((it=0; it<iterations; it++)); do
        PYTHONPYCACHEPREFIX="$tmp_pycache" python3 -m py_compile "$py_src" > /dev/null 2>&1
    done
    end_py=$(get_time_us)
    duration_py=$((end_py - start_py))

    total_bcc=$((total_bcc + duration_bcc))
    total_py=$((total_py + duration_py))

    bcc_ms=$(format_ms "$duration_bcc")
    py_ms=$(format_ms "$duration_py")

    space=""
    [ $i -lt 10 ] && space=" "
    echo -e "| ${space}$i. ${descs[$i - 1]}  | $bcc_ms   | $py_ms   |"

    rm -f "$biplan_out"
done

# Clean up temporary scratch disk space
rm -rf "$tmp_pycache"

echo "|_______________________________________|_____________|_____________|"

color_bcc="\033[31m"
color_py="\033[31m"
[ $total_bcc -lt $total_py ] && color_bcc="\033[32m" || color_py="\033[32m"

bcc_total_ms=$(awk "BEGIN {printf \"%.2f\", $total_bcc/1000}")
py_total_ms=$(awk "BEGIN {printf \"%.2f\", $total_py/1000}")

echo -e "                                         $color_bcc ${bcc_total_ms}ms\033[m    $color_py ${py_total_ms}ms\033[m"

if [ "$total_bcc" -eq 0 ] || [ "$total_py" -eq 0 ]; then
    echo -e "\nError: Calculation failed due to missing execution durations.\n"
elif [ $total_bcc -lt $total_py ]; then
    ratio=$(awk "BEGIN {printf \"%.2f\", $total_py/$total_bcc}")
    echo -e "\nbcc compiles $ratio times faster than python3.\n"
else
    ratio=$(awk "BEGIN {printf \"%.2f\", $total_bcc/$total_py}")
    echo -e "\npython3 compiles $ratio times faster than bcc.\n"
fi
