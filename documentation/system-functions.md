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
- **[System functions](/documentation/system-functions.md)** [`stop`](/documentation/system-functions.md#stop) [`restart`](/documentation/system-functions.md#restart) [`char`](/documentation/system-functions.md#print) [`sizeof`](/documentation/system-functions.md#sizeof) [`print`](/documentation/system-functions.md#print) [`delay`](/documentation/system-functions.md#delay) [`random`]() [`millis`](/documentation/system-functions.md#millis) [`sqrt`](/documentation/system-functions.md#sqrt) [`analogRead`](/documentation/system-functions.md#analogRead) [`digitalRead`](/documentation/system-functions.md#digitalRead) [`digitalWrite`](/documentation/system-functions.md#digitalWrite) [`pinMode`](/documentation/system-functions.md#pinMode) [`serialRead`](/documentation/system-functions.md#serialRead) [`serialWrite`](/documentation/system-functions.md#serialWrite) [`input`](/documentation/system-functions.md#input) [`index`](/documentation/system-functions.md#index) [`jump`](/documentation/system-functions.md#jump)
- [Unary operators](/documentation/unary-operators.md) [`++`]() [`--`]()

## System functions

### `analogRead`
```
analogRead [number or variable]
```
It receives a single parameter. Reads an analog pin and returns a value between 0 and 1023.

---

### `delay`
```
delay [number or variable]
```
It receives a single parameter. Pauses the execution of the program for a given amount of milliseconds.

---

### `digitalRead`
```
digitalRead [number or variable]
```
It receives a single parameter. Reads a digital pin, it returns 0 or 1.

---

### `digitalWrite`
```
digitalWrite [number or variable], [number or variable]
```
It receives two parameters, the pin number and the state (0 or LOW, 1 or HIGH). Sets the state of a digital pin.

---

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

---

### `index`
```
index [variable or string]
```
Receives a single parameter of type variable or string. Returns the position in the buffer of the parameter received.

---

### `input`
```
input
```
Returns the user's input. Returns -1 if no input is received.

---

### `label`
```
label [variable]
```
Saves the program index in a variable to be used by `jump` later. Receives a single parameter of type variable.

---

### `millis`
```
millis
```
Returns the amount of milliseconds elapsed since the program's execution started.

---

### `pinMode`
```
pinMode [number or variable], [number or variable]
```
It receives two parameters, the pin number and the mode (0 or INPUT, 1 or OUTPUT). Sets the mode of a digital pin.

---

### `print`
```
print [comma separated parameter list]
```
Receives a comma separated parameter list of type number, variable or string. It prints the parameters received. `char` can be used within print to convert numeric values to charaters.

---

### `random`
```
random [number or variable]

random [number or variable], [number or variable]
```
It can receive a single parameter, the maximum or two parameters the minimum and the maximum. Returns a randomly generated number.

---

### `restart`
```
restart
```
Restarts the execution of the program.

---

### `serialWrite`
```
serialWrite [number or variable or string]
```
Receives a single parameter of type number or variable or string. Transmits via serial the parameter's value.

---

### `serialRead`
```
serialRead
```
Returns the value received via serial or -1 if no value is received.

---

### `sizeof`
```
sizeof [variable or string]
```
Receives a single parameter of type variable or string. Returns the length of the parameter received.

---

### `sqrt`
```
sqrt [number or variable]
```
Receives a single parameter of type variable or string. Returns the length of the parameter received.

---

### `stop`
```
stop
```
Halts the execution of the program.

---

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
