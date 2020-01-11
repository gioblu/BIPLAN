## Functions
A function is a group of statements that together perform a task. It can be defined using the `function` keyword, defining its name and a parameter list delimited by parentheses used to define which variables are used for function computation. The variables used in the function's definition are set with the value passed by the call, when the function returns the global variable's value is restored.  Unlike many other programming languages only one `return` must be present and must be the last statement of the function definition, all statements contained in the function definition are be executed until `return` is encountered. The function definition must be placed after the `end` statement.   

```php
# Call
sum(1, 1)

end # must divide code to be executed from function definitions

# Definition
function sum($a, $b)
return $a + $b
```
Functions can contain more than one statement, but only one `return` statement can be used in each function and must be the last statement.
```php
# Call
print_sum(1, 1)

end

# Definition
function print_sum($a, $b)
  print "Sum: "
  print $a + $b
return
```

BIPLAN supports scoping only for variables part of the function parameters list, within functions it is possible to access all other variables globally.
```php
$a = 10
$b = 5

scope_test(2)
# Prints 10 2
print $b
# Prints 5

end # End of the program

# Definition
function scope_test($b)
  print $a
  print $b
return
```
