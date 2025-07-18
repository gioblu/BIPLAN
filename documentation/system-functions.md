### Documentation
- [Bytecode](/documentation/bytecode.md)
- [Configuration](/documentation/configuration.md)
- [Comments](/documentation/comments.md) [`//`](/documentation/comments.md)
- [Conditions](/documentation/conditions.md) [`if`](/documentation/conditions.md) [`else`](/documentation/conditions.md) [`end`](/documentation/conditions.md)
- [Constants](/documentation/constants.md) [`true`](/documentation/constants.md) [`false`](/documentation/constants.md) [`HIGH`](/documentation/constants.md) [`LOW`](/documentation/constants.md) [`INPUT`](/documentation/constants.md) [`OUTPUT`](/documentation/constants.md)
- [Cycles](/documentation/cycles.md) [`for`](/documentation/cycles.md#for) [`while`](/documentation/cycles.md#while) [`next`](/documentation/cycles.md#next) [`break`](/documentation/cycles.md#break) [`continue`](/documentation/cycles.md#continue)
- [Functions](/documentation/functions.md) [`function`](/documentation/functions.md) [`locals`](/documentation/functions.md) [`return`](/documentation/functions.md)
- [Macros](/documentation/macros.md) [`macro`](/documentation/macros.md#pre-processor-macros)
- [Numeric variables](/documentation/numeric-variables.md) [`@`](/documentation/numeric-variables.md) [`@[]`](/documentation/numeric-variables.md)
- [Operators](/documentation/operators.md) [`+`](/documentation/operators.md) [`-`](/documentation/operators.md) [`*`](/documentation/operators.md) [`/`](/documentation/operators.md) [`%`](/documentation/operators.md) [`==`](/documentation/operators.md) [`!=`](/documentation/operators.md) [`>`](/documentation/operators.md) [`>=`](/documentation/operators.md) [`<`](/documentation/operators.md) [`<=`](/documentation/operators.md) [`&&`](/documentation/operators.md) [`||`](/documentation/operators.md) [`&`](/documentation/operators.md) [`|`](/documentation/operators.md) [`^`](/documentation/operators.md) [`>>`](/documentation/operators.md) [`<<`](/documentation/operators.md) [`++`](/documentation/operators.md) [`--`](/documentation/operators.md) [`~`](/documentation/operators.md) [`not`](/documentation/operators.md)
- [Strings](/documentation/strings.md) [`:`](/documentation/strings.md) [`:[]`](/documentation/strings.md)
- **[System functions](/documentation/system-functions.md)** [`adc read`](/documentation/system-functions.md#adc-read) [`args`](/documentation/system-functions.md#args) [`char`](/documentation/system-functions.md#print) [`cursor`](/documentation/system-functions.md#print) [`delay`](/documentation/system-functions.md#delay) [`file close`](/documentation/system-functions.md#file-close) [`file open`](/documentation/system-functions.md#file-open) [`file read`](/documentation/system-functions.md#file-read) [`file write`](/documentation/system-functions.md#file-write) [`include`](/documentation/system-functions.md#include) [`index`](/documentation/system-functions.md#index) [`input`](/documentation/system-functions.md#input) [`io open`](/documentation/system-functions.md#io-open) [`io read`](/documentation/system-functions.md#io-read) [`io write`](/documentation/system-functions.md#digitalWrite) [`mem`](/documentation/system-functions.md#mem)  [`millis`](/documentation/system-functions.md#millis) [`number`](/documentation/system-functions.md#number) [`numeric`](/documentation/system-functions.md#numeric) [`print`](/documentation/system-functions.md#print) [`random`](/documentation/system-functions.md#random) [`restart`](/documentation/system-functions.md#restart) [`serial open`](/documentation/system-functions.md#serial-open) [`serial read`](/documentation/system-functions.md#serial-read) [`serial write`](/documentation/system-functions.md#serial-write) [`size`](/documentation/system-functions.md#size)  [`stop`](/documentation/system-functions.md#stop) [`string`](/documentation/system-functions.md#string) [`system`](/documentation/system-functions.md#system)
- [Unary operators](/documentation/unary-operators.md) [`++`](/documentation/unary-operators.md) [`--`](/documentation/unary-operators.md)

## System functions

### `adc`
Using the `adc` keyword along with `read`, `write`, `open` and `close` it is possible to fully handle the ADC (Analog to Digital Converter).

#### `adc read`
```
adc read [number or variable]
```
It receives a single parameter. Reads an analog pin and returns a value between 0 and 1023.
```c
print adc read A0 // Prints a value between 0 and 1023
```

---

### `args`
Using the `args` keyword it is possible to access to arguments that have been passed to the program.

```c
print args[0] // Prints the first argument passed to the program
```

---

### `delay`
```
delay [number or variable]
```
It receives a single parameter. Pauses the execution of the program for a given amount of milliseconds.
```c
delay 1000 // Pauses the execution of the program for 1 second
```

---

### `file`
Using the `file` keyword along with `read`, `write`, `open` and `close` it is possible to fully handle files.

#### `file open`
```
file open [string or string literal], [number or variable]
```
It receives two parameters, the file path and the mode. It returns the pointer to the file.

```c
@f = file open "test.txt", 0 // Opens the test.txt file in reading mode
```

#### `file close`

```
file close [pointer to file]
```
It receives a single parameter, the pointer to file. It closes the file.

```c
file close @f // Closes test.txt file
```

#### `file read`

```
file read [pointer to file], [variable or number]
```
It receives two parameters, the file pointer and the mode; It returns one character.

```c
@c = file read @f, 0 // Reads one character from test.txt using read mode
```
Available modes:

- `0`: read (r)
- `1`: read binary (rb)
- `2`: read write (r+)
- `3`: read write binary (rb+)
- `4`: write (w)
- `5`: write binary (wb)
- `6`: write read (w+)
- `7`: write read binary (wb+)
- `8`: append (a)
- `9`: append binary (ab)
- `10`: append read write (a+)
- `11`: append binary read write (ab+)

#### `file write`

```
file write [pointer to file], [string, string literal, variable or number]
```
It receives two parameters, the file pointer and the value to be written in the file.

```c
file write @f, "Hello world!" // Writes Hello world! test.txt
```
---

### `include`
With the `include` keyword it is possible to add at the end of the program the content of a `.biplan` file.

```
include [string literal]
```
The `include` statement receives a string literal that must contain the path, file name and extension of the file to be included. In the example below `hello_world.biplan` that contains the line `function hello_world() print "Hello World!" return 0` is included in the program. When executed the program prints "Hello World!" and stops.

```c
include "hello_world.biplan"
hello_world()
stop
```

---

### `index`
```
index [variable or string]
```
Receives a single parameter of type variable or string. Returns the position in the buffer of the parameter received.
```c
@roll = 125
@yaw  = 150
print index @roll // Prints 0
```

---

### `input`
The user's input source can be configured when the `BIPLAN_Interpreter` is instantiated

#### `input`
```
input
```
Returns the user's input, it blocks the execution until a carriage return is detected and it returns one character from the user's input.
```c
@i = input
if @i >= 0 print char @i end // Prints user's input
```

#### `input read`
```
input read
```
Returns one character from the user's input immediately or -1 if no input is received. The user's input source can be configured when the `BIPLAN_Interpreter` is instantiated.
```c
@i = input read
if @i >= 0 print char @i end // Prints user's input
```
---

### `io`
Using the `io` keyword along with `read`, `write`, `open` and `close` it is possible to fully handle IO (Input Output) ports.

#### `io read`
```
io read [number or variable]
```
It receives a single parameter. Reads a digital pin, it returns 0 or 1.
```c
print io read 12 // Prints either 0 or 1
```

#### `io write`

```
io write [number or variable], [number or variable]
```
It receives two parameters, the pin number and the state (0 or LOW, 1 or HIGH). Sets the state of a digital pin.
```c
io write 12, HIGH // Sets the state of pin 12 to HIGH
```

#### `io open`

```
io open [number or variable], [number or variable]
```
It receives two parameters, the pin number and the mode (0 or INPUT, 1 or OUTPUT). Sets the mode of a digital pin.
```c
io open 12, OUTPUT // Sets pin 12 mode as output
```

---

### `jump`
```
jump [variable]
```
The `jump` statement transfers control to the location specified by the `label`. It receives a single parameter of type variable.
```c
label @loop
  print "Hello world \n"
jump @loop // Prints Hello word cyclically
```

---

### `label`
```
label [variable]
```
Saves the position in the program in a variable to be used by `jump` later. Receives a single parameter of type variable.
```c
label @loop
  print "Hello world \n"
jump @loop // Prints Hello word cyclically
```

---

### `mem`

```
mem[number or variable]

mem[number or variable] = variable or character constant
```
Can read or write one byte of memory.

```c
mem[0] = 1
print mem[0] // Prints 1
```

---

### `millis`
```
millis
```
Returns the amount of milliseconds elapsed since the program's execution started.
```c
print millis // Prints time elapsed since start up
```

---

### `number`
```
number [string or string literal or argument]
```
Converts a string, string literal or argument to an integer and returns its value.
```c
:test = "123"
print number :test + 1 // Prints 124
```

---

### `numeric`
```
numeric [variable or number]
```
Returns true if the input value is a numeric character, false if it is not a numeric character.
```c
@num = '1'
@chr = 'A'
print numeric @num, " ", numeric @chr // Prints true false
```

---

### `print`
```
print [comma separated parameter list]
```
Receives a comma separated parameter list of type number, variable or string. It prints the parameters received. `char` can be used within print to convert numbers to characters.
```c
print "Hello world!"
```
To clear the screen, if supported by your physical machine, use the `restart` keyword as shown below.
```c
print restart
```
To move the cursor, if supported by your physical machine, use the `cursor` keyword as shown below.

```c
print cursor 0, 0 // Moves the cursor to x 0, y 0
```
---

### `random`
```
random [variable or number]
```
It receives a single parameter, the exclusive maximum value. Returns a randomly generated number.
```c
print random 10 // Prints a number between 0 and 9
```

---

### `restart`
```
restart
```
Restarts the execution of the program.
```c
restart // Restarts the program
```

---

### `serial`
Using the `serial` keyword along with `read`, `write`, `open` and `close` it is possible to fully handle serial communication.

#### `serial write`
```
serial write [variable, number, string or string literal]
```
Receives a single parameter of type number or variable or string. Transmits via serial the parameter's value.
```c
serial write "CIAO" // Transmits CIAO via serial
```

#### `serial read`
```
serial read
```
Returns the value received via serial or -1 if no value is received.
```c
print serial read // Prints what is received via serial
```

#### `serial open`
```
serial open [string or string literal], [variable or number]
```
Initializes the serial port.
```c
serial open "COM1", 9600 // Opens serial COM1 at 9600Bd
```

#### `serial close`
```
serial close [string or string literal], [variable or number]
```
Flushes the serial port.
```c
serial close // Flushes serial 
```

---

### `size`
```
size [variable or number or string or string literal]
```
Receives a single parameter of type variable or string. Returns the length of the parameter received.
```c
@v = 0
print size @v // Prints 4
:s = "Hello world!"
print size :s // Prints 12
```

---

### `stop`
```
stop
```
Halts the execution of the program.
```c
stop //Stops the program's execution
```

---

### `string`
```
string [variable or number], [string], [variable or number]
```
Converts a variable or a number to a string. It receives the number to be converted, the string where to save the conversion and optionally the position where to start writing.
```c
@test = 123
string @test, :str
print :str // Prints 123
```

---

### `system`
```
system [string or string literal]
```
Passes a command or program name to the host environment, returns after the command has been completed.
```c
system "ls" // On Linux prints list of files and directories
```
