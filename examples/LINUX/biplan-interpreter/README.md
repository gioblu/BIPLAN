## `biplan`
The `biplan.cpp` file is a complete and ready to use BIPLAN compiler and interpreter.

### How to build it
1. Open the console in the `BIPLAN/examples/LINUX/biplan-interpreter` directory
2. You can choose to build the compact interpreter using `sudo make compact` which is optimized for size (~47KB), or build the executable optimized for performance using `sudo make fast`, the resulting binary will be larger in size (~105KB) but around twice as fast if compared to the `compact` target.
3. Digit `sudo make install`

### How to use it
The `biplan` executable is copied in `usr/local/bin` to be reachable everywhere within your system. You can use it to interpret BIPLAN source code or BIP machine language:

Open the console in the `BIPLAN/examples/LINUX/fibonacci` directory and digit `biplan fib.biplan`, you should see the following output `102334155`.

`biplan -d fib.biplan` prints debug information:
```
BIPLAN interpreter - Giovanni Blu Mitolo 2026
Source: fib.bip
Source length: 57B

Interpreter output:

102334155

Execution duration: 648949 microseconds
```

For additional details, see the output printed by `biplan -h`.

### How to get rid of it
To remove the executable from the `usr/local/bin` directory digit `sudo make clean`.
