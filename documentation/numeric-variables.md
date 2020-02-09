### Documentation
- [Configuration](/documentation/configuration.md)
- [Comments](/documentation/comments.md)
- [Conditions](/documentation/conditions.md)
- [Constants](/documentation/constants.md)
- [Cycles](/documentation/cycles.md)
  - [`for`](/documentation/cycles.md#for)
  - [`while`](/documentation/cycles.md#while)
- [Functions](/documentation/functions.md)
- **[Numeric variables](/documentation/numeric-variables.md)**
- [Operators](/documentation/operators.md)
- [Strings](/documentation/strings.md)
- [System functions](/documentation/system-functions.md)
- [Unary operators](/documentation/unary-operators.md)

## Numeric variables
BIPLAN supports only one numeric variable type that is by default `int32_t` but can be easily changed, see [configuration](/documentation/configuration.md). Numeric variables are identified by `$`, their name must be composed by lowercase and or uppercase letters and must not contain symbols or numbers. Each variable is just an entry of a global array of variables. BIPLAN supports a maximum amount of 116 global variables. Variables can be defined using a name:
```php
$test = 10
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
