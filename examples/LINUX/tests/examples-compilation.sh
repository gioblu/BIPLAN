#!/bin/bash

# All examples to be tested in this run
declare -a tests=(
	"bcc-compiler/fib" 
	"x-drawer/x-drawer" 
	"mem-test/mem-test" 
	"read-file/read-file" 
	"notes/notes" 
	"graphics/graphics" 
	"strings/strings" 
	"draw-line/draw-line" 
	"date-epoch/date-epoch"
	"math/math" 
	"calc/calc"
	"../OSX/matrix/matrix"
	"../OSX/ASCII-table/ASCII-table"
)

# All expected errors from the compiler
declare -a errors=(
	"compilation failed"
	"unable to open source file"
	"the source file is too big"
	"unable to read source file"
)

info="bcc compilation test run: examples/LINUX/ "
tests_length=${#tests[@]}
errors_length=${#errors[@]}
fail=0

echo -e "\n$info\n"

# Try to compile all files in the list above and print the result of the test
for ((i=1; i<${tests_length} + 1; i++ ));
do
	space=$([ $i -lt 10 ] && echo " " || echo "")
	result=$(bcc "../${tests[$i - 1]}.biplan" "../${tests[$i - 1]}.bip")
	code=$?
	error="unknown"
	[ $code -lt $errors_length ] && error=${errors[$(($code - 1))]}
	[ $code -eq 1 ] && ((fail++))
	[ $code -eq 0 ] && 
		echo -e "| $i.$space | Result: \033[32mpassed \033[m| Exit code: $code | ../${tests[$i - 1]}.biplan" || 
	    echo -e "| $i.$space | Result: \033[31mfailed \033[m| Exit code: $code | ../${tests[$i - 1]}.biplan ($error)"
done

plural=""
[ $fail -gt 1 ] && plural="s" || plural="" 
[ $fail -lt 1 ] && echo -e "\nTest result:\033[32m passed\033[m"  || 
				   echo -e "\nTest result:\033[31m $fail test$plural failed\033[m"