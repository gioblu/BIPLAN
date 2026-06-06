
## BIPLAN CR.1
BIPLAN CR.1 (Bytecoded Interpreted Programming Language) is an experimental programming language for micro-controllers and real-time operating systems that fits in less than 48KB of program memory and it is implemented in less than 2000 lines of code. BIPLAN is a very compact language, even more compact than Wasm3, MicroPython or Lua. It is so compact that the BIPLAN interpreter fits in an Arduino Mega.

| Programming language | Minimum requirements |
| -------------------- | -------------------- |
| TinyBasicPlus        |  11KB ROM,  1KB RAM  |
| BIPLAN               |  48KB ROM,  5KB RAM  |
| Wasm3                |  64kB ROM, 10kB RAM  |
| MycroPython          | 256KB ROM, 16KB RAM  |
| Lua                  | 256KB ROM, 64kB RAM  |

The BIPLAN virtual machine implements the "fictional" BIP CR.1 computer architecture that operates with the BIP ASCII bytecode. It includes a serial interface, input-output ports, analog-to-digital and digital-to-analog converters, mono sound, text mode graphics and file handling.

### Why?
In 2017 I built a couple of standalone programmable computers with a screen and a keyboard using Arduino boards and running software I could more or less understand. In this [video](https://www.youtube.com/watch?v=xRZ9abs5ywA) you can see one machine I made in operation. At the end I was forced to use [TinyBasicPlus](https://github.com/BleuLlama/TinyBasicPlus/blob/master/TinyBasicPlus/TinyBasicPlus.ino) because it was the only implementation that fitted in them. The result was a machine with features comparable to an IBM 5150 booted into BASIC. Looking at it I asked myself: "How can BASIC, the first attempt to popularize programming, source of billions of lines of spaghetti code, now 57 years old, still be the only viable option?". I just needed a simple interpreted programming language implemented in C, with very few dependencies and layers of abstraction. After some experiments I decided to design and implement a new viable option for this use case, a programming language that is simple, portable, modern, but at the same time small enough to run even on limited micro-controllers.

### How?

The development of BIPLAN started in 2017, I wrote both the compiler and the interpreter from scratch avoiding external libraries, frameworks and the influence of compiler and interpreter design studies, learning by doing and evaluating results. In 9 years of experiments I wrote `BCC`, a pre-processor and a deterministic multi-pass compiler capable of syntax and lexical analysis (701 lines of code), and `BIPLAN`, a deterministic register-based virtual machine implemented with a recursive descent parser (874 lines of code).

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

When `bcc` is compiled using the target `fast` it is around 30 times faster than python and will compile to bip bytecode that is around 7 times more compact than pyc. To determine the performance of BCC I have implemented [benchmarks](/examples/LINUX/benchmarks/) that compare the compilation time and footprint of 20 different programs implemented in BIPLAN and Python, this is the output on my machine:

```
 ___________________________________________________________________
|                                       |             |             |
| Benchmark: Compilation time           | bcc compile | python3     |
|_______________________________________|_____________|_____________|
|                                       |             |             |
|  1. Hello world!                      | 18.07ms     | 210.54ms    |
|  2. For loop incrementing global      | 17.62ms     | 69.06ms     |
|  3. For loop nested if                | 17.87ms     | 69.90ms     |
|  4. For prints index                  | 17.66ms     | 69.60ms     |
|  5. While loop incrementing global    | 25.53ms     | 79.40ms     |
|  6. While increment and break         | 18.96ms     | 68.59ms     |
|  7. Read elapsed time cyclically      | 17.86ms     | 69.72ms     |
|  8. Get size of string                | 18.02ms     | 71.99ms     |
|  9. Check if numeric                  | 34.97ms     | 69.32ms     |
| 10. Basic math operations             | 23.40ms     | 82.58ms     |
| 11. Bitwise operations                | 17.75ms     | 70.24ms     |
| 12. Bitshift operations               | 18.43ms     | 69.51ms     |
| 13. Function call within condition    | 19.29ms     | 69.93ms     |
| 14. Function calls another function   | 19.00ms     | 70.61ms     |
| 15. Function leap year                | 17.71ms     | 70.12ms     |
| 16. Write character of string         | 19.17ms     | 69.50ms     |
| 17. Read character of string          | 17.78ms     | 69.37ms     |
| 18. For computing prime numbers       | 37.35ms     | 67.91ms     |
| 19. Non-recursive fibonacci           | 17.93ms     | 70.75ms     |
| 20. Factorial 20                      | 17.30ms     | 74.12ms     |
| 21. Pipes                             | 19.91ms     | 68.81ms     |
|_______________________________________|_____________|_____________|
                                          431.58ms     1631.59ms

bcc is 3.78 times faster than python3 compile.

 _________________________________________________________________
|                                      |             |            |
| Benchmark: Bytecode size             |  bip size   |  pyc size  |
|______________________________________|_____________|____________|
|                                      |             |            |
|  1. Hello world!                     | 26B         | 279B       |
|  2. For loop incrementing global     | 21B         | 328B       |
|  3. For loop nested if               | 26B         | 303B       |
|  4. For prints index                 | 18B         | 299B       |
|  5. While loop incrementing global   | 21B         | 308B       |
|  6. While increment and break        | 20B         | 272B       |
|  7. Read elapsed time cyclically     | 21B         | 361B       |
|  8. Get size of string               | 40B         | 307B       |
|  9. Check if numeric                 | 110B        | 323B       |
| 10. Basic math operations            | 60B         | 381B       |
| 11. Bitwise operations               | 53B         | 369B       |
| 12. Bitshift operations              | 30B         | 303B       |
| 13. Function call within condition   | 75B         | 464B       |
| 14. Function calls another function  | 92B         | 607B       |
| 15. Function leap year               | 72B         | 536B       |
| 16. Write character of string        | 68B         | 323B       |
| 17. Read character of string         | 71B         | 322B       |
| 18. For computing prime numbers      | 106B        | 520B       |
| 19. Non-recursive fibonacci          | 61B         | 565B       |
| 20. Factorial 20                     | 47B         | 491B       |
| 21. Pipes                            | 105B        | 702B       |
|______________________________________|_____________|____________|
| Total footprint                      | 1.12KB      | 8.17KB     |
|______________________________________|_____________|____________|

Footprint: bip is 7.32 times smaller than pyc.
```

When `biplan` is compiled using the target `fast` it interprets bip bytecode 1.3 times faster than python. To determine the performance of BIPLAN I have implemented [benchmarks](/examples/LINUX/benchmarks/) that compare the execution time of 20 different programs implemented in BIPLAN and Python, this is the output on my machine:

```
 ________________________________________________________________________________
|                                       |             |             |            |
| Benchmark: Interpretation time        |  BIPLAN     |  Python     | Iterations |
|_______________________________________|_____________|_____________|____________|
|                                       |             |             |            |
|  1. Hello world!                      | 81.55ms     | 135.89ms    | 100000     |
|  2. For loop incrementing global      | 9.62ms      | 71.17ms     | 100000     |
|  3. For loop nested if                | 18.44ms     | 74.04ms     | 100000     |
|  4. For prints index                  | 73.19ms     | 158.94ms    | 100000     |
|  5. While loop incrementing global    | 18.86ms     | 69.60ms     | 10000      |
|  6. While increment and break         | 24.60ms     | 68.55ms     | 10000      |
|  7. Read elapsed time cyclically      | 15.63ms     | 87.61ms     | 100000     |
|  8. Get size of string                | 13.14ms     | 76.14ms     | 100000     |
|  9. Check if numeric                  | 54.20ms     | 71.54ms     | 100000     |
| 10. Basic math operations             | 41.68ms     | 122.57ms    | 100000     |
| 11. Bitwise operations                | 39.43ms     | 113.40ms    | 100000     |
| 12. Bitshift operations               | 22.83ms     | 77.33ms     | 100000     |
| 13. Function call within condition    | 46.56ms     | 86.55ms     | 100000     |
| 14. Function calls another function   | 58.78ms     | 98.93ms     | 100000     |
| 15. Function leap year                | 75.26ms     | 97.41ms     | 100000     |
| 16. Write character of string         | 22.30ms     | 83.99ms     | 100000     |
| 17. Read character of string          | 316.75ms    | 227.03ms    | 100000     |
| 18. For computing prime numbers       | 746.80ms    | 725.51ms    | 100000     |
| 19. Non-recursive fibonacci           | 534.39ms    | 482.48ms    | 100000     |
| 20. Factorial 20                      | 152.60ms    | 244.22ms    | 100000     |
|_______________________________________|_____________|_____________|____________|
                                          2366.70ms     3172.99ms

BIPLAN is 1.34 times faster than Python.
```

### Documentation
- [Bytecode](/documentation/bytecode.md)
- [Configuration](/documentation/configuration.md)
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

Copyright 2022 Giovanni Blu Mitolo

Permission is hereby granted to You, free of charge, the rights to use, copy,
modify, merge, publish or distribute copies of the Software, subject to the
following conditions:

1.Use, copy, modify, merge, publish or distribute the Software only for
  experimental or educational purposes.

2.Companies, institutions, organizations and corporations don't have the right
  to use, copy, modify, merge, publish or distribute the Software.

3.THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
  FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
  COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
  IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
  YOU ARE SOLELY RESPONSIBLE FOR USING, COPYING, MODIFYING, MERGING, PUBLISHING
  OR REDISTRIBUTING THE SOFTWARE AND ASSUME ANY RISKS ASSOCIATED WITH YOUR
  EXERCISE OF PERMISSIONS UNDER THIS LICENSE.
```

The version name CR.1 was chosen to honour the italian [FIAT CR.1](https://en.wikipedia.org/wiki/Fiat_CR.1) biplane fighter aircraft. It was designed by Celestino Rosatelli, from whom it gained the 'CR' designation. The CR.1 was a [Sesquiplane](https://en.wikipedia.org/wiki/Biplane#Sesquiplane) of Wood-and-fabric construction.
