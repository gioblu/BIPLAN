This is the BIPLAN programming language repository. It is a novel programming language. Before you start writing any code on this codebase, initialize reading carefully the following sections below:

# Always comply with the following 10 requirements

1. Never make assumptions and present them as fact
2. When you present a fact include a proof
3. Complexity must be minimized
4. Safety and reliability must be maximized
5. Code you output must be concise, minimalistic and elegant
6. Code you output must be syntactically correct and must not add any vulnerability, bug, off-by-one or memory leak
7. When you write code and tests follow the DRY (Don't Repeat Yourself) principle
8. Do not generate code that is incomplete and it does not build
9. You must use only static memory allocation, dynamic memory allocation is outlawed
10. Code you output must be tested compiling it with `bcc` and interpreting it with `biplan`, tests must focus on testing functionality, not code

# Important things to know for working on this codebase

1. All the constants and data types are present in `src/BIPLAN_Defines.h`.
2. If you need information about the compiler go to `src/BCC.c` and `src/BCC.h`, if you change those files you need to recompile `bcc`.
3. If you need information about the interpreter go to `src/BIPLAN.c`, `src/BIPLAN.h` and `src/BIPLAN_Decoder.h`, if you change those files you need to recompile `biplan`.
4. The standard library is in `src/utils/libraries`, if you make changes inside this directory you will need to rebuild the compiler to update it in `usr/local/bin`.
5. All system calls are defined in `src/interfaces` if you change anything here you need to recompile `biplan`.

# Language Syntax

## Comments
Comments are human-readable notes present in the source-code. They will be ignored by the compiler. The `//` symbol signals the start of a comment. A comment can make use of an entire line:
```
// This is a comment
```
or can be placed after a statement:
```
print "Hello world!" // This is another comment
```

## Conditions
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
An `if`, if its condition is truthy, executes the following statements until `end` is encountered, otherwise it executes the statements that follow the next `end` or the next `else` until `end` is encountered. It is used where code needs to be executed only if a given condition is true. An `if` or `else` statement can execute a single statement and fit in a single line:
```
@fine = true
if @fine print "All is fine!" end

// Or

if not @fine print "Some error occurred"
else print "All is fine!" end
```
or can also conditionally execute a group of statements:
```
// Condition block

if 1 == 1
  print "All is fine!"
  print "Equality works"
else
  print "Some error occurred!"
  print "Equality does not work"
end
```

## Constants

| Constant   | Value  |
| ---------- | ------ |
| `false`    | `0`    |
| `true`     | `1`    |
| `LOW`      | `0`    |
| `HIGH`     | `1`    |
| `INPUT`    | `0`    |
| `OUTPUT`   | `1`    |
| `CR`       | `13`   |
| `LF`       | `10`   |
| `EOF`      | `-1`   |

## `for`
```
for [variable assignment] to [expression] step [expression]
  [statement]
next
```
The `for` is a cycle that supports a single local variable identified by `#` that can be set with an initial value and a limit value that is specified after `to`:
```
for #i = 0 to 5
  print #i
next

// Prints 0, 1, 2, 3, 4
```
In the example above `#i` is locally declared with a value of 0 and it will be incremented by 1 at each cycle. The `for` iterates the local variable up or down to the desired limit in both directions:
```
for #i = 5 to 0
  print #i
next

// Prints 5, 4, 3, 2, 1
```
Each time `next` is encountered the variable is incremented or decremented by 1 and the cycle restarts if the limit defined after the `to` is not reached. Consider that `for`, unlike `for` defined by other programming languages, evaluates and computes the limit the first time the `for` statement is encountered. For this reason the `for` is a quick iterator, if you need to conditionally exit from a loop use `while` instead.

#### `step`
Optionally the `for` the increment or decrement value can be configured after `step`:
```
for #i = 0 to 10 step 2
  print #i
next

// Prints 0, 2, 4, 6, 8
```

#### `break`
The BIPLAN `for` supports `break` as other programming languages do:
```
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
```
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
```
while io read 12 == HIGH
  print "The pin is HIGH"
next

// Prints The pin is HIGH until pin 12 is HIGH
```

#### `break`
The BIPLAN `while` supports `break` as other programming languages do:
```
while true
  if io read 12 == HIGH
    break
  end
next
print "Button pressed!"

// Prints Button pressed when pin 12 is HIGH
```
When `break` is encountered within a `while`, the iteration is interrupted and all following statements part of the `while` are ignored.

#### `continue`
The BIPLAN `while` supports `continue` as other programming languages do:
```
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
When `continue` is encountered within a `while`, all following statements part of the `while` are ignored and the next iteration is initiated.

## Functions
```

// Call

[name]([function call, relation, expression, term or factor])

// Definition

function [name]([parameter], [parameter], ..., locals: [local], [local], ...)
  [statement]
  return [function call, relation, expression, term or factor]
done
```
A function is a reusable group of statements identified by a unique name that perform a task and can return a value. BIPLAN supports up to 88 functions, each capable of hosting up to 88 parameters and local variables. Function definitions must be defined after the `stop` keyword.

Function definitions are identified by the `function` keyword followed by a unique name; parameters and local variables are defined within the following parentheses, local variables are defined after the `locals:` keyword. Names of functions and parameters must not start with a number, must be composed by lowercase and or uppercase letters, numbers and or the symbol `_`. The value of uninitialized parameters and local variables is guaranteed to be `0`.

When the `return` keyword is encountered the function returns the result of the following function call, relation, expression, term or factor. All statements contained in the function definition are executed until `done` is encountered. The `done` statement must be one and must be the last statement of the function.

```

// Call

average(10, 20); // Returns 15

// Definition

function average($a, $b, locals: $sum)
  $sum = $a + $b
  return $sum / 2
done
```

Functions can receive only numeric parameters, each parameter can represent a numeric value, a reference to a variable or a reference to a string:

```
:test = "test"

capitalize(index :test)

print :test // Prints "Test"

stop

function capitalize($string_addr)
  :[$string_addr][0] = :[$string_addr][0] - 32
done
```

In the example above the reference to the string `:test` is passed to the `capitalize` function. The reference is then used to modify the first character.


## Pre-processor macros
```
macro [name] [code]
```
A macro is a capitalized keyword of at least 2 characters associated with a single line of code containing at least one statement. Each time the macro's keyword occurs in the source it is substituted with its associated line of code. This task is executed by the pre-processor before the compilation phase starts.


```
macro WAIT delay 100

while true
  print "Hello World!"
  WAIT
next
```

After the pre-processing phase the code above looks like this:


```
while true
  print "Hello World!"
  delay 100
next
```
Macros are useful to associate a keyword with an integer constant or a string literal, without consuming a variable address. Macros can be used also to associate a keyword to a system function call or a function call with a predefined set of parameters.


## Numeric variables
BIPLAN supports only one signed numeric variable type, that is by default `long` (if a different type is required see [configuration](/documentation/configuration.md)). Numeric variables are identified by `@`. The name of variables must not start with a number, must be composed by lowercase and or uppercase letters, numbers and or the symbol `_`. Each variable is just an entry of a global array of variables. BIPLAN supports up to 88 variables.

See below how to define a variable:

```
@test = 10
```
Variables can be accessed by name:
```
print @test // Prints "10"
```
All Variables can be accessed by reference using `@[]`:
```
@test = 111
print @[0]  // Prints 111 or the value of the first variable defined
@[0] = 2
print @test // Prints 2
```
The reference of a variable can be obtained prepending its name with `index`:
```
@a_variable = 10 // index 0
@variable = 1    // index 1
@var = 22        // index 2

print index @var // Prints 2 or the index of $var
```
The `bcc` compiler starts from the longest variable name, for this reason `@var` is the last to be compiled and acquires the reference 2.

## Operators

| Arithmetic         | Logic                 | Bitwise           | Unary prefix             |
| ------------------ | --------------------- | ----------------- | ------------------------ |
| `+` Addition       | `==` Equal            | `&` And           | `++`  Increment then use |
| `-` Subtraction    | `!=` Not equal        | `\|` Or           | `--`  Decrement then use |
| `*` Multiplication | `<`  Less             | `^` Xor           | `~`   Bitwise not        |
| `/` Division       | `<=` Less or equal    | `<<` Left shift   | `not` Logic not          |
| `%` Modulus        | `>`  Greater          | `>>` Right shift  |                          |
|                    | `>=` Greater or equal |                   |                          |
|                    | `&&` And              |                   |                          |
|                    | `\|\|` Or             |                   |                          |

### Operator precedence

BIPLAN implements a recursive descent parser for this reason there is no operator precedence and calculations are executed in the order specified by the user.

### Operator syntax

In BIPLAN the following program is incorrect:
```
if 1 == 1 || 0 == 0 print "OK" end
```
The correct form is:
```
if (1 == 1) || (0 == 0) print "OK" end
```
Parenthesis are required for the interpreter to detect a nested relation and compute it before the primary relation.

## Strings
String are identified by `:`, their name must not start with a number, must be composed by lowercase and or uppercase letters and or the symbol `_` and or numbers. Each string is just an entry of a global array of strings. BIPLAN supports up to 88 strings of 2^31 or 2^63 bits length. A string can be declared:
```
:test = "Hello world!"
```
A string can be accessed by name:
```
:test = "Hello world!"
print :test // Prints "Hello world!"
```
Strings can be concatenated:
```
:name = "Fred"
:phrase = "Hi " + :name + "!" // Prints "Hi Fred!"
```
All strings can be accessed by reference using `:[]`:
```
:test = "Hello world!"
print :[0] // Prints "Hello world!"
```
Characters of strings can be accessed as shown below:
```
:test = "Hello world!"
print :test[0] // Prints "H"
```
The reference of a string can be obtained prepending its name with `index`:
```
:a_string = "Hello world" // index 0
:b_string = "World"       // index 1
:c_string = "Hello"       // index 2
print index :c_string     // Prints 2 or the index of :c_string
```


## System functions

### `adc`
Using the `adc` keyword along with `read`, `write`, `open` and `close` it is possible to fully handle the ADC (Analog to Digital Converter).

#### `adc read`
```
adc read [number or variable]
```
It receives a single parameter. Reads an analog pin and returns a value between 0 and 1023.
```
print adc read A0 // Prints a value between 0 and 1023
```

---

### `args`
Using the `args` keyword it is possible to access to arguments that have been passed to the program.

```
print args[0] // Prints the first argument passed to the program
```

---

### `delay`
```
delay [number or variable]
```
It receives a single parameter. Pauses the execution of the program for a given amount of milliseconds.
```
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

```
@f = file open "test.txt", 0 // Opens the test.txt file in reading mode
```

#### `file close`

```
file close [pointer to file]
```
It receives a single parameter, the pointer to file. It closes the file.

```
file close @f // Closes test.txt file
```

#### `file read`

```
file read [pointer to file], [variable or number]
```
It receives two parameters, the file pointer and the mode; It returns one character.

```
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

```
file write @f, "Hello world!" // Writes Hello world! test.txt
```
---

### `pipe`
Using the `pipe` keyword along with `open`, `read`, `write` and `close` it is possible to execute a shell command and stream its I/O.

#### `pipe open`
```
pipe open [string or string literal], [number or variable]
```
It receives the command to execute and an optional mode. It returns a handle that can be used with `pipe read`, `pipe write` and `pipe close`.

```
@pipe = pipe open "curl -s https://httpbin.org/get"
```

#### `pipe read`
```
pipe read [handle]
```
It receives a single parameter, the pipe handle, and returns one character from the command output or `-1` when the pipe is closed.

```
@c = pipe read @pipe
```

#### `pipe write`
```
pipe write [handle], [number or variable]
```
It receives two parameters: the pipe handle and the character code to write to the command's stdin.

```
pipe write @pipe, 'A'
```

#### `pipe close`
```
pipe close [handle]
```
It receives a single parameter, the pipe handle. It closes the pipe and terminates the associated subprocess.

```
pipe close @pipe
```
---

### `include`
With the `include` keyword it is possible to add at the end of the program the content of a `.biplan` file.

```
include [string literal]
```
The `include` statement receives a string literal that must contain the path, file name and extension of the file to be included. In the example below `hello_world.biplan` that contains the line `function hello_world() print "Hello World!" return 0` is included at the end of the program. When executed the program prints "Hello World!" and stops.

```
include "hello_world.biplan"
hello_world()
stop
```
You can include files from the current directory or use relative paths:

```
include "mylib.biplan"                      // File in current directory
include "../libs/mylib.biplan"              // Relative path from current directory
```
Standard libraries are installed in `/usr/local/BIPLAN/`. To include a standard library, use the absolute path:

```
include "/usr/local/BIPLAN/math.biplan"
include "/usr/local/BIPLAN/cordic.biplan"
include "/usr/local/BIPLAN/graphics.biplan"
```

---

### `index`
```
index [variable or string]
```
Receives a single parameter of type variable or string. Returns the position in the buffer of the parameter received.
```
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
```
@i = input
if @i >= 0 print char @i end // Prints user's input
```

#### `input read`
```
input read
```
Returns one character from the user's input immediately or -1 if no input is received. The user's input source can be configured when the `BIPLAN_Interpreter` is instantiated.
```
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
```
print io read 12 // Prints either 0 or 1
```

#### `io write`

```
io write [number or variable], [number or variable]
```
It receives two parameters, the pin number and the state (0 or LOW, 1 or HIGH). Sets the state of a digital pin.
```
io write 12, HIGH // Sets the state of pin 12 to HIGH
```

#### `io open`

```
io open [number or variable], [number or variable]
```
It receives two parameters, the pin number and the mode (0 or INPUT, 1 or OUTPUT). Sets the mode of a digital pin.
```
io open 12, OUTPUT // Sets pin 12 mode as output
```

---

### `mem`

```
mem[number or variable]

mem[number or variable] = variable or character constant
```
Can read or write one byte of memory.

```
mem[0] = 1
print mem[0] // Prints 1
```

---

### `millis`
```
millis
```
Returns the amount of milliseconds elapsed since the program's execution started.
```
print millis // Prints time elapsed since start up
```

---

### `number`
```
number [string or string literal or argument]
```
Converts a string, string literal or argument to an integer and returns its value.
```
:test = "123"
print number :test + 1 // Prints 124
```

---

### `numeric`
```
numeric [variable or number]
```
Returns true if the input value is a numeric character, false if it is not a numeric character.
```
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
```
print "Hello world!"
```
To clear the screen, if supported by your physical machine, use the `restart` keyword as shown below.
```
print restart
```
To move the cursor, if supported by your physical machine, use the `cursor` keyword as shown below.

```
print cursor 0, 0 // Moves the cursor to x 0, y 0
```
---

### `random`
```
random [variable or number]
```
It receives a single parameter, the exclusive maximum value. Returns a randomly generated number.
```
print random 10 // Prints a number between 0 and 9
```

---

### `restart`
```
restart
```
Restarts the execution of the program.
```
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
```
serial write "CIAO" // Transmits CIAO via serial
```

#### `serial read`
```
serial read
```
Returns the value received via serial or -1 if no value is received.
```
print serial read // Prints what is received via serial
```

#### `serial open`
```
serial open [string or string literal], [variable or number]
```
Initializes the serial port.
```
serial open "COM1", 9600 // Opens serial COM1 at 9600Bd
```

#### `serial close`
```
serial close [string or string literal], [variable or number]
```
Flushes the serial port.
```
serial close // Flushes serial
```

---

### `size`
```
size [variable or number or string or string literal]
```
Receives a single parameter of type variable or string. Returns the length of the parameter received.
```
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
```
stop //Stops the program's execution
```

---

### `string`
```
string [variable or number], [string], [variable or number]
```
Converts a variable or a number to a string. It receives the number to be converted, the string where to save the conversion and optionally the position where to start writing.
```
@test = 123
string @test, :str
print :str // Prints 123
```

## Unary operators
BIPLAN supports only prefix increment and decrement unary operators. Prefix unary operators are used to increment or decrement its operand. The increment operator `++` adds 1, the decrement operator `--` subtracts 1. Both `++` and `--` can be used as prefix operators (before the operand: `++v`). For example `++v` increments the value of `v` before it is used.

Prefix unary operators in statement must be used only when incrementing or decrementing variables:
```
@a = 0
print ++@a // Prints "1" and sets a = 1 in memory
```
BIPLAN unary operators can be chained:

```
@a = 0
print ++++@a // Sets a = 2 in memory and prints "2"

@a = 1
print ----@a // Sets a = -1 in memory and prints "-1"
```
## bcc (BIP Compiler Collection)
The `bcc.cpp` file is a complete and ready to use compiler. It is able to compile BIPLAN source into BIP machine language.

### How to build it
1. Open the console
2. Locate the `BIPLAN/examples/LINUX/bcc-compiler` directory
3. You can choose to build the compact compiler using `sudo make compact` which is optimized for size (~22KB), or build the executable optimized for performance using `sudo make fast`, the resulting binary will be larger in size (~34KB) but around twice as fast if compared to the `compact` target.
4. Digit `sudo make install`

### The bcc executable
With `bcc` you can compile a BIPLAN program into BIP machine language.

```
bcc [BIPLAN input file] [BIP output file]
```
The `bcc` executable is copied in `usr/bin` to be reachable everywhere within your system; it receives 2 parameters, the BIPLAN input file and the BIP output file. If the 2 files are not in the same directory your terminal is in you will need to specify the path to reach them.

### How to use it
 In this directory you find [`fib.biplan`](fib.biplan), it contains a BIPLAN program able to compute the 40th number of the fibonacci series 100.000 times. Let's compile it into BIP machine language in [`fib.bip`](../biplan-interpreter/fib.bip). To do so:

1. Open the console
2. Locate the `BIPLAN/examples/LINUX/bcc-compiler` directory
3. Digit `bcc fib.biplan ../biplan-interpreter/fib.bip`

Expected output:
```
BCC (BIP Compiler Collection) Giovanni Blu Mitolo 2021
Source: fib.biplan
Target: ../biplan-interpreter/fib.bip
Source length: 410B, BIP length: 57B, reduction: 86.097565%
Compilation time: 1241 microseconds

```

The compiler should have created `fib.bip` inside the `biplan-interpreter` directory.

You can now give a try to the [biplan-interpreter](../biplan-interpreter) and use it to run [`fib.bip`](../biplan-interpreter/fib.bip).

## biplan interpreter
The `biplan.cpp` file is a complete and ready to use BIP machine language interpreter.

### How to build it
1. Open the console
2. Locate the `BIPLAN/examples/LINUX/biplan-interpreter` directory
3. You can choose to build the compact interpreter using `sudo make compact` which is optimized for size (~26KB), or build the executable optimized for performance using `sudo make fast`, the resulting binary will be larger in size (~82KB) but around twice as fast if compared to the `compact` target.
4. Digit `sudo make install`
5. Digit `sudo make clean` to remove the executable from the `usr/local/bin` directory

### How to use it
The `bcc` executable is copied in `usr/local/bin` to be reachable everywhere within your system. You can use it to interpret BIP machine language. In this directory you find [`fib.bip`](fib.bip), this file contains a program in BIP machine language that computes the 40th number of the Fibonacci sequence 100.000 times (the human-readable version is [fib.biplan](../bcc-compiler/fib.biplan)). You can use the `biplan` executable to interpret [`fib.bip`](fib.bip) or any other BIPLAN program. To do so:

1. Open the console
2. Locate the `BIPLAN/examples/LINUX/biplan-interpreter` directory
3. Digit `biplan -i fib.bip -d`

Expected output:
```
BIPLAN interpreter - Giovanni Blu Mitolo 2025
Source: fib.bip
Source length: 57B

Interpreter output:

102334155

Execution duration: 648949 microseconds
```

You can now write a BIPLAN program, play with the [bcc-compiler](../bcc-compiler) and use the `biplan` executable to interpret it.

`biplan` supports additional arguments:
- `-a` passes an argument to the program
- `-d` prints debug information
- `-h` prints help

## Codestyle guidelines

Just see the following examples for information about code-style:

```
// Checks if an ASCII character is numeric (0..9)
// returns true if numeric, false if not numeric
function numeric($v)
  return (($v >= 48) && ($v <= 57))
done

// Searches for the first occurrence of a character within a string
// Returns -1 if no occurrence is found or a numeric index if found
function find_char($str, $chr)
	$r = - 1
	for #i = 0 to size :[$str]
		if :[$str][#i] == $chr return #i end
	next
  return $r
done

macro BLACK     0
macro WHITE     7

// ANSI escape codes for background color
macro BG_BLACK  system "echo -n '\033[0;40m'"
macro BG_WHITE  system "echo -n '\033[0;47m'"

// Set background
function ansi_background($color, locals: $v)
  if $color == BLACK $v = BG_BLACK return end
  if $color == WHITE $v = BG_WHITE return end
done

print "
X drawer example
Please input resolution between 3 and 9:"

@res = 0

while @res < 3
  @res = input
  if (@res >= 0) @res = number @res end
next

for #y = 0 to @res
  for #x = 0 to @res
    if #x == #y || (#x + #y == (@res - 1)) print "X"
    else print " "
    end
  next
  print "
"
next

stop

// Very simple terminal calculator
// Example: biplan -i calc.bip -a 10 -a "+" -a 10
// result:  20
@result = 0
@op = args[1][0]
if @op == '+'  @result = number args[0] + number args[2] end
if @op == '-'  @result = number args[0] - number args[2] end
if @op == '*'  @result = number args[0] * number args[2] end
if @op == '/'  @result = number args[0] / number args[2] end
print "result: ", @result
stop

include "/usr/local/BIPLAN/graphics.biplan"
include "/usr/local/BIPLAN/ansi.biplan"

macro HINT "Press WASD to move the rectangle, press Q to terminate the program."

@x = 10
@y = 5

ansi_cursor(false)
ansi_background(PURPLE)
ansi_color(BLACK)
print restart, HINT
draw_rect(@x, @y, 10, 5, 'X')

while true
  @k = input read
  if @k == 'q'
    break
  end
  if @k != 0
     print restart, HINT
     if @k == 'd' ++@x end
     if (@k == 'a') && (@x > 2) --@x end
     if (@k == 'w') && (@y > 2) --@y end
     if @k == 's' ++@y end
     draw_rect(@x, @y, 10, 5, 'X')
  end
next

ansi_cursor(true)
ansi_style(REGULAR)
stop

```