### bcc (BIP Compiler Collection)
The `bcc.cpp` file is a complete and ready to use compiler. It is able to compile BIPLAN source into BIP machine language.

#### How to build it
1. Open the console
2. Locate the `BIPLAN/examples/LINUX/bcc-compiler` directory
3. Digit `sudo make install`

#### How to use it
The `bcc` executable is copied in `usr/bin` to be reachable everywhere within your system. You can use `bcc` to compile a BIPLAN program into BIP machine language, in this example's directory you find [`fib.bpl`](fib.bpl) that contains a BIPLAN program able to compute the 40th number of the fibonacci series 100.000 times. This is compiled into BIP machine language in [`fib.bip`](../biplan-interpreter/fib.bip).

1. Open the console
2. Locate the `BIPLAN/examples/LINUX/bcc-compiler` directory
3. Digit `bcc fib.bpl ../biplan-interpreter/fib.bip`

Expected output:
```
BCC (BIP Compiler Collection) Giovanni Blu Mitolo 2021
Source: fib.bpl
Target: ../biplane-interpreter/fib.bip
Source length: 413B, BIP length: 63B, reduction: 84.745758%
Compilation time: 480 microseconds
```

You can now give a try to the [biplan-interpreter](../biplan-interpreter) and use it to run [`fib.bip`](../biplan-interpreter/fib.bip).
