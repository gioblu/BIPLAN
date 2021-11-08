
## BIPLAN™ CR.1
BIPLAN CR.1 (Byte-coded Interpreted Programming Language) is an experimental interpreted programming language that fits in less than 12KB of program memory. BIPLAN is a very compact language, even more compact than Wasm3, MicroPython or Lua.

| Programming language | Minimum requirements |
| -------------------- | -------------------- |
| TinyBasicPlus        |  11KB ROM,  1KB RAM  |
| BIPLAN               |  12KB ROM,  1KB RAM  |
| Wasm3                |  64kB ROM, 10kB RAM  |
| MycroPython          | 256KB ROM, 16KB RAM  |
| Lua                  | 256KB ROM, 64kB RAM  |

This tiny language implements the virtual or "fictional" BIP CR.1 computer architecture that operates with the BIP ASCII byte-code and includes a serial interface, input-output ports, analog-to-digital and digital-to-analog converters, mono sound, text mode graphics and file handling.  

### Why?

In 2017 I built a couple of stand-alone computers using Arduino boards, I was forced to use BASIC because it was the only interpreted programming language that fitted in them. I asked myself: "How can BASIC, the first attempt to popularize programming, source of billions of lines of spaghetti code, now 57 years old, still be the only viable option?". After some experiments I understood there was space for a new language; quick, portable, modern, but at the same time small enough to run on limited micro-controllers.

### Code example

Fibonacci sequence computation in 166 bytes of BIPLAN code:
```php
print fibonacci(40)
stop
function fibonacci($n, locals: $a, $b)
  $b = 1
  for $r = 0 to $n - 1
    $a = $b
    $b = result
    result = $a + $b
  next
return result
```
Compiled in 43 bytes of BIP virtual-machine language by the [`BCC`](/src/BCC.h) class:
```
p~#40)xf#$#$%$&)$&1@'0,$#-1$%$&$&tt$%+$&nrt
```
Compiler output:
```
BCC (BIP Compiler Collection) Giovanni Blu Mitolo 2021
Source: fib.bpl
Target: ../biplan-interpreter/fib.bip
Source length: 166B, BIP length: 43B, reduction: 74.096390%
Compilation time: 264 microseconds
```
Interpreted at run time by the [`BIPLAN_Interpreter`](/src/BIPLAN.c) class:
```
102334155
```
On my linux computer the [biplan-interpreter](examples/LINUX/biplan-interpreter/) needs around 35 microseconds to run the algorithm.

### Performance

For now BIPLAN is around 2 times slower than python on my linux machine and around 10 times quicker than TinyBasicPlus when running on Arduino compatible boards.

### Documentation
- [Configuration](/documentation/configuration.md)
- [Comments](/documentation/comments.md) [`#`](/documentation/comments.md)
- [Conditions](/documentation/conditions.md) [`if`](/documentation/conditions.md) [`else`](/documentation/conditions.md) [`end`](/documentation/conditions.md)
- [Constants](/documentation/constants.md) [`true`](/documentation/constants.md) [`false`](/documentation/constants.md) [`HIGH`](/documentation/constants.md) [`LOW`](/documentation/constants.md) [`INPUT`](/documentation/constants.md) [`OUTPUT`](/documentation/constants.md)
- [Cycles](/documentation/cycles.md) [`for`](/documentation/cycles.md#for) [`while`](/documentation/cycles.md#while) [`next`](/documentation/cycles.md#next) [`break`](/documentation/cycles.md#break) [`continue`](/documentation/cycles.md#continue)
- [Functions](/documentation/functions.md) [`function`](/documentation/functions.md) [`locals`](/documentation/functions.md) [`result`](/documentation/functions.md) [`return`](/documentation/functions.md)
- [Numeric variables](/documentation/numeric-variables.md) [`$`](/documentation/numeric-variables.md) [`$[]`](/documentation/numeric-variables.md)
- [Operators](/documentation/operators.md) [`+`](/documentation/operators.md) [`-`](/documentation/operators.md) [`*`](/documentation/operators.md) [`/`](/documentation/operators.md) [`%`](/documentation/operators.md) [`==`](/documentation/operators.md) [`!=`](/documentation/operators.md) [`>`](/documentation/operators.md) [`>=`](/documentation/operators.md) [`<`](/documentation/operators.md) [`<=`](/documentation/operators.md) [`&&`](/documentation/operators.md) [`||`](/documentation/operators.md) [`&`](/documentation/operators.md) [`|`](/documentation/operators.md) [`^`](/documentation/operators.md) [`>>`](/documentation/operators.md) [`<<`](/documentation/operators.md) [`++`](/documentation/operators.md) [`--`](/documentation/operators.md) [`~`](/documentation/operators.md) [`not`](/documentation/operators.md)
- [Strings](/documentation/strings.md) [`:`](/documentation/strings.md) [`:[]`](/documentation/strings.md)
- [System functions](/documentation/system-functions.md) [`adc read`](/documentation/system-functions.md#adc-read) [`char`](/documentation/system-functions.md#print) [`delay`](/documentation/system-functions.md#delay) [`file close`](/documentation/system-functions.md#file-close) [`file open`](/documentation/system-functions.md#file-open) [`file read`](/documentation/system-functions.md#file-read) [`file write`](/documentation/system-functions.md#file-write) [`jump`](/documentation/system-functions.md#jump) [`io open`](/documentation/system-functions.md#io-open) [`io read`](/documentation/system-functions.md#io-read) [`io write`](/documentation/system-functions.md#digitalWrite) [`index`](/documentation/system-functions.md#index) [`input`](/documentation/system-functions.md#input) [`millis`](/documentation/system-functions.md#millis) [`print`](/documentation/system-functions.md#print) [`random`](/documentation/system-functions.md#random) [`restart`](/documentation/system-functions.md#restart) [`serial open`](/documentation/system-functions.md#serial-open) [`serial read`](/documentation/system-functions.md#serial-read) [`serial write`](/documentation/system-functions.md#serial-write) [`size`](/documentation/system-functions.md#size) [`sqrt`](/documentation/system-functions.md#sqrt) [`stop`](/documentation/system-functions.md#stop) [`system`](/documentation/system-functions.md#system)
- [Unary operators](/documentation/unary-operators.md) [`++`](/documentation/unary-operators.md) [`--`](/documentation/unary-operators.md)

### License
The license grants permission to use, copy, modify, merge, publish and distribute BIPLAN, only to individuals, for experimental purposes. THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND. You are solely responsible for using, copying, modifying, merging, publishing or redistributing BIPLAN and assume any risks associated with your exercise of permissions under this License:

```
Definitions.

"You" (or "Your") shall mean an individual, human, exercising
permissions granted by this License.

"Software" shall mean the source code, associated documentation
and configuration files included in the BIPLAN directory

"License" shall mean the conditions for use, copy, modify, merge, publish or
distribute the Software as defined by Section 1 through 3 of this document.

BIPLAN Experimenter's License

Copyright 2021 Giovanni Blu Mitolo

Permission is hereby granted to You, free of charge, the rights to use, copy,
modify, merge, publish or distribute copies of the Software, subject to the
following conditions:

1.Use, copy, modify, merge, publish or distribute the Software only for
  experimental or educational purposes.

2.Companies, institutions, organizations and corporations don't have the right
  to use, copy, modify, merge, publish or distribute the Software

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
