### bcc (BIP Compiler Collection)
The `bcc.cpp` file is a complete and ready to use compiler. It is able to compile BIPLAN source into BIP machine language.

#### How to build it
1. Open the console
2. Locate the `BIPLAN/examples/LINUX/bcc-compiler` directory
3. You can choose to build the compact compiler using `sudo make compact` which is optimized for size (~22KB), or build the executable optimized for performance using `sudo make fast`, the resulting binary will be larger in size (~34KB) but around twice as fast if compared to the `compact` target.
4. Digit `sudo make install`

#### The bcc executable
With `bcc` you can compile a BIPLAN program into BIP machine language. 

```
bcc [BIPLAN input file] [BIP output file]
```
The `bcc` executable is copied in `usr/bin` to be reachable everywhere within your system; it receives 2 parameters, the BIPLAN input file and the BIP output file. If the 2 files are not in the same directory your terminal is in you will need to specify the path to reach them.

#### How to use it
 In this directory you find [`fib.biplan`](fib.biplan), it contains a BIPLAN program able to compute the 40th number of the fibonacci series 100.000 times. Let's compile it into BIP machine language in [`fib.bip`](../biplan-interpreter/fib.bip). To do so:

1. Open the console
2. Locate the `BIPLAN/examples/LINUX/bcc-compiler` directory
3. Digit `bcc fib.biplan ../biplan-interpreter/fib.bip`

Expected output:
```
BCC (BIP Compiler Collection) Giovanni Blu Mitolo 2021 
Source: fib.biplan 
Target: ../biplan-interpreter/fib.bip 
Source length: 410B, BIP length: 57B, reduction: 86.097565% 
Compilation time: 1241 microseconds 

```

The compiler should have created `fib.bip` inside the `biplan-interpreter` directory.

You can now give a try to the [biplan-interpreter](../biplan-interpreter) and use it to run [`fib.bip`](../biplan-interpreter/fib.bip).
