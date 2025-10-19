#!/bin/bash

# All examples to be tested in this run
declare -a tests=(
	"bcc-compiler/fib.bip"
	"bcc-compiler/fib_recursive.bip"
	"read-file/read-file.bip"
	"date-epoch/date-epoch.bip"
	"mem-test/mem-test.bip"
	"strings/strings.bip"
)

declare -a results=(
	"102334155"
	"55"
	'}%oY"read-file.bip",0l}$}&oX}%?}&T-1pb}&j}$FoZ}%x'
	"Epoch: 1665434120 Date: 10/10/2022 20:35:20"
	"Simplicity is best."
	"Printing entire string: This is a test string
Printing string character by character: This is a test string
Printing string from \"a\" onwards: a test string
"
)

echo " "
echo "biplan examples interpretation test run: examples/LINUX/ "
echo " "

length=${#tests[@]}
fail=0

# Try to interpret all files in the list above and print the result of the test
for ((i=1; i<${length} + 1; i++ ));
do
	space=$([ $i -lt 10 ] && echo " " || echo "")
	result=$(biplan -i "../${tests[$i - 1]}" 2>&1)
	code=$?
	expected=${results[$i - 1]}
	
	[ "$result" == "$expected" ] && 
		echo -e "| $i.$space | Result: \033[32mpassed \033[m| Exit code: $code | ../${tests[$i - 1]}" ||
		echo -e "| $i.$space | Result: \033[31mfailed \033[m| Exit code: $code | ../${tests[$i - 1]}"
	[ $code != 1 ] && ((fail++))
done

plural=""
[ $fail -gt 1 ] && plural="s" || plural="" 

[ $fail -lt 1 ] && echo -e "\nTest result:\033[32m passed\033[m"  || 
echo -e "\nTest result:\033[31m $fail test$plural failed\033[m"
