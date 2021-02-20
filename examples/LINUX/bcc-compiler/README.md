### bcc (BIP Compiler Collection)
The `bcc.cpp` file is a complete and ready to use compiler. It is able to compile BIPLAN source into BIP virtual-machine language.

#### How to build it
1. Open the console
2. Locate the `BIPLAN/examples/LINUX/bcc-compiler` directory
3. Digit `g++ -DLINUX -I. -I ../../../src -std=gnu++11 bcc.cpp -o bcc -lpthread -lcrypt -lm -lrtD`

#### How to use it
The `bcc` executable can be used to compile BIPLAN into BIP, in this example's directory is located a `test.txt` file that contains a BIPLAN program; this is compiled into BIP in `test.bip`.
1. Locate the `BIPLAN/examples/LINUX/bcc-compiler` directory
2. Digit `./bcc fib.bpl ../biplan-interpreter/fib.bip`
3. Try the [biplan-interpreter](../biplan-interpreter)

Expected output:
```
BCC (BIP Compiler Collection) Giovanni Blu Mitolo 2021
Source: fib.bpl
Target: ../biplan-interpreter/fib.bip
Source length: 238B, BIP length: 64B, reduction: 73.109245%
Compilation time: 251 microseconds
```
