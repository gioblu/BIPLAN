### biplan interpreter
The `biplan.cpp` file is a complete and ready to use interpreter. It is able to execute BIP machine language.

#### How to build it
1. Open the console
2. Locate the `BIPLAN/examples/LINUX/biplan-interpreter` directory
3. Digit `g++ -DLINUX -I. -I ../../../src -std=gnu++11 biplan.cpp -o biplan -lpthread -lcrypt -lm -lrtD`

#### How to use it
The `biplan` executable can be used to execute BIP machine language, in this example's directory is located a `test.bip` file that contains BIP machine code. We can use the `biplan` executable to run it.

1. Locate the `BIPLAN/examples/LINUX/biplan-interpreter` directory
2. Digit `./biplan test.bip`

Expected output:
```
BIPLAN interpreter - Giovanni Blu Mitolo 2021
Source: test.bip
Source length: 80B

Interpreter output:

BIPLAN 10000 increments benchmark
2 milliseconds

Execution duration: 1774 microseconds
```
