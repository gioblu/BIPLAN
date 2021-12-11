### biplan interpreter
The `biplan.cpp` file is a complete and ready to use interpreter. It is able to execute BIP machine language.

#### How to build it
1. Open the console
2. Locate the `BIPLAN/examples/LINUX/biplan-interpreter` directory
3. Digit `sudo make`
4. Digit `sudo make install`

#### How to use it
The `biplan` executable can be used to execute BIP machine language, in this example's directory you find [`fib.bip`](fib.bip), this file contains a program in BIP machine language that computes the 40th number of the Fibonacci sequence 100.000 times. Here you find the human readable version [bcc-compiler](../bcc-compiler/fib.bpl). You can use the `biplan` executable to interpret [`fib.bip`](fib.bip) and benchmark its performance against other programming languages.

1. Open the console
2. Locate the `BIPLAN/examples/LINUX/biplan-interpreter` directory
3. Digit `biplan -i fib.bip`

Expected output:
```
BIPLAN interpreter - Giovanni Blu Mitolo 2021
Source: fib.bip
Source length: 64B

Interpreter output:

102334155

Execution duration: 798395 microseconds
```

You can now write a BIPLAN program, play with the [bcc-compiler](../bcc-compiler) and use the `biplan` executable to interpret it. 

`biplan` supports additional arguments:
- `-a` passes an argument to the program
- `-b` specifies the serial baudrate
- `-s` specifies the serial port
- `-h` prints help 
