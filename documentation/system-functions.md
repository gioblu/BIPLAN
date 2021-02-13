### Documentation
- [Configuration](/documentation/configuration.md)
- [Comments](/documentation/comments.md) [`#`]()  
- [Conditions](/documentation/conditions.md) [`if`]() [`else`]() [`end`]()
- [Constants](/documentation/constants.md) [`true`]() [`false`]() [`HIGH`]() [`LOW`]() [`INPUT`]() [`OUTPUT`]()
- [Cycles](/documentation/cycles.md) [`for`](/documentation/cycles.md#for) [`while`](/documentation/cycles.md#while) [`next`](/documentation/cycles.md#next) [`break`](/documentation/cycles.md#break) [`continue`](/documentation/cycles.md#continue)
- [Functions](/documentation/functions.md) [`function`]() [`return`]()
- [Numeric variables](/documentation/numeric-variables.md) [`$`]() [`$[]`]()
- [Operators](/documentation/operators.md) [`+`]() [`-`]() [`*`]() [`/`]() [`%`]() [`==`]() [`!=`]() [`>`]() [`>=`]() [`<`]() [`<=`]() [`&&`]() [`||`]() [`&`]() [`|`]() [`^`]() [`>>`]() [`<<`]() [`++`]() [`--`]() [`~`]() [`not`]()
- [Strings](/documentation/strings.md) [`:`]() [`:[]`]()
- **[System functions](/documentation/system-functions.md)** [`stop`](/documentation/system-functions.md#stop) [`restart`](/documentation/system-functions.md#restart) [`char`](/documentation/system-functions.md#print) [`sizeof`](/documentation/system-functions.md#sizeof) [`print`](/documentation/system-functions.md#print) [`delay`](/documentation/system-functions.md#delay) [`random`]() [`millis`](/documentation/system-functions.md#millis) [`sqrt`]() [`analogRead`]() [`digitalRead`]() [`digitalWrite`]() [`pinMode`]() [`serialAvailable`]() [`serialRead`]() [`serialWrite`]() [`input`]() [`inputAvailable`]() [`index`](/documentation/system-functions.md#index) [`jump`](/documentation/system-functions.md#jump)
- [Unary operators](/documentation/unary-operators.md) [`++`]() [`--`]()

## System functions

### `delay`
```
delay [number in milliseconds]
```
It receives a single numeric parameter. Pauses the execution of the program.

### `jump`
```
jump [program index]
```
The `jump` statement transfers control to the location specified by the `label`. It receives a single parameter of type variable. It may appear before or after the label.
```php
label $cycle
  print $i++, " "
  jump $cycle
# Prints 0 1 2 3 4 5 ...
```
The program above saves in `$cycle` the index of the following statement, when `jump` is called what follows `label $cycle` is executed.

### `index`
```
index [variable or string]
```
Receives a single parameter of type variable or string. Returns the position in the buffer of the parameter received.

### `label`
```
label [variable]
```
Saves the program index in a variable to be used by `jump` later. Receives a single parameter of type variable.

### `millis`
```
millis
```
Returns the amount of milliseconds elapsed since the program's execution started.

### `print`
```
print [comma separated parameter list]
```
Receives a comma separated parameter list of type number, variable or string. It prints the parameters received. `char` can be used within print to convert numeric values to charaters.

### `restart`
```
restart
```
Restarts the execution of the program.

### `sizeof`
```
sizeof [variable or string]
```
Receives a single parameter of type variable or string. Returns the length of the parameter received.

### `stop`
```
stop
```
Halts the execution of the program.


| BIP code | BIPLAN function     | Purpose                                                |
| -------- | ------------------- | ------------------------------------------------------ |
|  `x`     | `stop`              | End program                                            |
|  `r`     | `restart`           | Restart program                                        |
|  `b`     | `char`              | Converts to char                                       |
|  `m`     | `sizeof`            | Returns the length of the trailing string or variable  |
|  `_`     | `index`             | Obtain index of                                        |
|  `\`     | `print`             | Prints data                                            |
|  `D`     | `delay`             | Pauses the program for n milliseconds                  |
|  `R`     | `random`            | Generates pseudo-random number                         |
|  `M`     | `millis`            | Returns the number of milliseconds since start up      |
|  `s`     | `sqrt`              | Calculates the square root of a number                 |
|  `J`     | `analogRead`        | Reads the value from the specified analog pin          |
|  `G`     | `digitalRead`       | Reads the value from a specified digital pin           |
|  `E`     | `digitalWrite`      | Sets the state to a digital pin                        |
|  `P`     | `pinMode`           | Configures the pin mode of a digital pin               |
|  `c`     | `serialRead`        | Get one character of input data                        |
|  `g`     | `serialWrite`       | Write one character to serial port                     |
|  `e`     | `input`             | Receive data                                           |
