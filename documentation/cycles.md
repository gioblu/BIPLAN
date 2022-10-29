### Documentation
- [Configuration](/documentation/configuration.md)
- [Comments](/documentation/comments.md) [`#`](/documentation/comments.md)
- [Conditions](/documentation/conditions.md) [`if`](/documentation/conditions.md) [`else`](/documentation/conditions.md) [`end`](/documentation/conditions.md)
- [Constants](/documentation/constants.md) [`true`](/documentation/constants.md) [`false`](/documentation/constants.md) [`HIGH`](/documentation/constants.md) [`LOW`](/documentation/constants.md) [`INPUT`](/documentation/constants.md) [`OUTPUT`](/documentation/constants.md)
- **[Cycles](/documentation/cycles.md)** [`for`](/documentation/cycles.md#for) [`while`](/documentation/cycles.md#while) [`break`](/documentation/cycles.md#break) [`continue`](/documentation/cycles.md#continue)
- [Functions](/documentation/functions.md) [`function`](/documentation/functions.md) [`locals`](/documentation/functions.md) [`result`](/documentation/functions.md) [`return`](/documentation/functions.md)
- [Macros](/documentation/macros.md) [`macro`](/documentation/macros.md#pre-processor-macros)
- [Numeric variables](/documentation/numeric-variables.md) [`@`](/documentation/numeric-variables.md) [`@[]`](/documentation/numeric-variables.md)
- [Operators](/documentation/operators.md) [`+`](/documentation/operators.md) [`-`](/documentation/operators.md) [`*`](/documentation/operators.md) [`/`](/documentation/operators.md) [`%`](/documentation/operators.md) [`==`](/documentation/operators.md) [`!=`](/documentation/operators.md) [`>`](/documentation/operators.md) [`>=`](/documentation/operators.md) [`<`](/documentation/operators.md) [`<=`](/documentation/operators.md) [`&&`](/documentation/operators.md) [`||`](/documentation/operators.md) [`&`](/documentation/operators.md) [`|`](/documentation/operators.md) [`^`](/documentation/operators.md) [`>>`](/documentation/operators.md) [`<<`](/documentation/operators.md) [`++`](/documentation/operators.md) [`--`](/documentation/operators.md) [`~`](/documentation/operators.md) [`not`](/documentation/operators.md)
- [Strings](/documentation/strings.md) [`:`](/documentation/strings.md) [`:[]`](/documentation/strings.md)
- [System functions](/documentation/system-functions.md) [`adc read`](/documentation/system-functions.md#adc-read) [`args`](/documentation/system-functions.md#args) [`char`](/documentation/system-functions.md#print) [`cursor`](/documentation/system-functions.md#cursor) [`delay`](/documentation/system-functions.md#delay) [`file close`](/documentation/system-functions.md#file-close) [`file open`](/documentation/system-functions.md#file-open) [`file read`](/documentation/system-functions.md#file-read) [`file write`](/documentation/system-functions.md#file-write) [`include`](/documentation/system-functions.md#include) [`index`](/documentation/system-functions.md#index) [`input`](/documentation/system-functions.md#input) [`io open`](/documentation/system-functions.md#io-open) [`io read`](/documentation/system-functions.md#io-read) [`io write`](/documentation/system-functions.md#digitalWrite) [`jump`](/documentation/system-functions.md#jump) [`label`](/documentation/system-functions.md#label) [`millis`](/documentation/system-functions.md#millis) [`number`](/documentation/system-functions.md#number) [`numeric`](/documentation/system-functions.md#numeric) [`print`](/documentation/system-functions.md#print) [`random`](/documentation/system-functions.md#random) [`restart`](/documentation/system-functions.md#restart) [`serial open`](/documentation/system-functions.md#serial-open) [`serial read`](/documentation/system-functions.md#serial-read) [`serial write`](/documentation/system-functions.md#serial-write) [`size`](/documentation/system-functions.md#size) [`sqrt`](/documentation/system-functions.md#sqrt) [`stop`](/documentation/system-functions.md#stop) [`string`](/documentation/system-functions.md#string) [`system`](/documentation/system-functions.md#system)
- [Unary operators](/documentation/unary-operators.md) [`++`](/documentation/unary-operators.md) [`--`](/documentation/unary-operators.md)

## `for`
```
for [variable assignment] to [expression] step [expression]
  [statement]
next
```
The `for` is a cycle that supports a single local variable identified by `#` that can be set with an initial value and a limit value that is specified after `to`:  
```c
for #i = 0 to 5
  print #i
next

// Prints 0, 1, 2, 3, 4
```
In the example above `#i` is locally declared with a value of 0 and it will be incremented by 1 at each cycle. The `for` iterates the local variable up or down to the desired limit in both directions:
```c
for #i = 5 to 0
  print #i
next

// Prints 5, 4, 3, 2, 1
```
Each time `next` is encountered the variable is incremented or decremented by 1 and the cycle restarts if the limit defined after the `to` is not reached. Consider that `for`, unlike `for` defined by other programming languages, evaluates and computes the limit the first time the `for` statement is encountered. For this reason the `for` is a quick iterator, if you need to conditionally exit from a loop use `while` instead.

#### `step`
Optionally the `for` the increment or decrement value can be configured after `step`:  
```c
for #i = 0 to 10 step 2
  print #i
next

// Prints 0, 2, 4, 6, 8
```

#### `break`
The BIPLAN `for` supports `break` as other programming languages do:
```c
for #i = 0 to 5
  if #i == 2 break end
  print #i
next
print "Finished"

// Prints 0, 1, Finished
```
When `break` is encountered within a `for`, the iteration is interrupted and all following statements part of the `for` are ignored.

#### `continue`
The BIPLAN `for` supports `continue` as other programming languages do:
```c
for #i = 0 to 5
  if #i == 2 continue end
  print #i
next
print "Finished"

// Prints 0, 1, 3, 4, Finished
```
When `continue` is encountered within a `for`, all following statements part of the `for` are ignored and the next iteration is initiated.

---

## `while`
```
while [condition]
  [statement]
next
```
The `while` statement, if the condition is truthy, forces the cyclical execution of the following statements until `next` is encountered.   
```c
while io read 12 == HIGH
  print "The pin is HIGH"
next

// Prints The pin is HIGH until pin 12 is HIGH
```

#### `break`
The BIPLAN `while` supports `break` as other programming languages do:
```c
while true
  if io read 12 == HIGH
    break
  end
next
print "Button pressed!"

// Prints Button pressed when pin 12 is HIGH
```
When `break` is encountered within a `for`, the iteration is interrupted and all following statements part of the `for` are ignored.

#### `continue`
The BIPLAN `while` supports `continue` as other programming languages do:
```c
@treshold = 512
while true
  if adc read A0 > @treshold
    continue
  else
    print "Alert"
  end
next

// Prints Alert if the reading is less than 512
```
When `continue` is encountered within a `for`, all following statements part of the `for` are ignored and the next iteration is initiated.
