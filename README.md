
# BIPLAN v0.0
BIPLAN (Byte-coded Interpreted Programming Language) is an experimental programming language based on a recursive descent parser that uses only static memory allocation and operates a completely software-defined architecture that does not require a garbage collector.

| Programming language | Minimum requirements |
| -------------------- | -------------------- |
| TinyBasicPlus        |  11KB ROM,  1KB RAM  |
| BIPLAN               |  12KB ROM,  1KB RAM  |
| MycroPython          | 256KB ROM, 16KB RAM  |
| Lua                  | 256KB ROM, 64kB RAM  |

BIPLAN comes with a modern syntax inspired by Ruby on Rails and Python and it is expressly designed to operate efficiently on microcontrollers with limited resources although its implementation is designed to be easily extended and applied in other architectures or real time operative systems.

## Constants

| Constant   | Value                       |
| ---------- | --------------------------- |
| `false`    | or `0`                      |
| `true`     | or `1`                      |
| `LOW`      | or `0` digital pin state    |
| `HIGH`     | or `1` digital pin state    |
| `INPUT`    | or `0` digital pin mode     |
| `OUTPUT`   | or `1` digital pin mode     |

## System functions

| BIP code | BIPLAN function     | Purpose                                                |
| -------- | ------------------- | ------------------------------------------------------ |
|  `x`     | `end`               | End program                                            |
|  `r`     | `restart`           | Restart program                                        |
|  `b`     | `char`              | Converts to char                                       |
|  `m`     | `sizeof`            | Returns the length of the trailing string or variable  |
|  `\`     | `print`             | Prints data                                            |
|  `D`     | `delay`             | Pauses the program for n milliseconds                  |
|  `R`     | `random`            | Generates pseudo-random number                         |
|  `M`     | `millis`            | Returns the number of milliseconds since start up      |
|  `s`     | `sqrt`              | Calculates the square root of a number                 |
|  `J`     | `analogRead`        | Reads the value from the specified analog pin          |
|  `G`     | `digitalRead`       | Reads the value from a specified digital pin           |
|  `E`     | `digitalWrite`      | Sets the state to a digital pin                        |
|  `P`     | `pinMode`           | Configures the pin mode of a digital pin               |
|  `a`     | `serialAvailable`   | Check if input data is available                       |
|  `c`     | `serialRead`        | Get one character of input data                        |
|  `g`     | `serialWrite`       | Write one character to serial port                     |
|  `e`     | `input`             | Receive data                                           |
|  `i`     | `inputAvailable`    | Check if data is available                             |

## Operators

| Arithmetic         | Logic                 | Bitwise          | Unary prefix             |  Unary postfix          |
| ------------------ | --------------------- | ---------------- | ------------------------ | ----------------------- |
| `+` Addition       | `==` Equal            | `&` And          | `++`  Increment then use | `++` use then increment |
| `-` Subtraction    | `!=` Not equal        | `\|` Or           | `--`  Decrement then use | `--` use then decrement |
| `*` Multiplication | `<`  Less             | `^` Xor          | `~`   Bitwise not        |                         |
| `/` Division       | `<=` Less or equal    | `<<` Left shift  | `not` Logic not          |                         |
| `%` Modulus        | `>`  Greater          | `>>` Right shift |                          |                         |
|                    | `>=` Greater or equal |                  |                          |                         |
|                    | `&&` And              |                  |                          |                         |
|                    | `\|\|` Or               |                  |                          |                         |

## Unary operators
BIPLAN supports prefix and postfix increment and decrement unary operators. Prefix unary operators are used to increment or decrement its operand. The increment operator `++` adds 1, the decrement operator `--` subtracts 1. Both `++` and `--` can be used either as prefix operators (before the operand: `++v`) or postfix operators (after the operand: `v++`). For example `++v` increments the value of `v` before it is used, while `v++` increments the value of `v` after it is used.

Prefix unary operators in statement must be used only when incrementing or decrementing variables:
```php
$a = 0
print ++$a
# Prints "1" and sets a = 1 in memory

$a = 0
print $a++
# Prints "0" and sets a = 1 in memory
```
BIPLAN unary operators can be chained:

```php
$a = 0
print ++$a++
# Prints "1" and sets a = 2 in memory

$a = 1
print --$a++
# Prints "0" and sets a = 1 in memory

$a = 0
print ++++$a
# Prints "2" and sets a = 2 in memory

$a = 10
print ++$a----
# Prints "11" and sets a = 9 in memory
```

## Comments
Comments are human-readable notes present in the source-code. They will be ignored by the compiler. The `#` symbol signals the start of a comment. A comment can make use of an entire line:
```php
# This is a comment
```
or can be placed after a statement:
```php
print "Hello world!" # This is another comment
```

## Conditions
An `if` executes the given statement if its condition is truthy, otherwise, it executes the following `else` statement if present. It is used where code needs to be executed only if a given condition is true. An `if` or `else` statement can execute a single statement and fit in a single line:
```php
if 1 == 1 print "All is fine!" endif

# Or

if 1 == 0 print "Some error occurred"
else print "All is fine!" endif
```
or can also conditionally execute a group of statements:
```php
# Condition block

if 1 == 1
  print "All is fine!"
  print "Equality works"
else
  print "Some error occurred!"
  print "Equality does not work"
endif
```

## Numeric variables
BIPLAN supports only one numeric variable type that is by default `int32_t` but can be easily changed, see [configuration]():   
```cpp
// Sets the BIPLAN numeric type to uint32_t
#define BP_VAR_TYPE uint32_t
#include "BIPLAN.h"
```
Numeric variables are identified by `$`, their name must be composed by lowercase and or uppercase letters and must not contain symbols or numbers. Each variable is just an entry of a global array of variables. The `BP_VARIABLES` constant can be used as shown below to configure the maximum amount of variables available:
```cpp
#define BP_VARIABLES 50
#include "BIPLAN.h"
```
BIPLAN supports a maximum amount of 116 global variables. Variables can be defined using a name:
```php
$test = 2
```
Variables can be accessed by name:
```php
print $test # Prints "10"
```
Variables can be accessed by reference, enabling the user to access all global strings as one big array:
```php
$test = 10
print $[0] # Access the first variable
# Prints "10" (value of the first variable defined in the program)
```

## Strings
String are identified by `:`, their name must be composed by lowercase and or uppercase letters and must not contain symbols or numbers. Each string is just an entry of a global array of strings.
```php
:test = "Hello world!"
```
String can be accessed by name:
```php
print :test
# Prints "Hello world!"
```
String can be accessed by reference treating all global strings as entries of an array:
```php
print :[0]
# Prints "Hello world!" or value of test (first string defined in the program)
```
Characters of strings can be accessed as shown below:
```php
:test = "Hello world!"
print :test[0]
# Prints "H"
```

## Cycles
BIPLAN supports cycles with the `for` and `while` statements.

The `for` statement is a loop that supports a single local variable:

```php
for $i = 0 to 5
  if $i == 2 continue
  if $i == 5 break
  print $i
next

# Prints 0, 1, 3, 4
```

The `while` statement, if the condition is truthy, forces the cyclical execution of the following statements until a `redo` statement is encountered.   
```php
$i = 0
while $i++ < 5
  if $i == 4 continue
  if $i == 5 break
  print $i++
next

# Prints 1, 2, 3
```

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


- REMOVE CR
- next - redo becomes only next
- function must have end statement
- reset variable functions loops and registers states on reset
