
## BIPLAN CR.1
BIPLAN CR.1 (Bytecoded Interpreted Programming Language) is an experimental interpreted language designed for microcontrollers and real-time operating systems. Both the interpreter and the compiler fit in less than 56KB of program memory and are implemented in less than 2000 lines of code; its footprint is significantly more compact than Wasm3, MicroPython, or Lua. By explicitly outlawing dynamic memory allocation, garbage collection, threads and speculative optimizations, BIPLAN is immune to runtime volatility, avoids a lot of architectural complexity and guarantees deterministic execution during both the compilation and interpretation phases.

| Programming language | Compiler | Interpreter | Minimum requirements |
| -------------------- | -------- | ----------- |-------------------- |
| TinyBasicPlus        |    ❌ (interprets source)    |     ✅     | 11KB ROM,  1KB RAM  |
| BIPLAN               |    ✅    |     ✅     | 56KB ROM,  5KB RAM  |
| Wasm3                |    ❌ (interprets bytecode)   |     ✅     | 64kB ROM, 10kB RAM  |
| MicroPython          |    ✅    |     ✅     | 256KB ROM, 16KB RAM  |
| Lua                  |    ✅    |     ✅     | 256KB ROM, 64kB RAM  |

BIPLAN is one of the few modern programming languages that provide a compiler and an interpreter in 56KB.

BIPLAN's virtual machine implements the "fictional" BIP CR.1 computer architecture that operates with the BIP ASCII bytecode. It includes a serial interface, input-output ports, analog-to-digital and digital-to-analog converters, mono sound, text mode graphics, file handling and inter-process communication pipes.

### Why?
In 2017 I built a couple of standalone [programmable computers](https://www.youtube.com/watch?v=xRZ9abs5ywA) with a screen and a keyboard using Arduino boards to run software I could understand. I was forced to use [TinyBasicPlus](https://github.com/BleuLlama/TinyBasicPlus/blob/master/TinyBasicPlus/TinyBasicPlus.ino) because it was the only interpreted language that could fit into such tight memory constraints. The result was a machine with features comparable to an IBM 5150 booted into BASIC. Looking at it I asked myself: "How can BASIC, the first attempt to popularize programming and the source of billions of lines of spaghetti code, now 57 years old, still be the only viable option?" I just needed a simple interpreted programming language implemented in C, with very few dependencies and layers of abstraction. After some experiments I decided to design and implement that myself. A programming language that is simple, portable, modern, efficient, but at the same time small enough to run even on limited micro-controllers.

### How?

The development of BIPLAN started in 2017. I wrote both the compiler and the interpreter from scratch avoiding external libraries, frameworks and the influence of compiler and interpreter design studies, learning by doing and evaluating results. In 9 years of experiments I wrote `BCC`, a pre-processor and a multi-pass compiler capable of syntax and lexical analysis (701 lines of code), and `BIPLAN`, a register-based virtual machine implemented with a recursive descent parser (874 lines of code).

### Code example

Fibonacci sequence computation in 149 bytes of BIPLAN code:
```c
print fibonacci(40)
stop
function fibonacci($a, locals: $b, $c)
  $b = 1
  for #r = 0 to $a
    $a = $b
    $b = $c
    $c = $a + $b
  next
  return $c
done
```
Compiled in 45 bytes of BIP bytecode by the [`BCC`](/src/BCC.h) class:
```
p~$40)xf$}j}k}l)}k1@$0,}j}j}k}k}l}l}j+}k;r}ld
```
Compiler output:
```
BCC (BIP Compiler Collection)
Giovanni Blu Mitolo 2025

| Source   | BIPLAN/examples/LINUX/bcc-compiler/fib.biplan (156B)
| Target   | BIPLAN/examples/LINUX/bcc-compiler/fib.bip (45B)
| Duration | 0.09 milliseconds
| State    | ✅ Success
```
Interpreted at run time by the [`BIPLAN_Interpreter`](/src/BIPLAN.c) class:
```
102334155
```
On my linux computer the [biplan-interpreter](examples/LINUX/biplan-interpreter/) needs around 30 microseconds to run the algorithm.

### Performance

The table below contains the results of the [benchmarks](/examples/LINUX/benchmarks/) developed to compare 20 different programs implemented in BIPLAN and Python:

| Language | Bytecode size | Compilation | Interpretation | Startup |
| -------- | ------------- | ----------- | -------------- | ------- |
| BIPLAN   | 1.12KB        | 431.58ms    | 2366.70ms      | 7ms     |
| Python   | 8.17KB        | 1631.59ms   | 3172.99ms      | 48ms    |

BIPLAN is more efficient than Python and it is well suited for applications that require fast startup time, minimal bytecode size and low power consumption.

### Documentation
- [Bytecode](/documentation/bytecode.md)
- [Configuration](/documentation/configuration.md)
- [Performance](/documentation/performance.md)
- [Comments](/documentation/comments.md) [`//`](/documentation/comments.md)
- [Conditions](/documentation/conditions.md) [`if`](/documentation/conditions.md) [`else`](/documentation/conditions.md) [`end`](/documentation/conditions.md)
- [Constants](/documentation/constants.md) [`true`](/documentation/constants.md) [`false`](/documentation/constants.md) [`HIGH`](/documentation/constants.md) [`LOW`](/documentation/constants.md) [`INPUT`](/documentation/constants.md) [`OUTPUT`](/documentation/constants.md)
- [Cycles](/documentation/cycles.md) [`for`](/documentation/cycles.md#for) [`while`](/documentation/cycles.md#while) [`next`](/documentation/cycles.md#next) [`break`](/documentation/cycles.md#break) [`continue`](/documentation/cycles.md#continue)
- [Functions](/documentation/functions.md) [`function`](/documentation/functions.md) [`locals`](/documentation/functions.md) [`return`](/documentation/functions.md)
- [Macros](/documentation/macros.md) [`macro`](/documentation/macros.md#pre-processor-macros)
- [Numeric variables](/documentation/numeric-variables.md) [`$`](/documentation/numeric-variables.md) [`$[]`](/documentation/numeric-variables.md)
- [Operators](/documentation/operators.md) [`+`](/documentation/operators.md) [`-`](/documentation/operators.md) [`*`](/documentation/operators.md) [`/`](/documentation/operators.md) [`%`](/documentation/operators.md) [`==`](/documentation/operators.md) [`!=`](/documentation/operators.md) [`>`](/documentation/operators.md) [`>=`](/documentation/operators.md) [`<`](/documentation/operators.md) [`<=`](/documentation/operators.md) [`&&`](/documentation/operators.md) [`||`](/documentation/operators.md) [`&`](/documentation/operators.md) [`|`](/documentation/operators.md) [`^`](/documentation/operators.md) [`>>`](/documentation/operators.md) [`<<`](/documentation/operators.md) [`++`](/documentation/operators.md) [`--`](/documentation/operators.md) [`~`](/documentation/operators.md) [`not`](/documentation/operators.md)
- [Strings](/documentation/strings.md) [`:`](/documentation/strings.md) [`:[]`](/documentation/strings.md)
- [System functions](/documentation/system-functions.md) [`adc read`](/documentation/system-functions.md#adc-read) [`args`](/documentation/system-functions.md#args) [`char`](/documentation/system-functions.md#print) [`cursor`](/documentation/system-functions.md#cursor) [`delay`](/documentation/system-functions.md#delay) [`file close`](/documentation/system-functions.md#file-close) [`file open`](/documentation/system-functions.md#file-open) [`file read`](/documentation/system-functions.md#file-read) [`file write`](/documentation/system-functions.md#file-write) [`include`](/documentation/system-functions.md#include) [`index`](/documentation/system-functions.md#index) [`input`](/documentation/system-functions.md#input) [`io open`](/documentation/system-functions.md#io-open) [`io read`](/documentation/system-functions.md#io-read) [`io write`](/documentation/system-functions.md#digitalWrite) [`mem`](/documentation/system-functions.md#mem) [`millis`](/documentation/system-functions.md#millis) [`number`](/documentation/system-functions.md#number) [`numeric`](/documentation/system-functions.md#numeric) [`print`](/documentation/system-functions.md#print) [`random`](/documentation/system-functions.md#random) [`restart`](/documentation/system-functions.md#restart) [`serial open`](/documentation/system-functions.md#serial-open) [`serial read`](/documentation/system-functions.md#serial-read) [`serial write`](/documentation/system-functions.md#serial-write) [`size`](/documentation/system-functions.md#size) [`stop`](/documentation/system-functions.md#stop) [`string`](/documentation/system-functions.md#string)
- [Unary operators](/documentation/unary-operators.md) [`++`](/documentation/unary-operators.md) [`--`](/documentation/unary-operators.md)

### Building BIPLAN

All you need to build BIPLAN is `g++`.

- [Build the compiler on Linux](/examples/LINUX/bcc-compiler/)
- [Build the compiler on OSX](/examples/OSX/bcc-compiler/)
- [Build the interpreter on Linux](/examples/LINUX/biplan-interpreter/)
- [Build the interpreter on OSX](/examples/OSX/biplan-interpreter/)
- [Linux examples](/examples/LINUX/)
- [OSX examples](/examples/OSX/)
- [Arduino examples](/examples/ARDUINO/)

### Notes on AI assisted development
Considering that the entire interpreter and compiler source code totals less than 90KB, LLMs can retain the complete toolchain within a single context window. This enables AI models to perform exceptionally well when debugging, porting or optimizing BIPLAN's source code. The [AGENTS.md]() file contains my personal configuration for this workflow.

### Contribute
Feel free to send a pull request sharing something you have made that could help, if you want to support this project you can also try to solve an issue. AI-generated slop will not be reviewed: contributions to this project are evaluated only if well detailed, throughly designed, minimalistic and efficient. Thanks to support, expertise, kindness and talent of the following contributors, BIPLAN has been strongly tested, enhanced and verified:

[Fred Larsen](https://github.com/fredilarsen), [Kevin Mathis](https://github.com/KMathisGit)

### License
The license grants permission to use, copy, modify, merge, publish and distribute BIPLAN, only to individuals, for experimental purposes. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND. You are solely responsible for using, copying, modifying, merging, publishing or redistributing BIPLAN and assume any risks associated with your exercise of permissions under this License:

```
Definitions.

"You" (or "Your") shall mean an individual, human, exercising
permissions granted by this License.

"Software" shall mean the source code, associated documentation
and configuration files included in the BIPLAN directory.

"License" shall mean the conditions for use, copy, modify, merge, publish or
distribute the Software as defined by Section 1 through 3 of this document.

BIPLAN Experimenter's License

Copyright 2026 Giovanni Blu Mitolo

Permission is hereby granted to You, free of charge, the rights to use, copy,
modify, merge, publish or distribute copies of the Software, subject to the
following conditions:

1. Use, copy, modify, merge, publish or distribute the Software only for
   non-commercial, experimental or educational purposes.

2. Companies, institutions, organizations and corporations don't have the right
   to use, copy, modify, merge, publish or distribute the Software.

3. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
   FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
   COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
   IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
   YOU ARE SOLELY RESPONSIBLE FOR USING, COPYING, MODIFYING, MERGING, PUBLISHING
   OR REDISTRIBUTING THE SOFTWARE AND ASSUME ANY RISKS ASSOCIATED WITH YOUR
   EXERCISE OF PERMISSIONS UNDER THIS LICENSE.

Commercial Licensing Notice

Companies, corporations, and institutions interested in obtaining a commercial or
institutional license for BIPLAN may submit an official inquiry directly to the
author via email at gioscarab@gmail.com
```

The version name CR.1 was chosen to honour the italian [FIAT CR.1](https://en.wikipedia.org/wiki/Fiat_CR.1) biplane fighter aircraft. It was designed by Celestino Rosatelli, from whom it gained the 'CR' designation. The CR.1 was a [Sesquiplane](https://en.wikipedia.org/wiki/Biplane#Sesquiplane) of Wood-and-fabric construction.
