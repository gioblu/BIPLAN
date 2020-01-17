### Documentation
- [Configuration](/documentation/configuration.md)
- [Comments](/documentation/comments.md)
- [Conditions](/documentation/conditions.md)
- [Constants](/documentation/constants.md)
- **[Cycles](/documentation/cycles.md)**
- [Functions](/documentation/functions.md)
- [Numeric variables](/documentation/numeric-variables.md)
- [Operators](/documentation/operators.md)
- [Strings](/documentation/strings.md)
- [System functions](/documentation/system-functions.md)
- [Unary operators](/documentation/unary-operators.md)

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

The `while` statement, if the condition is truthy, forces the cyclical execution of the following statements until a `next` statement is encountered.   
```php
$i = 0
while $i++ < 10
  if $i == 4 continue
  if $i == 5 break
  print $i
next

# Prints 1, 2, 3
```
