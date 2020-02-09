### Documentation
- [Configuration](/documentation/configuration.md)
- [Comments](/documentation/comments.md)
- [Conditions](/documentation/conditions.md)
- [Constants](/documentation/constants.md)
- [Cycles](/documentation/cycles.md)
  - [`for`](/documentation/cycles.md#for)
  - [`while`](/documentation/cycles.md#while)
- [Functions](/documentation/functions.md)
- [Numeric variables](/documentation/numeric-variables.md)
- [Operators](/documentation/operators.md)
- [Strings](/documentation/strings.md)
- [System functions](/documentation/system-functions.md)
- **[Unary operators](/documentation/unary-operators.md)**

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
