### Documentation
- [Configuration](/documentation/configuration.md)
- [Comments](/documentation/comments.md) [`#`]()  
- [Conditions](/documentation/conditions.md) [`if`]() [`else`]() [`end`]()
- [Constants](/documentation/constants.md) [`true`]() [`false`]() [`HIGH`]() [`LOW`]() [`INPUT`]() [`OUTPUT`]()
- [Cycles](/documentation/cycles.md) [`for`](/documentation/cycles.md#for) [`while`](/documentation/cycles.md#while) [`next`](/documentation/cycles.md#next) [`break`](/documentation/cycles.md#break) [`continue`](/documentation/cycles.md#continue)
- [Functions](/documentation/functions.md) [`function`]() [`return`]()
- [Numeric variables](/documentation/numeric-variables.md) [`$`]() [`$[]`]()
- [Operators](/documentation/operators.md) [`+`]() [`-`]() [`*`]() [`/`]() [`%`]() [`==`]() [`!=`]() [`>`]() [`>=`]() [`<`]() [`<=`]() [`&&`]() [`||`]() [`&`]() [`|`]() [`^`]() [`>>`]() [`<<`]() [`++`]() [`--`]() [`~`]() [`not`]()
- **[Strings](/documentation/strings.md)** [`:`]() [`:[]`]()
- [System functions](/documentation/system-functions.md) [`stop`](/documentation/system-functions.md#stop) [`restart`](/documentation/system-functions.md#restart) [`char`](/documentation/system-functions.md#print) [`sizeof`](/documentation/system-functions.md#sizeof) [`print`](/documentation/system-functions.md#print) [`delay`](/documentation/system-functions.md#delay) [`random`](/documentation/system-functions.md#random) [`millis`](/documentation/system-functions.md#millis) [`sqrt`](/documentation/system-functions.md#sqrt) [`analogRead`](/documentation/system-functions.md#analogRead) [`digitalRead`](/documentation/system-functions.md#digitalRead) [`digitalWrite`](/documentation/system-functions.md#digitalWrite) [`pinMode`](/documentation/system-functions.md#pinMode) [`serialRead`](/documentation/system-functions.md#serialRead) [`serialWrite`](/documentation/system-functions.md#serialWrite) [`input`](/documentation/system-functions.md#input) [`index`](/documentation/system-functions.md#index) [`jump`](/documentation/system-functions.md#jump)
- [Unary operators](/documentation/unary-operators.md) [`++`]() [`--`]()

## Strings
String are identified by `:`, their name must be composed by lowercase and or uppercase letters and must not contain symbols or numbers. Each string is just an entry of a global array of strings.
```php
:test = "Hello world!"
```
String can be accessed by name:
```php
print :test # Prints "Hello world!"
```
All strings can be accessed as part of one single array using `:[]`:
```php
print :[0] # Prints "Hello world!"
# or the value of :test (first string defined in the program)
```
Characters of strings can be accessed as shown below:
```php
:test = "Hello world!"
print :test[0] # Prints "H"
```
The index of a string can be obtained prepending its name with `index`:
```php
:a_string = "Hello world" # index 0
:b_string = "World"       # index 1
:c_string = "Hello"       # index 2

print index :c_string # Prints 2 or the index of :c_string
```
