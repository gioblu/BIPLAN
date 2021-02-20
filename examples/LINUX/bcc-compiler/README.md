### bcc (BIP Compiler Collection)
The `bcc.cpp` file is a complete and ready to use compiler. It is able to compile BIPLAN source into BIP machine language.

#### How to build it
1. Open the console
2. Locate the `BIPLAN/examples/LINUX/bcc-compiler` directory
3. Digit `g++ -DLINUX -I. -I ../../../src -std=gnu++11 bcc.cpp -o bcc -lpthread -lcrypt -lm -lrtD`

#### How to use it
The `bcc` executable can be used to compile BIPLAN into BIP machine language, in this example's directory you find [`fib.bpl`](fib.bpl) that contains a BIPLAN program able to compute the 40th number of the fibonacci series. This is compiled into BIP machine language in [`fib.bip`](../biplan-interpreter/fib.bip).

1. Open the console
2. Locate the `BIPLAN/examples/LINUX/bcc-compiler` directory
3. Digit `./bcc fib.bpl ../biplan-interpreter/fib.bip`

Expected output:
```
BCC (BIP Compiler Collection) Giovanni Blu Mitolo 2021
Source: fib.bpl
Target: ../biplan-interpreter/fib.bip
Source length: 238B, BIP length: 64B, reduction: 73.109245%
Compilation time: 251 microseconds
```

You can now give a try to the [biplan-interpreter](../biplan-interpreter).
