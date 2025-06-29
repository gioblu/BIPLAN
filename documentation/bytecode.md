### Documentation
- **[Bytecode](/documentation/bytecode.md)**
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
- [System functions](/documentation/system-functions.md) [`adc read`](/documentation/system-functions.md#adc-read) [`args`](/documentation/system-functions.md#args) [`char`](/documentation/system-functions.md#print) [`cursor`](/documentation/system-functions.md#print) [`delay`](/documentation/system-functions.md#delay) [`file close`](/documentation/system-functions.md#file-close) [`file open`](/documentation/system-functions.md#file-open) [`file read`](/documentation/system-functions.md#file-read) [`file write`](/documentation/system-functions.md#file-write) [`include`](/documentation/system-functions.md#include) [`index`](/documentation/system-functions.md#index) [`input`](/documentation/system-functions.md#input) [`io open`](/documentation/system-functions.md#io-open) [`io read`](/documentation/system-functions.md#io-read) [`io write`](/documentation/system-functions.md#digitalWrite) [`mem`](/documentation/system-functions.md#mem)  [`millis`](/documentation/system-functions.md#millis) [`number`](/documentation/system-functions.md#number) [`numeric`](/documentation/system-functions.md#numeric) [`print`](/documentation/system-functions.md#print) [`random`](/documentation/system-functions.md#random) [`restart`](/documentation/system-functions.md#restart) [`serial open`](/documentation/system-functions.md#serial-open) [`serial read`](/documentation/system-functions.md#serial-read) [`serial write`](/documentation/system-functions.md#serial-write) [`size`](/documentation/system-functions.md#size)  [`stop`](/documentation/system-functions.md#stop) [`string`](/documentation/system-functions.md#string) [`system`](/documentation/system-functions.md#system)
- [Unary operators](/documentation/unary-operators.md) [`++`](/documentation/unary-operators.md) [`--`](/documentation/unary-operators.md)

## Bytecode
When you compile a BIPLAN program with BCC, you are just translating your program in a more compact form designed to be efficiently interpreted.

For example, this is a short BIPLAN program of 45 characters:
```c
print "Hello World!"
@a = 3 + 3
print @a
stop
```
This is the program above compiled in 24 characters of BIP bytecode:
```
p"Hello World!"}$3+3p}$x
```
When executed prints:
```
Hello World!6
```

The BIP bytecode is just an ASCII string, so it does not require any tool to browse it, analize it or transmit it. BIP bytecode is saved in .bip files, that can be browsed as any other text file.

Using the ASCII encoding and representing addresses with one character restricts their number to 87. The first 34 characters are not used and 6 (`:`, `f`, `~`, `}`, `#`, `@` ) are reserved. This is why BIPLAN can work with a maximum of 87 functions, variables, parameters, strings and cycles.

Not to drastically limit the memory available BIP bytecode supports a memory read and write instruction that expects a numeric address, so depending on the machine you are running BIPLAN on, you may be able to address 2^32 or 2^64 bytes of memory.

| Description                                           | Character | Decimal |
| --------------------------------------------------------------- | --- | --- |
| [`else`](/documentation/conditions.md)                          | `!` | 33  |
| `literal string separator`                                      | `"` | 34  |
| `for variable` (followed by address)                            | `#` | 35  |
|                                                                 | `$` | 36  |
| modulus                                                         | `%` | 37  |
| bitwise and                                                     | `&` | 38  |
|                                                                 | `'` | 39  |
| open round parenthesis                                          | `(` | 40  |
| closed round parenthesis                                        | `)` | 41  |
| multiplication                                                  | `*` | 42  |
| addition                                                        | `+` | 43  |
| value separator                                                 | `,` | 44  |
| subtraction                                                     | `-` | 45  |
|                                                                 | `.` | 46  |
| division                                                        | `/` | 47  |
| number                                                          | `0` | 48  |
| number                                                          | `1` | 49  |
| number                                                          | `2` | 50  |
| number                                                          | `3` | 51  |
| number                                                          | `4` | 52  |
| number                                                          | `5` | 53  |
| number                                                          | `6` | 54  |
| number                                                          | `7` | 55  |
| number                                                          | `8` | 56  |
| number                                                          | `9` | 57  |
| [`:`](/documentation/strings.md) (followed by address)          | `:` | 58  |
| [`next`](/documentation/cycles.md#next)                         | `;` | 59  |
| less than                                                       | `<` | 60  |
|                                                                 | `=` | 61  |
| greater than                                                    | `>` | 62  |
| [`if`](/documentation/conditions.md)                            | `?` | 63  |
| [`for`](/documentation/cycles.md#for) (followed by address)     | `@` | 64  |
| `logic and`                                                     | `A` | 65  |
| [`break`](/documentation/cycles.md#break)                       | `B` | 66  |
| [`--`](/documentation/unary-operators.md)                       | `C` | 67  |
| [`delay`](/documentation/system-functions.md#delay)             | `D` | 68  |
| [`io`](/documentation/system-functions.md#io-open)              | `E` | 69  |
| [`end`](/documentation/conditions.md)                           | `F` | 70  |
|                                                                 | `G` | 71  |
| greater or equal                                                | `H` | 72  |
| less than or equal                                              | `I` | 73  |
| [`adc`](/documentation/system-functions.md#adc-read)            | `J` | 74  |
| bit shift right                                                 | `K` | 75  |
| bit shift left                                                  | `L` | 76  |
| [`millis`](/documentation/system-functions.md#millis)           | `M` | 77  |
| bitwise not                                                     | `N` | 78  |
| logic or                                                        | `O` | 79  |
|                                                                 | `P` | 80  |
| `==` equals to                                                  | `Q` | 81  |
| [`random`](/documentation/system-functions.md#random)           | `R` | 82  |
| [`:[]`](/documentation/strings.md)                              | `S` | 83  |
| not equal                                                       | `T` | 84  |
| [`mem`](/documentation/system-functions#mem.md)                 | `U` | 85  |
| [`@[]`](/documentation/numeric-variables.md)                    | `V` | 86  |
|                                                                 | `W` | 87  |
|                                                                 | `X` | 88  |
|                                                                 | `Y` | 89  |
|                                                                 | `Z` | 90  |
| `[`                                                             | `[` | 91  |
| backslash                                                       | `\` | 92  |
| `]`                                                             | `]` | 93  |
| `^`                                                             | `^` | 94  |
|                                                                 | `_` | 97  |
| [`++`](/documentation/unary-operators.md)                       | `` ` ``| 96 |
| [`index`](/documentation/system-functions.md#index)             | `a` | 97  |
| [`char`](/documentation/system-functions.md#print)              | `b` | 98  |
| [`continue`](/documentation/cycles.md#continue)                 | `c` | 99  |
|                                                                 | `d` | 100 |
| [`input`](/documentation/system-functions.md#input)             | `e` | 101 |
| [`function`](/documentation/functions.md) (followed by address) | `f` | 102 |
| [`serial`](/documentation/system-functions.md#serial-open)      | `g` | 103 |
| [`string`](/documentation/system-functions.md#string)           | `h` | 104 |
|                                                                 | `i` | 105 |
|                                                                 | `j` | 106 |
| [`system`](/documentation/system-functions.md#system)           | `k` | 107 |
|                                                                 | `l` | 108 |
| [`size`](/documentation/system-functions.md#size)               | `m` | 109 |
|                                                                 | `n` | 110 |
| [`file`](/documentation/system-functions.md#file-open)          | `o` | 111 |
| [`print`](/documentation/system-functions.md#print)             | `p` | 112 |
| [`number`](/documentation/system-functions.md#number)           | `q` | 113 |
| [`return`](/documentation/functions.md)                         | `r` | 114 |
|                                                                 | `s` | 115 |
|                                                                 | `t` | 116 |
|                                                                 | `u` | 117 |
|                                                                 | `v` | 118 |
| [`while`](/documentation/cycles.md#while)                       | `w` | 119 |
| [`end`](/documentation/conditions.md)                           | `x` | 120 |
| [`cursor`](/documentation/system-functions.md#print)            | `y` | 121 |
| [`restart`](/documentation/system-functions.md#restart)         | `z` | 122 |
|                                                                 | `{` | 123 |
| bitwise or                                                      | `\|`| 124 |
| numeric variable, function parameter (followed by address)      | `}` | 125 |
| function call (followed by address)                             | `~` | 126 |
|                                                                 | DEL | 127 |