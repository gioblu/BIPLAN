### Documentation
- [Configuration](/documentation/configuration.md)
- [Comments](/documentation/comments.md) [`#`]()  
- **[Conditions](/documentation/conditions.md)** [`if`](/documentation/conditions.md) [`else`](/documentation/conditions.md) [`end`](/documentation/conditions.md)
- [Constants](/documentation/constants.md) [`true`]() [`false`]() [`HIGH`]() [`LOW`]() [`INPUT`]() [`OUTPUT`]()
- [Cycles](/documentation/cycles.md) [`for`](/documentation/cycles.md#for) [`while`](/documentation/cycles.md#while) [`next`](/documentation/cycles.md#next) [`break`](/documentation/cycles.md#break) [`continue`](/documentation/cycles.md#continue)
- [Functions](/documentation/functions.md) [`function`]() [`return`]()
- [Numeric variables](/documentation/numeric-variables.md) [`$`]() [`$[]`]()
- [Operators](/documentation/operators.md) [`+`]() [`-`]() [`*`]() [`/`]() [`%`]() [`==`]() [`!=`]() [`>`]() [`>=`]() [`<`]() [`<=`]() [`&&`]() [`||`]() [`&`]() [`|`]() [`^`]() [`>>`]() [`<<`]() [`++`]() [`--`]() [`~`]() [`not`]()
- [Strings](/documentation/strings.md) [`:`]() [`:[]`]()
- [System functions](/documentation/system-functions.md) [`stop`]() [`restart`]() [`char`]() [`sizeof`]() [`print`]() [`delay`]() [`random`]() [`millis`]() [`sqrt`]() [`analogRead`]() [`digitalRead`]() [`digitalWrite`]() [`pinMode`]() [`serialAvailable`]() [`serialRead`]() [`serialWrite`]() [`input`]() [`inputAvailable`]() [`index`]() [`known`]()
- [Unary operators](/documentation/unary-operators.md) [`++`]() [`--`]()

# Conditions
```
if [relation] [statement] end

if [relation] [statement]
else [statement] end

if [relation]
  [statement]
end

if [relation]
  [statement]
else
  [statement]
end
```
An `if`, if its condition is truthy, executes the following statements until `end` is encountered, otherwise it executes the statements that follow the next `else` until `end` is encountered. It is used where code needs to be executed only if a given condition is true. An `if` or `else` statement can execute a single statement and fit in a single line:
```php
$fine = true
if $fine print "All is fine!" end

# Or

if not $fine print "Some error occurred"
else print "All is fine!" end
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
end
```
