### biplan interpreter
The `biplan.cpp` file is a complete and ready to use interpreter. It is able to execute BIP machine language.

#### How to build it
1. Open the console
2. Locate the `BIPLAN/examples/LINUX/biplan-interpreter` directory
3. Digit `g++ -DLINUX -I. -I ../../../src -std=gnu++11 biplan.cpp -o biplan -lpthread -lcrypt -lm -lrtD`

#### How to use it
The `biplan` executable can be used to execute BIP machine language, in this example's directory is located a `fib.bip` file that contains BIP machine code able to compute the 40th fibonacci number. We can use the `biplan` executable to run it and benchmark its performance.

1. Locate the `BIPLAN/examples/LINUX/biplan-interpreter` directory
2. Digit `./biplan fib.bip`

Expected output:
```
BIPLAN interpreter - Giovanni Blu Mitolo 2021
Source: fib.bip
Source length: 64B

Interpreter output:

102334155

Execution duration: 124 microseconds
```

On my computer it takes around 124 microseconds to find the 40th Fibonacci number. BIPLAN looks to be around 11316 times quicker than python.
