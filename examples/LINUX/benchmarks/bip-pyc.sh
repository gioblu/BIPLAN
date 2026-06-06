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

iterations=1
tests_length=${#tests[@]}
total_bip=0
total_pyc=0

if ! command -v bcc >/dev/null 2>&1 ; then
    echo "bcc not found, please install it!"
    exit 1
fi

if ! command -v python3 >/dev/null 2>&1 ; then
    echo "python3 not found, please install it!"
    exit 1
fi

# Cross-platform file size getter (Linux & macOS)
get_file_size() {
    if stat --version 2>/dev/null | grep -q GNU; then
        stat -c%s "$1"
    else
        stat -f%z "$1"
    fi
}

# Fixed precision sizing layout
format_size() {
    local size=$1
    if [ "$size" -lt 1024 ]; then
        printf "%-10s" "${size}B"
    elif [ "$size" -lt 1048576 ]; then
        local kb
        kb=$(awk "BEGIN {printf \"%.2f\", $size/1024}")
        printf "%-10s" "${kb}KB"
    else
        local mb
        mb=$(awk "BEGIN {printf \"%.2f\", $size/1048576}")
        printf "%-10s" "${mb}MB"
    fi
}

echo " _________________________________________________________________"
echo "|                                      |             |            |"
echo "| Benchmark: Bytecode size             |  bip size   |  pyc size  |"
echo "|______________________________________|_____________|____________|"
echo "|                                      |             |            |"

for ((i=1; i<=tests_length; i++)); do
    test_name="${tests[$i - 1]}"
    desc="${descs[$i - 1]}"
    biplan_src="$SCRIPT_DIR/programs/${test_name}.biplan"
    bip_out="/tmp/${test_name}.bip"
    py_src="$SCRIPT_DIR/programs/${test_name}.py"
    pyc_out="/tmp/${test_name}.pyc"

    bip_size=0
    pyc_size=0

    # Compile Biplan
    for ((it=0; it<iterations; it++)); do
        bcc "$biplan_src" "$bip_out" > /dev/null 2>&1
    done
    if [ -f "$bip_out" ]; then
        bip_size=$(get_file_size "$bip_out")
    fi

    # Compile Python (Using optimize=2 to strip docstrings/asserts cleanly)
    for ((it=0; it<iterations; it++)); do
        python3 -c "import py_compile, sys; py_compile.compile(sys.argv[1], sys.argv[2], doraise=True, optimize=2)" "$py_src" "$pyc_out" > /dev/null 2>&1
    done
    if [ -f "$pyc_out" ]; then
        pyc_size=$(get_file_size "$pyc_out")
    fi

    total_bip=$((total_bip + bip_size))
    total_pyc=$((total_pyc + pyc_size))

    bip_text=$(format_size "$bip_size")
    pyc_text=$(format_size "$pyc_size")

    space=""
    [ $i -lt 10 ] && space=" "
    echo -e "| ${space}$i. ${desc} | ${bip_text}  | ${pyc_text} |"

    # Clean up at the very end of the step
    rm -f "$bip_out" "$pyc_out"
done

echo "|______________________________________|_____________|____________|"

bip_total_text=$(format_size $total_bip)
pyc_total_text=$(format_size $total_pyc)

echo -e "| Total footprint                      | ${bip_total_text}  | ${pyc_total_text} |"
echo "|______________________________________|_____________|____________|"

if [ "$total_bip" -eq 0 ] || [ "$total_pyc" -eq 0 ]; then
    echo -e "\nError: One of the language compilers failed to yield target files.\n"
elif [ "$total_bip" -lt "$total_pyc" ]; then
    ratio=$(awk "BEGIN {printf \"%.2f\", $total_pyc/$total_bip}")
    echo -e "\nFootprint: bip is $ratio times smaller than pyc.\n"
else
    ratio=$(awk "BEGIN {printf \"%.2f\", $total_bip/$total_pyc}")
    echo -e "\nFootprint: pyc is $ratio times smaller than bip.\n"
fi
