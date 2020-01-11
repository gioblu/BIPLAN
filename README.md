
# BIPLAN v0.0
BIPLAN (Byte-coded Interpreted Programming Language) is an experimental programming language based on a recursive descent parser that uses only static memory allocation and operates a completely software-defined architecture that does not require a garbage collector.

| Programming language | Minimum requirements |
| -------------------- | -------------------- |
| TinyBasicPlus        |  11KB ROM,  1KB RAM  |
| BIPLAN               |  12KB ROM,  1KB RAM  |
| MycroPython          | 256KB ROM, 16KB RAM  |
| Lua                  | 256KB ROM, 64kB RAM  |

BIPLAN comes with a modern syntax inspired by Ruby on Rails and Python and it is expressly designed to operate efficiently on microcontrollers with limited resources although its implementation is designed to be easily extended and applied in other architectures or real time operative systems.

## documentation
- [Configuration](documentation/configuration.md)
- [Comments](documentation/comments.md)
- [Conditions](documentation/conditions.md)
- [Constants](documentation/constants.md)
- [Cycles](documentation/cycles.md)
- [Functions](documentation/functions.md)
- [Numeric variables](documentation/numeric-variables.md)
- [Operators](documentation/operators.md)
- [Strings](documentation/strings.md)
- [System functions](documentation/system-functions.md)
- [Unary operators](documentation/unary-operators.md)

## TODO

- REMOVE CR
- next - redo becomes only next
- function must have end statement
- reset variable functions loops and registers states on reset
