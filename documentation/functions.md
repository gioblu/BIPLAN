### Documentation
- [Configuration](/documentation/configuration.md)
- [Comments](/documentation/comments.md) [`#`]()  
- [Conditions](/documentation/conditions.md) [`if`]() [`else`]() [`end`]()
- [Constants](/documentation/constants.md) [`true`]() [`false`]() [`HIGH`]() [`LOW`]() [`INPUT`]() [`OUTPUT`]()
- [Cycles](/documentation/cycles.md) [`for`](/documentation/cycles.md#for) [`while`](/documentation/cycles.md#while) [`next`](/documentation/cycles.md#next) [`break`](/documentation/cycles.md#break) [`continue`](/documentation/cycles.md#continue)
- **[Functions](/documentation/functions.md)** [`function`]() [`return`]()
- [Numeric variables](/documentation/numeric-variables.md) [`$`]() [`$[]`]()
- [Operators](/documentation/operators.md) [`+`]() [`-`]() [`*`]() [`/`]() [`%`]() [`==`]() [`!=`]() [`>`]() [`>=`]() [`<`]() [`<=`]() [`&&`]() [`||`]() [`&`]() [`|`]() [`^`]() [`>>`]() [`<<`]() [`++`]() [`--`]() [`~`]() [`not`]()
- [Strings](/documentation/strings.md) [`:`]() [`:[]`]()
- [System functions](/documentation/system-functions.md) [`stop`]() [`restart`]() [`char`]() [`sizeof`]() [`print`]() [`delay`]() [`random`]() [`millis`]() [`sqrt`]() [`analogRead`]() [`digitalRead`]() [`digitalWrite`]() [`pinMode`]() [`serialAvailable`]() [`serialRead`]() [`serialWrite`]() [`input`]() [`inputAvailable`]()
- [Unary operators](/documentation/unary-operators.md) [`++`]() [`--`]()

## Functions
```
function [function name]([parameter], [parameter])
  [statement]
return [expression]
```
A function is a group of statements that together perform a task and can return a value. It is important to take in consideration that the function's statements are executed recursively when the function is called, so at each call a certain overhead is pushed on the stack of the physical machine that is executing the interpreter. A function can be defined using the `function` keyword, defining its name and a parameter list delimited by parentheses used to define which variables are used for function computation. The variables used in the function's definition are set with the value passed by the call, when the function returns the global variable's value is restored. All statements contained in the function definition are be executed until a `return` is encountered. The function definition must be placed after the `stop` statement.   

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
return 0
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
