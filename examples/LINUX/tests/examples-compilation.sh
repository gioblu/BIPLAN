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
	"calc/calc"
	"../OSX/matrix/matrix"
	"../OSX/ASCII-table/ASCII-table"
)

echo " "
echo "bcc compilation test run: examples/LINUX/ "
echo "This run compiles examples that are expected to compile."
echo " "

length=${#tests[@]}

# Try to compile all files in the list above and print the result of the test
for ((i=1; i<${length} + 1; i++ ));
do
	result=$(bcc "../${tests[$i - 1]}.bpl" ../bcc-compiler/fib.bip)
	code=$?
	echo "$i. Testing compilation of ../${tests[$i - 1]}.bpl"
	[ $code -eq 1 ] && echo -e "Exit code: $code. Test result: \033[32m passed. \033[m" || 
	                   echo -e "Exit code: $code. Test result: \033[31m failed. \033[m"
	echo " "
done
