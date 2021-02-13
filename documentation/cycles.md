### Documentation
- [Configuration](/documentation/configuration.md)
- [Comments](/documentation/comments.md) [`#`](/documentation/comments.md)
- [Conditions](/documentation/conditions.md) [`if`](/documentation/conditions.md) [`else`](/documentation/conditions.md) [`end`](/documentation/conditions.md)
- [Constants](/documentation/constants.md) [`true`](/documentation/constants.md) [`false`](/documentation/constants.md) [`HIGH`](/documentation/constants.md) [`LOW`](/documentation/constants.md) [`INPUT`](/documentation/constants.md) [`OUTPUT`](/documentation/constants.md)
- **[Cycles](/documentation/cycles.md)** [`for`](/documentation/cycles.md#for) [`while`](/documentation/cycles.md#while) [`break`](/documentation/cycles.md#break) [`continue`](/documentation/cycles.md#continue)
- [Functions](/documentation/functions.md) [`function`](/documentation/functions.md) [`return`](/documentation/functions.md)
- [Numeric variables](/documentation/numeric-variables.md) [`$`](/documentation/numeric-variables.md) [`$[]`](/documentation/numeric-variables.md)
- [Operators](/documentation/operators.md) [`+`](/documentation/operators.md) [`-`](/documentation/operators.md) [`*`](/documentation/operators.md) [`/`](/documentation/operators.md) [`%`](/documentation/operators.md) [`==`](/documentation/operators.md) [`!=`](/documentation/operators.md) [`>`](/documentation/operators.md) [`>=`](/documentation/operators.md) [`<`](/documentation/operators.md) [`<=`](/documentation/operators.md) [`&&`](/documentation/operators.md) [`||`](/documentation/operators.md) [`&`](/documentation/operators.md) [`|`](/documentation/operators.md) [`^`](/documentation/operators.md) [`>>`](/documentation/operators.md) [`<<`](/documentation/operators.md) [`++`](/documentation/operators.md) [`--`](/documentation/operators.md) [`~`](/documentation/operators.md) [`not`](/documentation/operators.md)
- [Strings](/documentation/strings.md) [`:`](/documentation/strings.md) [`:[]`](/documentation/strings.md)
- [System functions](/documentation/system-functions.md) [`stop`](/documentation/system-functions.md#stop) [`restart`](/documentation/system-functions.md#restart) [`char`](/documentation/system-functions.md#print) [`sizeof`](/documentation/system-functions.md#sizeof) [`print`](/documentation/system-functions.md#print) [`delay`](/documentation/system-functions.md#delay) [`random`](/documentation/system-functions.md#random) [`millis`](/documentation/system-functions.md#millis) [`sqrt`](/documentation/system-functions.md#sqrt) [`analogRead`](/documentation/system-functions.md#analogRead) [`digitalRead`](/documentation/system-functions.md#digitalRead) [`digitalWrite`](/documentation/system-functions.md#digitalWrite) [`pinMode`](/documentation/system-functions.md#pinMode) [`serialRead`](/documentation/system-functions.md#serialRead) [`serialWrite`](/documentation/system-functions.md#serialWrite) [`input`](/documentation/system-functions.md#input) [`index`](/documentation/system-functions.md#index) [`jump`](/documentation/system-functions.md#jump)
- [Unary operators](/documentation/unary-operators.md) [`++`](/documentation/unary-operators.md) [`--`](/documentation/unary-operators.md)

## `for`
```
for [variable assignment] to [expression] step [expression]
  [statement]
next
```
The `for` is a cycle that supports a single local variable that can be set with an initial value and a limit value that is specified after `to`:  
```php
for $i = 0 to 5
  print $i
next

# Prints 0, 1, 2, 3, 4, 5
```
In the example above `$i` is locally declared with a value of 0 and it will be incremented by 1 at each cycle. The `for` iterates the local variable up or down to the desired limit in both directions:
```php
for $i = 5 to 0
  print $i
next

# Prints 5, 4, 3, 2, 1, 0
```
Each time `next` is encountered the variable is incremented or decremented by 1 and the cycle restart if the limit defined after the `to` is not reached. Consider that `for`, unlike `for` defined by other programming languages, evaluates and caches the limit the first time the `for` statement is encountered. For this reason the `for` is a quick iterator, if you need to conditionally exit from a loop use `while` instead.

#### `step`
Optionally the `for` the increment or decrement value can be configured after `step`:  
```php
for $i = 0 to 10 step 2
  print $i
next

# Prints 0, 2, 4, 6, 8, 10
```

---

#### `break`
The BIPLAN `for` supports the `break` statement as other programming languages do:
```php
for $i = 0 to 5
  if $i == 2 break end
  print $i
next
print "Finished"

# Prints 0, 1, Finished
```
When the `break` statement is encountered within a `for`, the iteration is interrupted and all following statements part of the `for` are ignored.

#### `continue`
The BIPLAN `for` supports the `continue` statement as other programming languages do:
```php
for $i = 0 to 5
  if $i == 2 continue end
  print $i
next
print "Finished"

# Prints 0, 1, 3, 4, 5, Finished
```
When the `continue` statement is encountered within a `for`, all following statements part of the `for` are ignored and the next iteration is initiated.

---

## `while`
```
while [condition]
  [statement]
next
```
The `while` statement, if the condition is truthy, forces the cyclical execution of the following statements until a `next` statement is encountered.   
```php
while digitalRead 12 == HIGH
  print "The pin is HIGH"
next

# Prints The pin is HIGH until pin 12 is HIGH
```

#### `break`
The BIPLAN `while` supports the `break` statement as other programming languages do:
```php
while true
  if digitalRead 12 == HIGH
    break
  end
next
print "Button pressed!"

# Prints Button pressed when pin 12 is HIGH
```
When the `break` statement is encountered within a `for`, the iteration is interrupted and all following statements part of the `for` are ignored.

#### `continue`
The BIPLAN `while` supports the `continue` statement as other programming languages do:
```php
$treshold = 512
while true
  if analogRead A0 > $treshold
    continue
  else
    print "Alert"
  end
next

# Prints Alert if the reading is less than $treshold
```
When the `continue` statement is encountered within a `for`, all following statements part of the `for` are ignored and the next iteration is initiated.
