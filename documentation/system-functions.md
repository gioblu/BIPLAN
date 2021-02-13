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
- **[System functions](/documentation/system-functions.md)** [`stop`]() [`restart`]() [`char`]() [`sizeof`]() [`print`]() [`delay`]() [`random`]() [`millis`]() [`sqrt`]() [`analogRead`]() [`digitalRead`]() [`digitalWrite`]() [`pinMode`]() [`serialAvailable`]() [`serialRead`]() [`serialWrite`]() [`input`]() [`inputAvailable`]() [`index`]() [`known`]()
- [Unary operators](/documentation/unary-operators.md) [`++`]() [`--`]()

## System functions

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
|  `a`     | `serialAvailable`   | Check if input data is available                       |
|  `c`     | `serialRead`        | Get one character of input data                        |
|  `g`     | `serialWrite`       | Write one character to serial port                     |
|  `e`     | `input`             | Receive data                                           |
|  `i`     | `inputAvailable`    | Check if data is available                             |
