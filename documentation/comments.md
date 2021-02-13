### Documentation
- [Configuration](/documentation/configuration.md)
- **[Comments](/documentation/comments.md)** [`#`]()  
- [Conditions](/documentation/conditions.md) [`if`]() [`else`]() [`end`]()
- [Constants](/documentation/constants.md) [`true`]() [`false`]() [`HIGH`]() [`LOW`]() [`INPUT`]() [`OUTPUT`]()
- [Cycles](/documentation/cycles.md) [`for`](/documentation/cycles.md#for) [`while`](/documentation/cycles.md#while) [`next`](/documentation/cycles.md#next) [`break`](/documentation/cycles.md#break) [`continue`](/documentation/cycles.md#continue)
- [Functions](/documentation/functions.md) [`function`]() [`return`]()
- [Numeric variables](/documentation/numeric-variables.md) [`$`]() [`$[]`]()
- [Operators](/documentation/operators.md) [`+`]() [`-`]() [`*`]() [`/`]() [`%`]() [`==`]() [`!=`]() [`>`]() [`>=`]() [`<`]() [`<=`]() [`&&`]() [`||`]() [`&`]() [`|`]() [`^`]() [`>>`]() [`<<`]() [`++`]() [`--`]() [`~`]() [`not`]()
- [Strings](/documentation/strings.md) [`:`]() [`:[]`]()
- [System functions](/documentation/system-functions.md) [`stop`](/documentation/system-functions.md#stop) [`restart`](/documentation/system-functions.md#restart) [`char`](/documentation/system-functions.md#print) [`sizeof`](/documentation/system-functions.md#sizeof) [`print`](/documentation/system-functions.md#print) [`delay`](/documentation/system-functions.md#delay) [`random`](/documentation/system-functions.md#random) [`millis`](/documentation/system-functions.md#millis) [`sqrt`](/documentation/system-functions.md#sqrt) [`analogRead`](/documentation/system-functions.md#analogRead) [`digitalRead`](/documentation/system-functions.md#digitalRead) [`digitalWrite`](/documentation/system-functions.md#digitalWrite) [`pinMode`](/documentation/system-functions.md#pinMode) [`serialRead`](/documentation/system-functions.md#serialRead) [`serialWrite`](/documentation/system-functions.md#serialWrite) [`input`](/documentation/system-functions.md#input) [`index`](/documentation/system-functions.md#index) [`jump`](/documentation/system-functions.md#jump)
- [Unary operators](/documentation/unary-operators.md) [`++`]() [`--`]()

## Comments
Comments are human-readable notes present in the source-code. They will be ignored by the compiler. The `#` symbol signals the start of a comment. A comment can make use of an entire line:
```php
# This is a comment
```
or can be placed after a statement:
```php
print "Hello world!" # This is another comment
```
