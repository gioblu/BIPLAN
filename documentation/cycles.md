
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
redo

# Prints 1, 2, 3
```
