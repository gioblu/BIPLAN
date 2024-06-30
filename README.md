
## BIPLAN CR.1
BIPLAN CR.1 (Bytecoded Interpreted Programming Language) is an experimental programming language that fits in less than 12KB of program memory and it is implemented in less than 2000 lines of code. BIPLAN is a very compact language, even more compact than Wasm3, MicroPython or Lua. It is so compact that the BIPLAN virtual machine and the BCC compiler fit in an Arduino Duemilanove.

| Programming language | Minimum requirements |
| -------------------- | -------------------- |
| TinyBasicPlus        |  11KB ROM,  1KB RAM  |
| BIPLAN               |  12KB ROM,  1KB RAM  |
| Wasm3                |  64kB ROM, 10kB RAM  |
| MycroPython          | 256KB ROM, 16KB RAM  |
| Lua                  | 256KB ROM, 64kB RAM  |

The BIPLAN virtual machine implements the "fictional" BIP CR.1 computer architecture that operates with the BIP ASCII bytecode. It includes fixed-point arithmetics, serial interface, input-output ports, analog-to-digital and digital-to-analog converters, mono sound, text mode graphics and file handling.

### Why?
In 2017 I built a couple of standalone programmable computers with a screen and a keyboard using Arduino boards and running software I could more or less understand. At the end I was forced to use [TinyBasicPlus](https://github.com/BleuLlama/TinyBasicPlus/blob/master/TinyBasicPlus/TinyBasicPlus.ino) because it was the only implementation that fitted in them. The result was a machine with features comparable to an IBM 5150 booted into BASIC. Looking at it I asked myself: "How can BASIC, the first attempt to popularize programming, source of billions of lines of spaghetti code, now 57 years old, still be the only viable option?". I really needed a simple interpreted programming language implemented in C, with very few dependencies and layers of abstraction, easy to port and analyze that could fit both in an Arduino and in my brain. After some experiments I decided to design and implement a new viable option for this use case, a programming language that is simple, portable, modern, but at the same time small enough to run even on limited micro-controllers.

### How?

The development of BIPLAN started in 2017, I wrote both the compiler and the interpreter from scratch avoiding external libraries, frameworks and the influence of compiler and interpreter design studies, learning by doing and evaluating results. In 5 years of experiments I wrote `BCC`, a pre-processor and multi-pass compiler capable of syntax and lexical analysis (576 lines of code), and `BIPLAN`, a register-based virtual machine implemented with a recursive descent parser (784 lines of code).

### Code example

Fibonacci sequence computation in 166 bytes of BIPLAN code:
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
```
Compiled in 39 bytes of BIP bytecode by the [`BCC`](/src/BCC.h) class:
```
p~$40)xf$}t}u)}u1@$0,}t}t}u}utt}t+}u;rt
```
Compiler output:
```
BCC (BIP Compiler Collection) Giovanni Blu Mitolo 2024
Source: fib.bpl
Target: fib.bip
Source length: 157B, BIP length: 39B, reduction: 75.159233%
Compilation time: 239 microseconds
```
Interpreted at run time by the [`BIPLAN_Interpreter`](/src/BIPLAN.c) class:
```
102334155
```
On my linux computer the [biplan-interpreter](examples/LINUX/biplan-interpreter/) needs around 30 microseconds to run the algorithm.

### Performance

For now this implementation is around 2 times slower than python, requirement 5 is still not satisfied.

### Documentation
- [Bytecode](/documentation/bytecode.md)
- [Configuration](/documentation/configuration.md)
- [Comments](/documentation/comments.md) [`#`](/documentation/comments.md)
- [Conditions](/documentation/conditions.md) [`if`](/documentation/conditions.md) [`else`](/documentation/conditions.md) [`end`](/documentation/conditions.md)
- [Constants](/documentation/constants.md) [`true`](/documentation/constants.md) [`false`](/documentation/constants.md) [`HIGH`](/documentation/constants.md) [`LOW`](/documentation/constants.md) [`INPUT`](/documentation/constants.md) [`OUTPUT`](/documentation/constants.md)
- [Cycles](/documentation/cycles.md) [`for`](/documentation/cycles.md#for) [`while`](/documentation/cycles.md#while) [`next`](/documentation/cycles.md#next) [`break`](/documentation/cycles.md#break) [`continue`](/documentation/cycles.md#continue)
- [Functions](/documentation/functions.md) [`function`](/documentation/functions.md) [`locals`](/documentation/functions.md) [`return`](/documentation/functions.md)
- [Macros](/documentation/macros.md) [`macro`](/documentation/macros.md#pre-processor-macros)
- [Numeric variables](/documentation/numeric-variables.md) [`$`](/documentation/numeric-variables.md) [`$[]`](/documentation/numeric-variables.md)
- [Operators](/documentation/operators.md) [`+`](/documentation/operators.md) [`-`](/documentation/operators.md) [`*`](/documentation/operators.md) [`/`](/documentation/operators.md) [`%`](/documentation/operators.md) [`==`](/documentation/operators.md) [`!=`](/documentation/operators.md) [`>`](/documentation/operators.md) [`>=`](/documentation/operators.md) [`<`](/documentation/operators.md) [`<=`](/documentation/operators.md) [`&&`](/documentation/operators.md) [`||`](/documentation/operators.md) [`&`](/documentation/operators.md) [`|`](/documentation/operators.md) [`^`](/documentation/operators.md) [`>>`](/documentation/operators.md) [`<<`](/documentation/operators.md) [`++`](/documentation/operators.md) [`--`](/documentation/operators.md) [`~`](/documentation/operators.md) [`not`](/documentation/operators.md)
- [Strings](/documentation/strings.md) [`:`](/documentation/strings.md) [`:[]`](/documentation/strings.md)
- [System functions](/documentation/system-functions.md) [`adc read`](/documentation/system-functions.md#adc-read) [`args`](/documentation/system-functions.md#args) [`char`](/documentation/system-functions.md#print) [`cursor`](/documentation/system-functions.md#cursor) [`delay`](/documentation/system-functions.md#delay) [`file close`](/documentation/system-functions.md#file-close) [`file open`](/documentation/system-functions.md#file-open) [`file read`](/documentation/system-functions.md#file-read) [`file write`](/documentation/system-functions.md#file-write) [`include`](/documentation/system-functions.md#include) [`index`](/documentation/system-functions.md#index) [`input`](/documentation/system-functions.md#input) [`io open`](/documentation/system-functions.md#io-open) [`io read`](/documentation/system-functions.md#io-read) [`io write`](/documentation/system-functions.md#digitalWrite) [`jump`](/documentation/system-functions.md#jump) [`label`](/documentation/system-functions.md#label) [`mem`](/documentation/system-functions.md#mem) [`millis`](/documentation/system-functions.md#millis) [`number`](/documentation/system-functions.md#number) [`numeric`](/documentation/system-functions.md#numeric) [`print`](/documentation/system-functions.md#print) [`random`](/documentation/system-functions.md#random) [`restart`](/documentation/system-functions.md#restart) [`serial open`](/documentation/system-functions.md#serial-open) [`serial read`](/documentation/system-functions.md#serial-read) [`serial write`](/documentation/system-functions.md#serial-write) [`size`](/documentation/system-functions.md#size) [`stop`](/documentation/system-functions.md#stop) [`string`](/documentation/system-functions.md#string) [`system`](/documentation/system-functions.md#system)
- [Unary operators](/documentation/unary-operators.md) [`++`](/documentation/unary-operators.md) [`--`](/documentation/unary-operators.md)

### Building BIPLAN

All you need to build BIPLAN is `g++`.

- [How to build and use the compiler on Linux](/examples/LINUX/bcc-compiler/)
- [How to build and use the compiler on OSX](/examples/OSX/bcc-compiler/)
- [How to build and use the interpreter on Linux](/examples/LINUX/biplan-interpreter/)
- [How to build and use the interpreter on OSX](/examples/OSX/biplan-interpreter/)
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
