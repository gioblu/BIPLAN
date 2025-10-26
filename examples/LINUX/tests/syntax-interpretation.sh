#!/bin/bash

SCRIPT_PATH=$(realpath "$0")
SCRIPT_DIR=$(dirname "$SCRIPT_PATH")

# All examples to be tested in this run
declare -a tests=(
	"char-const-in-string.bip"
	"function-in-string.bip"
	"if-in-string.bip"
	"round-parent-in-string.bip"
	"square-parent-in-string.bip"
	"for.bip"
	"function.bip"
	"while.bip"
	"math.bip"
)

declare -a results=(
	"'H"
	"sum(1, 1)"
	'if true stop end'
	"(a + b"
	"mem[12"
	"0123451054321"
	"2"
	"9876543210"
	"12 102334155 10 0 9 144 1 -1 0 20 90 10 100 100 0 0"
)

echo " "
echo "biplan syntax interpretation test run: examples/LINUX/ "
echo " "

length=${#tests[@]}
fail=0

# Try to interpret all files in the list above and print the result of the test
for ((i=1; i<${length} + 1; i++ ));
do
	space=$([ $i -lt 10 ] && echo " " || echo "")
	result=$(biplan -i "$SCRIPT_DIR/../tests/syntax/${tests[$i - 1]}" 2>&1)
	code=$?
	expected=${results[$i - 1]}
	
	[ "$result" == "$expected" ] && 
		echo -e "| $i.$space | Result: \033[32mpassed \033[m| Exit code: $code | ../${tests[$i - 1]}" || 
		echo -e "| $i.$space | Result: \033[31mfailed \033[m| Exit code: $code | ../${tests[$i - 1]}"

	[ $code != 1 ] && ((fail++))
done

plural=""
[ $fail -gt 1 ] && plural="s" || plural=""

[ $fail -lt 1 ] && echo -e "\nTest result:\033[32m passed\033[m\n"  || 
echo -e "\nTest result:\033[31m $fail test$plural failed\033[m\n"
