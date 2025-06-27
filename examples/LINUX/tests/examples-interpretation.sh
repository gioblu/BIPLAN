#!/bin/bash

# All examples to be tested in this run
declare -a tests=(
	"bcc-compiler/fib.bip"
	"bcc-compiler/fib_recursive.bip"
	"read-file/read-file.bip"
	"date-epoch/date-epoch.bip"
	"mem-test/mem-test.bip"
)

declare -a results=(
	"102334155"
	"55"
	'}%oY"read-file.bip",0l}$}&oX}%?}&T-1pb}&j}$FoZ}%x'
	"Epoch: 1665434120 Date: 10/10/2022 20:35:20"
	"Simplicity is best."
)

echo " "
echo "biplan interpretation test run: examples/LINUX/ "
echo " "

length=${#tests[@]}

# Try to interpret all files in the list above and print the result of the test
for ((i=1; i<${length} + 1; i++ ));
do
	result=$(biplan -i "../${tests[$i - 1]}" 2>&1)
	code=$?
	expected=${results[$i - 1]}

	echo "$i. Testing interpretation of ../${tests[$i - 1]}"

	if [[ "$result" == "$expected" ]]; then
	  echo -e "Result: \033[32mpassed \033[m- Exit code: $code"
	else
	 echo "Expected: $expected, Result: $result"
	 echo -e "Result: \033[31mfailed \033[m- Exit code: $code"
	fi

	echo " "
done
