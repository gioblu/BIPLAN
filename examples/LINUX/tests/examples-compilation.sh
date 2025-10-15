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

echo " "
echo "bcc compilation test run: examples/LINUX/ "
echo " "

tests_length=${#tests[@]}
errors_length=${#errors[@]}

# Try to compile all files in the list above and print the result of the test
for ((i=1; i<${tests_length} + 1; i++ ));
do
	result=$(bcc "../${tests[$i - 1]}.biplan" test.bip)
	code=$?
	error="unknown"
	[ $code -lt $errors_length ] && error=${errors[$(($code - 1))]}
	echo "$i. Testing compilation of ../${tests[$i - 1]}.biplan"
	[ $code -eq 0 ] && echo -e "Result: \033[32mpassed \033[m- Exit code: $code" || 
	                   echo -e "Result: \033[31mfailed \033[m- Exit code: $code ($error)"
	echo " "
done
