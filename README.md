
## BIPLAN™ CR.1
BIPLAN (Byte-coded Interpreted Programming Language) is an experimental programming language based on a recursive descent parser that uses only static memory allocation and operates a completely software-defined virtual machine that does not require a garbage collector. It's human-readable language called BIPLAN is compiled in an 7-bit ASCII virtual-machine language called BIP.

| Programming language | Minimum requirements |
| -------------------- | -------------------- |
| TinyBasicPlus        |  11KB ROM,  1KB RAM  |
| BIPLAN               |  12KB ROM,  1KB RAM  |
| Wasm3                |  64kB ROM, 10kB RAM  |
| MycroPython          | 256KB ROM, 16KB RAM  |
| Lua                  | 256KB ROM, 64kB RAM  |

BIPLAN has a modern syntax inspired by Python and it is expressly designed to operate efficiently on microcontrollers with limited resources although its implementation is designed to be easily extensible. Today the complexity of tools required for a programming language to work is often overwhelming, BIPLAN's architecture and its machine-language are designed to offer a very simple set of tools that can operate in a constrained environment with no need of external dependencies.

### Code example

Fibonacci sequence computation in 212 bytes of BIPLAN code:
```php
fibonacci(10) # Prints 0 1 1 2 3 5 8
stop # End of program
function fibonacci($x)
  $a = 0
  $b = 1
  $n = 0
  while $n < $x
    print $n, " "
    $a = $b
    $b = $n
    $n = $a + $b
  next
return
```
Compiled in 52 bytes of BIP virtual-machine language by the [`BCC`](/src/BCC.h) class:
```
~#(10)xf#($#)$$0$%1$&0w$&<$#p$&," "$$$%$%$&$&$$+$%nr
```
Interpreted at run time by the [`BIPLAN_Interpreter`](/src/BIPLAN.h) class:
```
0 1 1 2 3 5 8
```

### Documentation
- [Configuration](/documentation/configuration.md)
- [Comments](/documentation/comments.md) [`#`](/documentation/comments.md#comments)  
- [Conditions](/documentation/conditions.md) [`if`](/documentation/conditions.md#conditions) [`else`](/documentation/conditions.md#conditions) [`end`](/documentation/conditions.md#conditions)
- [Constants](/documentation/constants.md) [`true`](/documentation/constants.md) [`false`](/documentation/constants.md) [`HIGH`](/documentation/constants.md) [`LOW`](/documentation/constants.md) [`INPUT`](/documentation/constants.md) [`OUTPUT`](/documentation/constants.md)
- [Cycles](/documentation/cycles.md) [`for`](/documentation/cycles.md#for) [`while`](/documentation/cycles.md#while) [`break`](/documentation/cycles.md#break) [`continue`](/documentation/cycles.md#continue)
- [Functions](/documentation/functions.md) [`function`](/documentation/functions.md#functions) [`return`](/documentation/functions.md#functions)
- [Numeric variables](/documentation/numeric-variables.md) [`$`](/documentation/numeric-variables.md#numeric-variables) [`$[]`](/documentation/numeric-variables.md#numeric-variables)
- [Operators](/documentation/operators.md) [`+`](https://github.com/gioblu/BIPLAN/blob/master/documentation/operators.md) [`-`](https://github.com/gioblu/BIPLAN/blob/master/documentation/operators.md) [`*`](https://github.com/gioblu/BIPLAN/blob/master/documentation/operators.md) [`/`](https://github.com/gioblu/BIPLAN/blob/master/documentation/operators.md) [`%`](https://github.com/gioblu/BIPLAN/blob/master/documentation/operators.md) [`==`](https://github.com/gioblu/BIPLAN/blob/master/documentation/operators.md) [`!=`](https://github.com/gioblu/BIPLAN/blob/master/documentation/operators.md) [`>`](https://github.com/gioblu/BIPLAN/blob/master/documentation/operators.md) [`>=`](https://github.com/gioblu/BIPLAN/blob/master/documentation/operators.md) [`<`](https://github.com/gioblu/BIPLAN/blob/master/documentation/operators.md) [`<=`](https://github.com/gioblu/BIPLAN/blob/master/documentation/operators.md) [`&&`](https://github.com/gioblu/BIPLAN/blob/master/documentation/operators.md) [`||`](https://github.com/gioblu/BIPLAN/blob/master/documentation/operators.md) [`&`](https://github.com/gioblu/BIPLAN/blob/master/documentation/operators.md) [`|`](https://github.com/gioblu/BIPLAN/blob/master/documentation/operators.md) [`^`](https://github.com/gioblu/BIPLAN/blob/master/documentation/operators.md) [`>>`](https://github.com/gioblu/BIPLAN/blob/master/documentation/operators.md) [`<<`](https://github.com/gioblu/BIPLAN/blob/master/documentation/operators.md) [`++`](https://github.com/gioblu/BIPLAN/blob/master/documentation/operators.md) [`--`](https://github.com/gioblu/BIPLAN/blob/master/documentation/operators.md) [`~`](https://github.com/gioblu/BIPLAN/blob/master/documentation/operators.md) [`not`](https://github.com/gioblu/BIPLAN/blob/master/documentation/operators.md)
- [Strings](/documentation/strings.md) [`:`](/documentation/strings.md#strings) [`:[]`](/documentation/strings.md#strings)
- [System functions](/documentation/system-functions.md) [`stop`](/documentation/system-functions.md#stop) [`restart`](/documentation/system-functions.md#restart) [`char`](/documentation/system-functions.md#print) [`sizeof`](/documentation/system-functions.md#sizeof) [`print`](/documentation/system-functions.md#print) [`delay`](/documentation/system-functions.md#delay) [`random`](/documentation/system-functions.md#random) [`millis`](/documentation/system-functions.md#millis) [`sqrt`](/documentation/system-functions.md#sqrt) [`analogRead`](/documentation/system-functions.md#analogRead) [`digitalRead`](/documentation/system-functions.md#digitalRead) [`digitalWrite`](/documentation/system-functions.md#digitalWrite) [`pinMode`](/documentation/system-functions.md#pinMode) [`serialRead`](/documentation/system-functions.md#serialRead) [`serialWrite`](/documentation/system-functions.md#serialWrite) [`input`](/documentation/system-functions.md#input) [`index`](/documentation/system-functions.md#index) [`jump`](/documentation/system-functions.md#jump)
- [Unary operators](/documentation/unary-operators.md) [`++`](/documentation/unary-operators.md#unary-operators) [`--`](/documentation/unary-operators.md#unary-operators)

### License
This work is dual-licensed under [Apache 2.0](LICENSE.Apache-2.0) and [LGPL 3.0 (or any later version)](LICENSE.LGPL-3.0-or-later).
You can choose between one of them if you use this work.

`SPDX-License-Identifier: Apache-2.0 OR LGPL-3.0-or-later`

All the software included in this project is experimental and it is distributed "AS IS" without any warranty, use it at your own risk. BIPLAN™ and its brand are registered trademarks, property of Giovanni Blu Mitolo gioscarab@gmail.com

### Safety warning
This software is experimental and may not behave as expected. Consider that using a virtual machine of this sort, specially if enabling remote program update, is dangerous. When enabling remote programming of a BIPLAN virtual machine, it must be considered potentially compromised, manipulated or remotely actuated against your will. It should be considered a good practice not to connect to the internet systems that may create a damage (fire, flood, data-leak) if hacked.

#### TODO
- function must have end statement
- reset functions loops and registers states on reset
