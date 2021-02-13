### Documentation
- [Configuration](/documentation/configuration.md)
- [Comments](/documentation/comments.md) [`#`]()  
- [Conditions](/documentation/conditions.md) [`if`]() [`else`]() [`end`]()
- [Constants](/documentation/constants.md) [`true`]() [`false`]() [`HIGH`]() [`LOW`]() [`INPUT`]() [`OUTPUT`]()
- [Cycles](/documentation/cycles.md) [`for`](/documentation/cycles.md#for) [`while`](/documentation/cycles.md#while) [`next`](/documentation/cycles.md#next) [`break`](/documentation/cycles.md#break) [`continue`](/documentation/cycles.md#continue)
- [Functions](/documentation/functions.md) [`function`]() [`return`]()
- **[Numeric variables](/documentation/numeric-variables.md)** [`$`]() [`$[]`]()
- [Operators](/documentation/operators.md) [`+`]() [`-`]() [`*`]() [`/`]() [`%`]() [`==`]() [`!=`]() [`>`]() [`>=`]() [`<`]() [`<=`]() [`&&`]() [`||`]() [`&`]() [`|`]() [`^`]() [`>>`]() [`<<`]() [`++`]() [`--`]() [`~`]() [`not`]()
- [Strings](/documentation/strings.md) [`:`]() [`:[]`]()
- [System functions](/documentation/system-functions.md) [`stop`]() [`restart`]() [`char`]() [`sizeof`]() [`print`]() [`delay`]() [`random`]() [`millis`]() [`sqrt`]() [`analogRead`]() [`digitalRead`]() [`digitalWrite`]() [`pinMode`]() [`serialAvailable`]() [`serialRead`]() [`serialWrite`]() [`input`]() [`inputAvailable`]() [`index`]() 
- [Unary operators](/documentation/unary-operators.md) [`++`]() [`--`]()

## Numeric variables
BIPLAN supports only one numeric variable type that is by default `int32_t` but can be easily changed, see [configuration](/documentation/configuration.md). Numeric variables are identified by `$`, their name must be composed by lowercase and or uppercase letters and must not contain symbols or numbers. Each variable is just an entry of a global array of variables. BIPLAN supports a maximum amount of 116 global variables. Variables can be defined using a name:
```php
$test = 10
```
Variables can be accessed by name:
```php
print $test # Prints "10"
```
All Variables can be accessed as part of one single array using `$[]`:
```php
$test = 111
print $[0] # Prints 111 or the value of the first variable defined
$[0] = 2
print $[0] # Prints 2
```
The index of a variable can be obtained prepending its name with `index`:
```php
$a_variable = 10 # index 0
$variable = 1    # index 1
$var = 22        # index 2

print index $var # Prints 2 or the index of $var
```
