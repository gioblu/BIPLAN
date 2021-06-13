### Documentation
- [Configuration](/documentation/configuration.md)
- [Comments](/documentation/comments.md) [`#`](/documentation/comments.md)
- [Conditions](/documentation/conditions.md) [`if`](/documentation/conditions.md) [`else`](/documentation/conditions.md) [`end`](/documentation/conditions.md)
- [Constants](/documentation/constants.md) [`true`](/documentation/constants.md) [`false`](/documentation/constants.md) [`HIGH`](/documentation/constants.md) [`LOW`](/documentation/constants.md) [`INPUT`](/documentation/constants.md) [`OUTPUT`](/documentation/constants.md)
- [Cycles](/documentation/cycles.md) [`for`](/documentation/cycles.md#for) [`while`](/documentation/cycles.md#while) [`next`](/documentation/cycles.md#next) [`break`](/documentation/cycles.md#break) [`continue`](/documentation/cycles.md#continue)
- **[Functions](/documentation/functions.md)** [`function`](/documentation/functions.md) [`return`](/documentation/functions.md)
- [Numeric variables](/documentation/numeric-variables.md) [`$`](/documentation/numeric-variables.md) [`$[]`](/documentation/numeric-variables.md)
- [Operators](/documentation/operators.md) [`+`](/documentation/operators.md) [`-`](/documentation/operators.md) [`*`](/documentation/operators.md) [`/`](/documentation/operators.md) [`%`](/documentation/operators.md) [`==`](/documentation/operators.md) [`!=`](/documentation/operators.md) [`>`](/documentation/operators.md) [`>=`](/documentation/operators.md) [`<`](/documentation/operators.md) [`<=`](/documentation/operators.md) [`&&`](/documentation/operators.md) [`||`](/documentation/operators.md) [`&`](/documentation/operators.md) [`|`](/documentation/operators.md) [`^`](/documentation/operators.md) [`>>`](/documentation/operators.md) [`<<`](/documentation/operators.md) [`++`](/documentation/operators.md) [`--`](/documentation/operators.md) [`~`](/documentation/operators.md) [`not`](/documentation/operators.md)
- [Strings](/documentation/strings.md) [`:`](/documentation/strings.md) [`:[]`](/documentation/strings.md)
- [System functions](/documentation/system-functions.md) [`adc read`](/documentation/system-functions.md#adc-read) [`char`](/documentation/system-functions.md#print) [`delay`](/documentation/system-functions.md#delay) [`file close`](/documentation/system-functions.md#file-close) [`file open`](/documentation/system-functions.md#file-open) [`file read`](/documentation/system-functions.md#file-read) [`file write`](/documentation/system-functions.md#file-write) [`jump`](/documentation/system-functions.md#jump) [`io open`](/documentation/system-functions.md#io-open) [`io read`](/documentation/system-functions.md#io-read) [`io write`](/documentation/system-functions.md#digitalWrite) [`index`](/documentation/system-functions.md#index) [`input`](/documentation/system-functions.md#input) [`millis`](/documentation/system-functions.md#millis) [`print`](/documentation/system-functions.md#print) [`random`](/documentation/system-functions.md#random) [`restart`](/documentation/system-functions.md#restart) [`serial open`](/documentation/system-functions.md#serial-open) [`serial read`](/documentation/system-functions.md#serial-read) [`serial write`](/documentation/system-functions.md#serial-write) [`size`](/documentation/system-functions.md#size) [`sqrt`](/documentation/system-functions.md#sqrt) [`stop`](/documentation/system-functions.md#stop) [`system`](/documentation/system-functions.md#system)
- [Unary operators](/documentation/unary-operators.md) [`++`](/documentation/unary-operators.md) [`--`](/documentation/unary-operators.md)

## Functions
```
function [function name]([parameter], [parameter], ...)
  [statement]
return [expression]
```
A function is a group of statements that together perform a task and can return a value. It is important to take in consideration that the function's statements are executed recursively when the function is called, so at each call a certain overhead is pushed on the stack of the physical machine that is executing the interpreter. A function can be defined using the `function` keyword, defining its name and a parameter list delimited by parentheses used to define which variables are used for function computation. The variables used in the function's definition are set with the value passed by the call, when the function returns the global variable's value is restored. All statements contained in the function definition are executed until a `return` is encountered. The function definition must be placed after the `stop` statement. Each function is just an entry of a global array of functions. BIPLAN supports up to 92 functions.

```php
# Call
print sum(1, 1)

stop # end of the program

# Definition
function sum($a, $b)
return $a + $b
```
The following function `fibonacci` prints the Fibonacci series.
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
  return $n
```

BIPLAN supports scoping only for variables part of the function parameters list, within functions it is possible to access all other variables globally.
```php
$a = 10
$b = 5

scope_test(2) # Prints 10 2
print($b) # Prints 5

stop # end of the program

# Definition
function scope_test($b)
  print $a, " ", $b
return 0
```
