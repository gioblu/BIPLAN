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
- **[System functions](/documentation/system-functions.md)** [`stop`](/documentation/system-functions.md#stop) [`restart`](/documentation/system-functions.md#restart) [`char`](/documentation/system-functions.md#print) [`sizeof`](/documentation/system-functions.md#sizeof) [`print`](/documentation/system-functions.md#print) [`delay`](/documentation/system-functions.md#delay) [`random`](/documentation/system-functions.md#random) [`millis`](/documentation/system-functions.md#millis) [`sqrt`](/documentation/system-functions.md#sqrt) [`analogRead`](/documentation/system-functions.md#analogRead) [`digitalRead`](/documentation/system-functions.md#digitalRead) [`digitalWrite`](/documentation/system-functions.md#digitalWrite) [`pinMode`](/documentation/system-functions.md#pinMode) [`serialRead`](/documentation/system-functions.md#serialRead) [`serialWrite`](/documentation/system-functions.md#serialWrite) [`input`](/documentation/system-functions.md#input) [`index`](/documentation/system-functions.md#index) [`jump`](/documentation/system-functions.md#jump)
- [Unary operators](/documentation/unary-operators.md) [`++`](/documentation/unary-operators.md) [`--`](/documentation/unary-operators.md)

## System functions

### `adc`

#### `adc read`
```
adc read [number or variable]
```
It receives a single parameter. Reads an analog pin and returns a value between 0 and 1023.
```php
print adc read A0
# Prints a value between 0 and 1023
```

---

### `cursor`
```
cursor [number or variable], [number or variable] 
```
It receives two parameters. Moves the cursor to the coordinates received.
```php
cursor 0, 0
# Moves the cursor to x 0, y 0
```

---

### `delay`
```
delay [number or variable]
```
It receives a single parameter. Pauses the execution of the program for a given amount of milliseconds.
```php
delay 1000
# Pauses the execution of the program for 1 second
```

---

### `file`

#### `file open`
```
file open [string or string address], [number or variable]
```
It receives two parameters, the file path and the mode. It returns the pointer to the file.

```php
$f = file open "test.txt", 0
# Opens the test.txt file in reading mode
```

#### `file close`

```
file close [pointer to file]
```
It receives a single parameter, the pointer to file. It closes the file.

```php
file close $f
# Closes test.txt file 
```

#### `file read`

```
file read [pointer to file]
```
It receives a single parameter, the file pointer. It returns one character.

```php
$c = file read $f
# Reads one character from test.txt
```

#### `file write`

```
file write [pointer to file], [string, string address, variable or value] 
```
It receives two parameters, the file pointer and the value to be written in the file. 

```php
file write $f, "Hello world!"
# Writes Hello world! test.txt
```

---

### `io`

#### `io read`
```
io read [number or variable]
```
It receives a single parameter. Reads a digital pin, it returns 0 or 1.
```php
print io read 12
# Prints either 0 or 1
```

#### `io write`

```
io write [number or variable], [number or variable]
```
It receives two parameters, the pin number and the state (0 or LOW, 1 or HIGH). Sets the state of a digital pin.
```php
io write 12, HIGH
# Sets the state of pin 12 to HIGH
```

#### `io open`

```
io open [number or variable], [number or variable]
```
It receives two parameters, the pin number and the mode (0 or INPUT, 1 or OUTPUT). Sets the mode of a digital pin.
```php
io open 12, OUTPUT
# Sets pin 12 mode as output
```

---

### `jump`
```
jump [variable]
```
The `jump` statement transfers control to the location specified by the `label`. It receives a single parameter of type variable.
```php
label $loop
  print "Hello world \n"
jump $loop
# Prints Hello word cyclically
```

---

### `index`
```
index [variable or string]
```
Receives a single parameter of type variable or string. Returns the position in the buffer of the parameter received.
```php
$roll = 125  
$yaw  = 150
print index $roll
# Prints 0
```

---

### `input`
```
input
```
Returns the user's input. On the Arduino returns -1 if no input is received on Linux instead it blocks the execution until a carriage return is detected. The user's input source can be configured when the `BIPLAN_Interpreter` is instantiated.
```php
$i = input
if $i >= 0 print char $i end
# Prints user's input
```

---

### `label`
```
label [variable]
```
Saves the program index in a variable to be used by `jump` later. Receives a single parameter of type variable.
```php
label $loop
  print "Hello world \n"
jump $loop
# Prints Hello word cyclically
```

---

### `millis`
```
millis
```
Returns the amount of milliseconds elapsed since the program's execution started.
```php
print millis
# Prints time elapsed since start up
```

---

### `numeric`
```
numeric [variable or numeric value]
```
Returns true if the input value is a numeric character, false if it is not a numeric character.
```php
$num = '1'
$chr = 'A'
print numeric $num, " ", numeric $chr
# Prints true false
```

---

### `print`
```
print [comma separated parameter list]
```
Receives a comma separated parameter list of type number, variable or string. It prints the parameters received. `char` can be used within print to convert numeric values to characters.
```php
print "Hello world!"
```

---

### `random`
```
random [variable or numeric value]
```
It receives a single parameter, the exclusive maximum value. Returns a randomly generated number.
```php
print random 10
# Prints a number between 0 and 9
```

---

### `restart`
```
restart
```
Restarts the execution of the program.
```php
restart
# Restarts the program
```

---

### `serial`

#### `serial write`
```
serial write [variable or numeric value or string]
```
Receives a single parameter of type number or variable or string. Transmits via serial the parameter's value.
```php
serial write "CIAO"
# Transmits CIAO via serial
```

#### `serial read`
```
serial read
```
Returns the value received via serial or -1 if no value is received.
```php
print serial read
# Prints what is received via serial
```

#### `serial open`
```
serial open [variable or numeric value]
```
Returns 1 if the serial port was correctly initialized, -1 if initialization failed.
```php
print serial read
# Prints what is received via serial
```

---

### `size`
```
size [variable or numeric value or string]
```
Receives a single parameter of type variable or string. Returns the length of the parameter received.
```php
$v = 0
print size $v
# Prints 4
:s = "Hello world!"
print size :s
# Prints 12
```
---

### `system` 
``` 
system [string or string address]
```
Passes a command or program name to the host environment, returns after the command has been completed.
```php
system "ls"
# On Linux prints list of files and directories
```

---

### `sqrt`
```
sqrt [variable or numeric value]
```
Receives a single parameter of type variable or string. Returns the length of the parameter received.
```php
print sqrt 81
# Prints 9
```

---

### `stop`
```
stop
```
Halts the execution of the program.
```php
stop
# Stops the program's execution
```

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
