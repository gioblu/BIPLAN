### Documentation
- [Configuration](/documentation/configuration.md)
- [Comments](/documentation/comments.md)
- [Conditions](/documentation/conditions.md)
- [Constants](/documentation/constants.md)
- [Cycles](/documentation/cycles.md)
- **[Functions](/documentation/functions.md)**
- [Numeric variables](/documentation/numeric-variables.md)
- [Operators](/documentation/operators.md)
- [Strings](/documentation/strings.md)
- [System functions](/documentation/system-functions.md)
- [Unary operators](/documentation/unary-operators.md)

## Functions
A function is a group of statements that together perform a task. It can be defined using the `function` keyword, defining its name and a parameter list delimited by parentheses used to define which variables are used for function computation. The variables used in the function's definition are set with the value passed by the call, when the function returns the global variable's value is restored. All statements contained in the function definition are be executed until a `return` is encountered. The function definition must be placed after the `end` statement.   

```php
# Call
print sum(1, 1)

end # end of the program

# Definition
function sum($a, $b)
return $a + $b
```
Functions can contain more than one statement, but only one `return` statement can be used in each function and must be the last statement.
```php
# Call
print_sum(1, 1)

end # end of the program

# Definition
function print_sum($a, $b)
  print "Sum: "
  print $a + $b
return

# Prints Sum: 2
```

BIPLAN supports scoping only for variables part of the function parameters list, within functions it is possible to access all other variables globally.
```php
$a = 10
$b = 5

scope_test(2) # Prints 10 2
print $b # Prints 5

end # end of the program

# Definition
function scope_test($b)
  print $a
  print $b
return
```
