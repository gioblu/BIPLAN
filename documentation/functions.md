### Documentation
- [Bytecode](/documentation/bytecode.md)
- [Configuration](/documentation/configuration.md)
- [Comments](/documentation/comments.md) [`//`](/documentation/comments.md)
- [Conditions](/documentation/conditions.md) [`if`](/documentation/conditions.md) [`else`](/documentation/conditions.md) [`end`](/documentation/conditions.md)
- [Constants](/documentation/constants.md) [`true`](/documentation/constants.md) [`false`](/documentation/constants.md) [`HIGH`](/documentation/constants.md) [`LOW`](/documentation/constants.md) [`INPUT`](/documentation/constants.md) [`OUTPUT`](/documentation/constants.md)
- [Cycles](/documentation/cycles.md) [`for`](/documentation/cycles.md#for) [`while`](/documentation/cycles.md#while) [`next`](/documentation/cycles.md#next) [`break`](/documentation/cycles.md#break) [`continue`](/documentation/cycles.md#continue)
- **[Functions](/documentation/functions.md)** [`function`](/documentation/functions.md) [`locals`](/documentation/functions.md) [`return`](/documentation/functions.md)
- [Macros](/documentation/macros.md) [`macro`](/documentation/macros.md#pre-processor-macros)
- [Numeric variables](/documentation/numeric-variables.md) [`@`](/documentation/numeric-variables.md) [`@[]`](/documentation/numeric-variables.md)
- [Operators](/documentation/operators.md) [`+`](/documentation/operators.md) [`-`](/documentation/operators.md) [`*`](/documentation/operators.md) [`/`](/documentation/operators.md) [`%`](/documentation/operators.md) [`==`](/documentation/operators.md) [`!=`](/documentation/operators.md) [`>`](/documentation/operators.md) [`>=`](/documentation/operators.md) [`<`](/documentation/operators.md) [`<=`](/documentation/operators.md) [`&&`](/documentation/operators.md) [`||`](/documentation/operators.md) [`&`](/documentation/operators.md) [`|`](/documentation/operators.md) [`^`](/documentation/operators.md) [`>>`](/documentation/operators.md) [`<<`](/documentation/operators.md) [`++`](/documentation/operators.md) [`--`](/documentation/operators.md) [`~`](/documentation/operators.md) [`not`](/documentation/operators.md)
- [Strings](/documentation/strings.md) [`:`](/documentation/strings.md) [`:[]`](/documentation/strings.md)
- [System functions](/documentation/system-functions.md) [`adc read`](/documentation/system-functions.md#adc-read) [`args`](/documentation/system-functions.md#args) [`char`](/documentation/system-functions.md#print) [`cursor`](/documentation/system-functions.md#print) [`delay`](/documentation/system-functions.md#delay) [`file close`](/documentation/system-functions.md#file-close) [`file open`](/documentation/system-functions.md#file-open) [`file read`](/documentation/system-functions.md#file-read) [`file write`](/documentation/system-functions.md#file-write) [`include`](/documentation/system-functions.md#include) [`index`](/documentation/system-functions.md#index) [`input`](/documentation/system-functions.md#input) [`io open`](/documentation/system-functions.md#io-open) [`io read`](/documentation/system-functions.md#io-read) [`io write`](/documentation/system-functions.md#digitalWrite) [`mem`](/documentation/system-functions.md#mem)  [`millis`](/documentation/system-functions.md#millis) [`number`](/documentation/system-functions.md#number) [`numeric`](/documentation/system-functions.md#numeric) [`print`](/documentation/system-functions.md#print) [`random`](/documentation/system-functions.md#random) [`restart`](/documentation/system-functions.md#restart) [`serial open`](/documentation/system-functions.md#serial-open) [`serial read`](/documentation/system-functions.md#serial-read) [`serial write`](/documentation/system-functions.md#serial-write) [`size`](/documentation/system-functions.md#size)  [`stop`](/documentation/system-functions.md#stop) [`string`](/documentation/system-functions.md#string) [`system`](/documentation/system-functions.md#system)
- [Unary operators](/documentation/unary-operators.md) [`++`](/documentation/unary-operators.md) [`--`](/documentation/unary-operators.md)

## Functions
```
function [name]([parameter], [parameter], locals: [parameter], [parameter])
  [statement]
return [expression]
```
A function is a group of statements identified by a unique name that together perform a task and can return a value. Each function is just an entry of a global array of up to 88 functions, each function stores up to 88 parameters and local variables. A function can be defined using the `function` keyword, defining its name and a parameters' list delimited by parentheses used to define which variables are used for function computation. The parameters listed in the function's definition are identified by `$` and are set with the value passed by the call.

```c
// Call
print sum(1, 1)

stop // end of the program

// Definition
function sum($a, $b)
return $a + $b
```

All statements contained in the function definition are executed until `return` is encountered. The `return` statement must be one and must be the last statement of the function. Function definitions must be placed after `stop`.

The following function `fibonacci` prints the Fibonacci series. As you can see the local variables must be defined along with the function parameters after the `locals:` keyword. The value of uninitialized parameters and local variables is guaranteed to be `0`.
```c
fibonacci(10) // Prints 0 1 1 2 3 5 8

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

Functions receive numeric parameters, each parameter can represent a numeric value, a reference to a variable or a reference to a string:

```c
:test = "test"

@result = cap(index :test)

print :[@result], " ", :test // Prints "Test Test"

stop

function cap($s)
  :[$s][0] = 'T'
return $s
```

In the example above the reference to the string `:test` is passed to the `cap` function. The reference is then used to modify the first character. 