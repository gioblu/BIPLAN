#!/bin/bash

# All examples to be tested in this run
declare -a tests=(
	"bcc-compiler/fib" 
	"x-drawer/x-drawer" 
	"mem-test/mem-test" 
	"read-file/read-file" 
	"notes/notes" 
	"graphics/graphics" 
	"draw-line/draw-line" 
	"date-epoch/date-epoch"
	"math/math" 
	"calc/calc"
	"../OSX/matrix/matrix"
	"../OSX/ASCII-table/ASCII-table"
)

echo " "
echo "bcc compilation test run: examples/LINUX/ "
echo " "

length=${#tests[@]}

# Try to compile all files in the list above and print the result of the test
for ((i=1; i<${length} + 1; i++ ));
do
	result=$(bcc "../${tests[$i - 1]}.bpl" test.bip)
	code=$?
	echo "$i. Testing compilation of ../${tests[$i - 1]}.bpl"
	[ $code -eq 1 ] && echo -e "Result: \033[32mpassed \033[m- Exit code: $code" || 
	                   echo -e "Result: \033[31mfailed \033[m- Exit code: $code"
	echo " "
done
