#!/bin/bash

SCRIPT_PATH=$(realpath "$0")
SCRIPT_DIR=$(dirname "$SCRIPT_PATH")

# All examples to be tested in this run
declare -a tests=(
	"char-const-missing-separator" 
	"for-missing-next" 
	"function-missing-return" 
	"function-too-long" 
	"if-missing-end" 
	"round-parent-missing" 
	"square-parent-missing" 
	"string-missing-separator" 
	"variable-too-long"
	"wrong-include-path" 
)

# All expected errors from the compiler
declare -a errors=(
	"compilation failed"
	"unable to open source file"
	"the source file is too big"
	"unable to read source file"
)

tests_length=${#tests[@]}
errors_length=${#errors[@]}
error="unknown"
fail=0
info="bcc error compilation test run: examples/LINUX/tests/errors "

echo -e "\n$info\n"

# Try to compile all files in the list above and print the result of the test
for ((i=1; i<${tests_length} + 1; i++ ));
do
	space=$([ $i -lt 10 ] && echo " " || echo "")
	result=$(bcc "$SCRIPT_DIR/errors/${tests[$i - 1]}.biplan" "$SCRIPT_DIR/errors/test.bip")
	code=$?
	[ $code -lt $errors_length ] && error=${errors[$(($code - 1))]}
	[ $code -eq 1 ] && 
		echo -e "| $i.$space | Result: \033[32mpassed \033[m| Exit code: $code | ${tests[$i - 1]}.biplan" || 
	    echo -e "| $i.$space | Result: \033[31mfailed \033[m| Exit code: $code | ${tests[$i - 1]}.biplan ($error)"
	[ $code -eq 0 ] && ((fail++))
done

plural=""
[ $fail -gt 1 ] && plural="s" || plural="" 
[ $fail -lt 1 ] && echo -e "\nTest result:\033[32m passed\033[m\n"  || 
				   echo -e "\nTest result:\033[31m $fail test$plural failed\033[m\n"