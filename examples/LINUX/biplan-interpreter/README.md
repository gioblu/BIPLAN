### biplan interpreter
The `biplan.cpp` file is a complete and ready to use interpreter. It is able to execute BIP machine language.

#### How to build it
1. Open the console
2. Locate the `BIPLAN/examples/LINUX/biplan-interpreter` directory
3. Digit `make`

#### How to use it
The `biplan` executable can be used to execute BIP machine language, in this example's directory you find [`fib.bip`](fib.bip). This file contains an algorithm in BIP machine language able to compute the 40th number of the Fibonacci sequence. You can use the `biplan` executable to run it and benchmark its performance.

1. Open the console
2. Locate the `BIPLAN/examples/LINUX/biplan-interpreter` directory
3. Digit `./biplan fib.bip`

Expected output:
```
BIPLAN interpreter - Giovanni Blu Mitolo 2021
Source: fib.bip
Source length: 64B

Interpreter output:

102334155

Execution duration: 124 microseconds
```

You can now write a BIPLAN program, play with the [bcc-compiler](../bcc-compiler) and use the `biplan` executable to interpret it.
On my computer `biplan` needs 124 microseconds to run the algorithm, `python` instead needs around 170 milliseconds to run the same algorithm written in python. BIPLAN looks to be around 1370 times faster than python.
