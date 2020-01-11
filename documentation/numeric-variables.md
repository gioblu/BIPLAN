
## Numeric variables
BIPLAN supports only one numeric variable type that is by default `int32_t` but can be easily changed:   
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
BIPLAN supports a maximum amount of 116 global variables. Variables can be defined as follows:
```php

$test 0     # Concise
$test = 2   # Less concise
$test = 10; # Even less, like php
```
Variables can be accessed by name:
```php
print $test   # Concise
print($test)  # Less concise
print($test); # Even less, like php
# Prints "10"
```
Variables can be accessed by reference passing a numeric variable:
```php
$test = 10
print $>0 # Access the first variable
# Prints "10" (value of the first variable defined in the program)
```
or passing another variable:
```php
$a =  1
$b = 15
print $>$a # Access second variable
# Prints "15" (value of the second variable defined in the program)
```
