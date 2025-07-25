### biplan interpreter
The `biplan.cpp` file is a complete and ready to use BIP machine language interpreter.

#### How to build it
1. Open the console
2. Locate the `BIPLAN/examples/LINUX/biplan-interpreter` directory
3. You can choose to build the compact interpreter using `sudo make compact` which is optimized for size (~26KB), or build the executable optimized for performance using `sudo make fast`, the resulting binary will be larger in size (~82KB) but around twice as fast if compared to the `compact` target. 
4. Digit `sudo make install`
5. Digit `sudo make clean` to remove the executable from the `usr/local/bin` directory

#### How to use it
The `bcc` executable is copied in `usr/local/bin` to be reachable everywhere within your system. You can use it to interpret BIP machine language. In this directory you find [`fib.bip`](fib.bip), this file contains a program in BIP machine language that computes the 40th number of the Fibonacci sequence 100.000 times (the human-readable version is [fib.biplan](../bcc-compiler/fib.biplan)). You can use the `biplan` executable to interpret [`fib.bip`](fib.bip) or any other BIPLAN program. To do so:

1. Open the console
2. Locate the `BIPLAN/examples/LINUX/biplan-interpreter` directory
3. Digit `biplan -i fib.bip -d`

Expected output:
```
BIPLAN interpreter - Giovanni Blu Mitolo 2025 
Source: fib.bip
Source length: 57B 

Interpreter output: 

102334155

Execution duration: 648949 microseconds 
```

You can now write a BIPLAN program, play with the [bcc-compiler](../bcc-compiler) and use the `biplan` executable to interpret it. 

`biplan` supports additional arguments:
- `-a` passes an argument to the program
- `-d` prints debug information
- `-h` prints help 
