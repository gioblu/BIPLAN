
## Conditions
An `if` executes the given statement if its condition is truthy, otherwise, it executes the following `else` statement if present. It is used where code needs to be executed only if a given condition is true. An `if` or `else` statement can execute a single statement:
```php
if 1 == 1 print "All fine"
else print "Some error occurred"
```
or can also conditionally execute a block of statements:
```php
# Condition block

if 1 == 1 {
  print "All is"
  print " fine."
} else {
  print "Some error occurred"
  print "!!!"
}
```
