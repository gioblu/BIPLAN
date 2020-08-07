
## BIPLAN™ CR.1
BIPLAN (Byte-coded Interpreted Programming Language) is an experimental programming language based on a recursive descent parser that uses only static memory allocation and operates a completely software-defined 7bit virtual machine that does not require a garbage collector.

| Programming language | Minimum requirements |
| -------------------- | -------------------- |
| TinyBasicPlus        |  11KB ROM,  1KB RAM  |
| BIPLAN               |  12KB ROM,  1KB RAM  |
| Wasm3                |  64kB ROM, 10kB RAM  |
| MycroPython          | 256KB ROM, 16KB RAM  |
| Lua                  | 256KB ROM, 64kB RAM  |

BIPLAN has a modern syntax inspired by Ruby on Rails and Python and it is expressly designed to operate efficiently on microcontrollers with limited resources although its implementation is designed to be easily extended and applied in other architectures or real time operative systems.

### Code example

Here is some BIPLAN code that shows how to compute the Fibonacci sequence:
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

### Documentation
- [Configuration](documentation/configuration.md)
- [Comments](documentation/comments.md)
- [Conditions](documentation/conditions.md)
- [Constants](documentation/constants.md)
- [Cycles](documentation/cycles.md)
- [Functions](documentation/functions.md)
- [Numeric variables](documentation/numeric-variables.md)
- [Operators](documentation/operators.md)
- [Strings](documentation/strings.md)
- [System functions](documentation/system-functions.md)
- [Unary operators](documentation/unary-operators.md)

### License
All the software included in this project is experimental and it is distributed "AS IS" without any warranty, use it at your own risk. [Licensed](/LICENSE) under the Apache License, Version 2.0. BIPLAN™ and its brand are registered trademarks, property of Giovanni Blu Mitolo gioscarab@gmail.com

### Safety warning
This software is experimental and may not behave as expected. Consider that using a virtual machine of this sort, specially if enabling remote program update, is dangerous. When enabling remote programming of a BIPLAN virtual machine, it must be considered potentially compromised, manipulated or remotely actuated against your will. It should be considered a good practice not to connect to the internet systems that may create a damage (fire, flood, data-leak) if hacked.

#### TODO
- Avoid variable `$ -> v` and string `: -> t` identifier translation (2 codes spared)
- function must have end statement
- reset functions loops and registers states on reset
