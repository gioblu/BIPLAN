#!/bin/bash

SCRIPT_PATH=$(realpath "$0")
SCRIPT_DIR=$(dirname "$SCRIPT_PATH")

declare -a tests=(
    "hello-world"
	"for-loop"
    "for-if"
    "print"
    "while"
    "increment-break"
    "millis"
    "size"
    "numeric"
    "math"
    "bitwise"
    "bitshift"
    "function-call"
    "function-call-function"
    "function-leap-year"
    "write-string"
    "read-string"
    "prime"
	"fib" 
    "factorial"
    #"date-epoch"
    #"bubble-sort"
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
    #"Date from Epoch                 "
    #"Bubble sort array               "
)

declare -a iters=(
    "100000"
    "100000"
    "100000"
    "100000"
    "10000 "
    "10000 "
    "100000"
    "100000"
    "100000"
    "100000"
    "100000"
    "100000"
    "100000"
    "100000"
    "100000"
    "100000"
    "100000"
    "100000"
    "100000"
    "100000"
)

iterations=1
tests_length=${#tests[@]}
total_bip=0
total_py=0

if ! command -v python3 >/dev/null 2>&1 ; then
    echo "python3 not found, the benchmark cannot be run without it, please install it!"
    exit 1
fi

echo " ________________________________________________________________________________"
echo "|                                       |             |             |            |"
echo "| Benchmark                             | biplan      | python3     | Iterations |"
echo "|_______________________________________|_____________|_____________|____________|"
echo "|                                       |             |             |            |"
for ((i=1; i<${tests_length} + 1; i++ ));
do
    start_bip=$(date +%s%6N)
    bcc "$SCRIPT_DIR/programs/${tests[$i - 1]}.biplan" "$SCRIPT_DIR/programs/${tests[$i - 1]}.bip"  > /dev/null 2>&1
    for ((it=0; it<${iterations}; it++ ));
    do
        biplan -i "$SCRIPT_DIR/programs/${tests[$i - 1]}.bip"  > /dev/null 2>&1
    done
    end_bip=$(date +%s%6N)
    duration_bip=$((end_bip - start_bip))

    start_py=$(date +%s%6N)
    for ((it=0; it<${iterations}; it++ ));
    do
        python3 "$SCRIPT_DIR/programs/${tests[$i - 1]}.py"  > /dev/null 2>&1
    done
    end_py=$(date +%s%6N)

    duration_py=$((end_py - start_py))

    
    total_bip=$((total_bip + duration_bip))
    total_py=$((total_py + duration_py))

    format_ms() {
        ms=$(( $1 / 1000 ))
        frac=$(( ($1 % 1000) / 10 ))
        num_str=$(printf "%-9s" "$(printf "%d.%02dms" "$ms" "$frac")")
        printf "$num_str"
    }

    bip_ms=$(format_ms $duration_bip)
    py_ms=$(format_ms $duration_py)
    space=""
    [ $i -lt 10 ] && space=" " 
    echo -e "| ${space}$i. ${descs[$i - 1]}  | ${color_bip}$bip_ms ${color_py}  | $py_ms   | ${iters[$i - 1]}     |"
    result=$(rm "$SCRIPT_DIR/programs/${tests[$i - 1]}.bip")
done

echo "|_______________________________________|_____________|_____________|____________|"

color_bip="\033[31m"
color_py="\033[31m"
[ $total_bip -lt $total_py ] && color_bip="\033[32m" || color_py="\033[32m" 

bip_total_ms=$(printf "%.2f" "$(echo "scale=3; $total_bip/1000" | bc)")
py_total_ms=$(printf "%.2f" "$(echo "scale=3; $total_py/1000" | bc)")

echo -e "                                         $color_bip ${bip_total_ms}ms\033[m    $color_py ${py_total_ms}ms\033[m"

if [ $total_bip -lt $total_py ]; then
    ratio=$(echo "scale=2; $total_py/$total_bip" | bc)
    echo -e "\nbiplan is $ratio times faster than python3.\n"
else
    ratio=$(echo "scale=2; $total_bip/$total_py" | bc)
    echo -e "\npython3 is $ratio times faster than biplan.\n"
fi