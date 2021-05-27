### Documentation
- [Configuration](/documentation/configuration.md)
- [Comments](/documentation/comments.md) [`#`](/documentation/comments.md)
- [Conditions](/documentation/conditions.md) [`if`](/documentation/conditions.md) [`else`](/documentation/conditions.md) [`end`](/documentation/conditions.md)
- [Constants](/documentation/constants.md) [`true`](/documentation/constants.md) [`false`](/documentation/constants.md) [`HIGH`](/documentation/constants.md) [`LOW`](/documentation/constants.md) [`INPUT`](/documentation/constants.md) [`OUTPUT`](/documentation/constants.md)
- [Cycles](/documentation/cycles.md) [`for`](/documentation/cycles.md#for) [`while`](/documentation/cycles.md#while) [`next`](/documentation/cycles.md#next) [`break`](/documentation/cycles.md#break) [`continue`](/documentation/cycles.md#continue)
- [Functions](/documentation/functions.md) [`function`](/documentation/functions.md) [`return`](/documentation/functions.md)
- [Numeric variables](/documentation/numeric-variables.md) [`$`](/documentation/numeric-variables.md) [`$[]`](/documentation/numeric-variables.md)
- [Operators](/documentation/operators.md) [`+`](/documentation/operators.md) [`-`](/documentation/operators.md) [`*`](/documentation/operators.md) [`/`](/documentation/operators.md) [`%`](/documentation/operators.md) [`==`](/documentation/operators.md) [`!=`](/documentation/operators.md) [`>`](/documentation/operators.md) [`>=`](/documentation/operators.md) [`<`](/documentation/operators.md) [`<=`](/documentation/operators.md) [`&&`](/documentation/operators.md) [`||`](/documentation/operators.md) [`&`](/documentation/operators.md) [`|`](/documentation/operators.md) [`^`](/documentation/operators.md) [`>>`](/documentation/operators.md) [`<<`](/documentation/operators.md) [`++`](/documentation/operators.md) [`--`](/documentation/operators.md) [`~`](/documentation/operators.md) [`not`](/documentation/operators.md)
- [Strings](/documentation/strings.md) [`:`](/documentation/strings.md) [`:[]`](/documentation/strings.md)
- [System functions](/documentation/system-functions.md) [`stop`](/documentation/system-functions.md#stop) [`restart`](/documentation/system-functions.md#restart) [`char`](/documentation/system-functions.md#print) [`sizeof`](/documentation/system-functions.md#sizeof) [`print`](/documentation/system-functions.md#print) [`delay`](/documentation/system-functions.md#delay) [`random`](/documentation/system-functions.md#random) [`millis`](/documentation/system-functions.md#millis) [`sqrt`](/documentation/system-functions.md#sqrt) [`analogRead`](/documentation/system-functions.md#analogRead) [`digitalRead`](/documentation/system-functions.md#digitalRead) [`digitalWrite`](/documentation/system-functions.md#digitalWrite) [`pinMode`](/documentation/system-functions.md#pinMode) [`serialRead`](/documentation/system-functions.md#serialRead) [`serialWrite`](/documentation/system-functions.md#serialWrite) [`input`](/documentation/system-functions.md#input) [`index`](/documentation/system-functions.md#index) [`jump`](/documentation/system-functions.md#jump)
- **[Unary operators](/documentation/unary-operators.md)** [`++`](/documentation/unary-operators.md) [`--`](/documentation/unary-operators.md)


## Unary operators
BIPLAN supports prefix increment and decrement unary operators. Prefix unary operators are used to increment or decrement its operand. The increment operator `++` adds 1, the decrement operator `--` subtracts 1. Both `++` and `--` can be used as prefix operators (before the operand: `++v`). For example `++v` increments the value of `v` before it is used.

Prefix unary operators in statement must be used only when incrementing or decrementing variables:
```php
$a = 0
print ++$a
# Prints "1" and sets a = 1 in memory
```
BIPLAN unary operators can be chained:

```php
$a = 0
print ++++$a
# Sets a = 2 in memory and prints "2"

$a = 1
print ----$a
# Sets a = -1 in memory and prints "-1" 
```
