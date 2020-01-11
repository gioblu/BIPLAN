
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
