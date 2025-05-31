#!/bin/bash

# All examples to be tested in this run
declare -a tests=(
	"bcc-compiler/fib.bip"
	"read-file/read-file.bip"
	"date-epoch/date-epoch.bip"
)

declare -a results=(
	"102334155"
	'}%oY"read-file.bip",0l}$}&oX}%?}&T-1pb}&j}$FoZ}%x'
	"Epoch: 1665434120 Date: 10/10/2022 20:35:20"
)

echo " "
echo "biplan interpretation test run: examples/LINUX/ "
echo "This run compiles examples that are expected to compile."
echo " "

length=${#tests[@]}

# Try to compile all files in the list above and print the result of the test
for ((i=1; i<${length} + 1; i++ ));
do
	result=$(biplan -i "../${tests[$i - 1]}" 2>&1)
	code=$?
	expected=${results[$i - 1]}

	echo "$i. Testing interpretation of ../${tests[$i - 1]}"

	if [[ "$result" == "$expected" ]]; then
	  echo -e "Exit code: $code. Test result: \033[32m passed. \033[m"
	else
	 echo "Expected: $expected, Result: $result"
	 echo -e "Exit code: $code. Test result: \033[31m failed. \033[m"
	fi

	echo " "
done
