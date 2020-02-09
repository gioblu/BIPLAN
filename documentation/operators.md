### Documentation
- [Configuration](/documentation/configuration.md)
- [Comments](/documentation/comments.md)
  - [`#`]()  
- [Conditions](/documentation/conditions.md)
  - [`if`]() [`else`]() [`end`]()
- [Constants](/documentation/constants.md)
  - [`true`]() [`false`]() [`HIGH`]() [`LOW`]() [`INPUT`]() [`OUTPUT`]()
- [Cycles](/documentation/cycles.md)
  - [`for`](/documentation/cycles.md#for) [`while`](/documentation/cycles.md#while)
- [Functions](/documentation/functions.md)
  - [`function`]() [`return`]()
- [Numeric variables](/documentation/numeric-variables.md)
  - [`$`]() [`$[]`]()
- **[Operators](/documentation/operators.md)**
  - Arithmetic [`+`]() [`-`]() [`*`]() [`/`]() [`%`]()
  - Logic [`==`]() [`!=`]() [`>`]() [`>=`]() [`<`]() [`<=`]() [`&&`]() [`||`]()
  - Bitwise [`&`]() [`|`]() [`^`]() [`>>`]() [`<<`]()
  - Unary prefix [`++`]() [`--`]() [`~`]() [`not`]()
  - Unary postfix [`++`]() [`--`]()
- [Strings](/documentation/strings.md)
  - [`:`]() [`:[]`]()
- [System functions](/documentation/system-functions.md)
  - [`stop`]() [`restart`]() [`char`]() [`sizeof`]() [`print`]() [`delay`]() [`random`]() [`millis`]() [`sqrt`]() [`analogRead`]() [`digitalRead`]() [`digitalWrite`]() [`pinMode`]() [`serialAvailable`]() [`serialRead`]() [`serialWrite`]() [`input`]() [`inputAvailable`]()
- [Unary operators](/documentation/unary-operators.md)
  - [`++`]() [`--`]()

## Operators

| Arithmetic         | Logic                 | Bitwise          | Unary prefix             |  Unary postfix          |
| ------------------ | --------------------- | ---------------- | ------------------------ | ----------------------- |
| `+` Addition       | `==` Equal            | `&` And          | `++`  Increment then use | `++` use then increment |
| `-` Subtraction    | `!=` Not equal        | `\|` Or           | `--`  Decrement then use | `--` use then decrement |
| `*` Multiplication | `<`  Less             | `^` Xor          | `~`   Bitwise not        |                         |
| `/` Division       | `<=` Less or equal    | `<<` Left shift  | `not` Logic not          |                         |
| `%` Modulus        | `>`  Greater          | `>>` Right shift |                          |                         |
|                    | `>=` Greater or equal |                  |                          |                         |
|                    | `&&` And              |                  |                          |                         |
|                    | `\|\|` Or               |                  |                          |                         |
