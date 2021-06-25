
## BIPLAN™ CR.1
BIPLAN (Byte-coded Interpreted Programming Language) is an experimental interpreted programming language that fits in less than 12KB of program memory. BIPLAN is a very compact language, even more compact than Wasm3, MicroPython or Lua.

| Programming language | Minimum requirements |
| -------------------- | -------------------- |
| TinyBasicPlus        |  11KB ROM,  1KB RAM  |
| BIPLAN               |  12KB ROM,  1KB RAM  |
| Wasm3                |  64kB ROM, 10kB RAM  |
| MycroPython          | 256KB ROM, 16KB RAM  |
| Lua                  | 256KB ROM, 64kB RAM  |

### Why?

In 2017 I built a couple of stand-alone computers using Arduino boards and I was forced to use BASIC because it was the only interpreted programming language that fitted in them. I asked myself: "How can BASIC, the first attempt to popularize programming, source of billions of lines of spaghetti code, now 57 years old, still be the only viable option?". After some experiments I understood there was space for a new language; quick, portable, modern, but at the same time small enough to run on limited micro-controllers.

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

### Documentation
- [Configuration](/documentation/configuration.md)
- [Comments](/documentation/comments.md) [`#`](/documentation/comments.md)
- [Conditions](/documentation/conditions.md) [`if`](/documentation/conditions.md) [`else`](/documentation/conditions.md) [`end`](/documentation/conditions.md)
- [Constants](/documentation/constants.md) [`true`](/documentation/constants.md) [`false`](/documentation/constants.md) [`HIGH`](/documentation/constants.md) [`LOW`](/documentation/constants.md) [`INPUT`](/documentation/constants.md) [`OUTPUT`](/documentation/constants.md)
- [Cycles](/documentation/cycles.md) [`for`](/documentation/cycles.md#for) [`while`](/documentation/cycles.md#while) [`next`](/documentation/cycles.md#next) [`break`](/documentation/cycles.md#break) [`continue`](/documentation/cycles.md#continue)
- [Functions](/documentation/functions.md) [`function`](/documentation/functions.md) [`return`](/documentation/functions.md)
- [Numeric variables](/documentation/numeric-variables.md) [`$`](/documentation/numeric-variables.md) [`$[]`](/documentation/numeric-variables.md)
- [Operators](/documentation/operators.md) [`+`](/documentation/operators.md) [`-`](/documentation/operators.md) [`*`](/documentation/operators.md) [`/`](/documentation/operators.md) [`%`](/documentation/operators.md) [`==`](/documentation/operators.md) [`!=`](/documentation/operators.md) [`>`](/documentation/operators.md) [`>=`](/documentation/operators.md) [`<`](/documentation/operators.md) [`<=`](/documentation/operators.md) [`&&`](/documentation/operators.md) [`||`](/documentation/operators.md) [`&`](/documentation/operators.md) [`|`](/documentation/operators.md) [`^`](/documentation/operators.md) [`>>`](/documentation/operators.md) [`<<`](/documentation/operators.md) [`++`](/documentation/operators.md) [`--`](/documentation/operators.md) [`~`](/documentation/operators.md) [`not`](/documentation/operators.md)
- [Strings](/documentation/strings.md) [`:`](/documentation/strings.md) [`:[]`](/documentation/strings.md)
- [System functions](/documentation/system-functions.md) [`adc read`](/documentation/system-functions.md#adc-read) [`char`](/documentation/system-functions.md#print) [`delay`](/documentation/system-functions.md#delay) [`file close`](/documentation/system-functions.md#file-close) [`file open`](/documentation/system-functions.md#file-open) [`file read`](/documentation/system-functions.md#file-read) [`file write`](/documentation/system-functions.md#file-write) [`jump`](/documentation/system-functions.md#jump) [`io open`](/documentation/system-functions.md#io-open) [`io read`](/documentation/system-functions.md#io-read) [`io write`](/documentation/system-functions.md#digitalWrite) [`index`](/documentation/system-functions.md#index) [`input`](/documentation/system-functions.md#input) [`millis`](/documentation/system-functions.md#millis) [`print`](/documentation/system-functions.md#print) [`random`](/documentation/system-functions.md#random) [`restart`](/documentation/system-functions.md#restart) [`serial open`](/documentation/system-functions.md#serial-open) [`serial read`](/documentation/system-functions.md#serial-read) [`serial write`](/documentation/system-functions.md#serial-write) [`size`](/documentation/system-functions.md#size) [`sqrt`](/documentation/system-functions.md#sqrt) [`stop`](/documentation/system-functions.md#stop) [`system`](/documentation/system-functions.md#system)
- [Unary operators](/documentation/unary-operators.md) [`++`](/documentation/unary-operators.md) [`--`](/documentation/unary-operators.md)

### License
This work is dual-licensed under [Apache 2.0](LICENSE.Apache-2.0) and [LGPL 3.0 (or any later version)](LICENSE.LGPL-3.0-or-later).
You can choose between one of them if you use this work.

`SPDX-License-Identifier: Apache-2.0 OR LGPL-3.0-or-later`

All the software included in this project is experimental and it is distributed "AS IS" without any warranty, use it at your own risk. BIPLAN™ and its brand are registered trademarks, property of Giovanni Blu Mitolo gioscarab@gmail.com

### Safety warning
This software is experimental and may not behave as expected. Consider that using a virtual machine of this sort, specially if enabling remote program update, is dangerous. When enabling remote programming of a BIPLAN virtual machine, it must be considered potentially compromised, manipulated or remotely actuated against your will. It should be considered a good practice not to connect to the internet systems that may create a damage (fire, flood, data-leak) if hacked.
