### Documentation
- [Bytecode](/documentation/bytecode.md)
- [Configuration](/documentation/configuration.md)
- [Comments](/documentation/comments.md) [`//`](/documentation/comments.md)
- [Conditions](/documentation/conditions.md) [`if`](/documentation/conditions.md) [`else`](/documentation/conditions.md) [`end`](/documentation/conditions.md)
- [Constants](/documentation/constants.md) [`true`](/documentation/constants.md) [`false`](/documentation/constants.md) [`HIGH`](/documentation/constants.md) [`LOW`](/documentation/constants.md) [`INPUT`](/documentation/constants.md) [`OUTPUT`](/documentation/constants.md)
- [Cycles](/documentation/cycles.md) [`for`](/documentation/cycles.md#for) [`while`](/documentation/cycles.md#while) [`next`](/documentation/cycles.md#next) [`break`](/documentation/cycles.md#break) [`continue`](/documentation/cycles.md#continue)
- **[Functions](/documentation/functions.md)** [`function`](/documentation/functions.md) [`locals`](/documentation/functions.md) [`return`](/documentation/functions.md)  [`done`](/documentation/functions.md)
- [Macros](/documentation/macros.md) [`macro`](/documentation/macros.md#pre-processor-macros)
- [Numeric variables](/documentation/numeric-variables.md) [`@`](/documentation/numeric-variables.md) [`@[]`](/documentation/numeric-variables.md)
- [Operators](/documentation/operators.md) [`+`](/documentation/operators.md) [`-`](/documentation/operators.md) [`*`](/documentation/operators.md) [`/`](/documentation/operators.md) [`%`](/documentation/operators.md) [`==`](/documentation/operators.md) [`!=`](/documentation/operators.md) [`>`](/documentation/operators.md) [`>=`](/documentation/operators.md) [`<`](/documentation/operators.md) [`<=`](/documentation/operators.md) [`&&`](/documentation/operators.md) [`||`](/documentation/operators.md) [`&`](/documentation/operators.md) [`|`](/documentation/operators.md) [`^`](/documentation/operators.md) [`>>`](/documentation/operators.md) [`<<`](/documentation/operators.md) [`++`](/documentation/operators.md) [`--`](/documentation/operators.md) [`~`](/documentation/operators.md) [`not`](/documentation/operators.md)
- [Strings](/documentation/strings.md) [`:`](/documentation/strings.md) [`:[]`](/documentation/strings.md)
- [System functions](/documentation/system-functions.md) [`adc read`](/documentation/system-functions.md#adc-read) [`args`](/documentation/system-functions.md#args) [`char`](/documentation/system-functions.md#print) [`cursor`](/documentation/system-functions.md#print) [`delay`](/documentation/system-functions.md#delay) [`file close`](/documentation/system-functions.md#file-close) [`file open`](/documentation/system-functions.md#file-open) [`file read`](/documentation/system-functions.md#file-read) [`file write`](/documentation/system-functions.md#file-write) [`include`](/documentation/system-functions.md#include) [`index`](/documentation/system-functions.md#index) [`input`](/documentation/system-functions.md#input) [`io open`](/documentation/system-functions.md#io-open) [`io read`](/documentation/system-functions.md#io-read) [`io write`](/documentation/system-functions.md#digitalWrite) [`mem`](/documentation/system-functions.md#mem)  [`millis`](/documentation/system-functions.md#millis) [`number`](/documentation/system-functions.md#number) [`numeric`](/documentation/system-functions.md#numeric) [`print`](/documentation/system-functions.md#print) [`random`](/documentation/system-functions.md#random) [`restart`](/documentation/system-functions.md#restart) [`serial open`](/documentation/system-functions.md#serial-open) [`serial read`](/documentation/system-functions.md#serial-read) [`serial write`](/documentation/system-functions.md#serial-write) [`size`](/documentation/system-functions.md#size)  [`stop`](/documentation/system-functions.md#stop) [`string`](/documentation/system-functions.md#string) [`system`](/documentation/system-functions.md#system)
- [Unary operators](/documentation/unary-operators.md) [`++`](/documentation/unary-operators.md) [`--`](/documentation/unary-operators.md)

## Functions
```

// Call

[name]([function call, relation, expression, term or factor])

// Definition

task [name]([parameter], [parameter], ..., locals: [local], [local], ...)
  [statement]
  emit [function call, relation, expression, term or factor]
done
```
A function is a reusable group of statements identified by a unique name that perform a task and can return a value. BIPLAN supports up to 87 functions, each capable of hosting up to 87 parameters and local variables. Function definitions must be defined after the `stop` keyword.

Function definitions are identified by the `task` keyword followed by a unique name; parameters and local variables are defined within the following parentheses, local variables are defined after the `locals:` keyword. Names of functions and parameters must not start with a number, must be composed by lowercase and or uppercase letters, numbers and or the symbol `_`. The value of uninitialized parameters and local variables is guaranteed to be `0`.

When the `emit` keyword is encountered the function returns the result of the following function call, relation, expression, term or factor. All statements contained in the function definition are executed until `done` is encountered. The `done` statement must be one and must be the last statement of the function.

```c

// Call

average(10, 20); // Returns 15

// Definition

task average($a, $b, locals: $sum)
  $sum = $a + $b
  emit $sum / 2
done
```

Functions can receive only numeric parameters, each parameter can represent a numeric value, a reference to a variable or a reference to a string:

```c
:test = "test"

capitalize(index :test)

print :test // Prints "Test"

stop

task capitalize($string_addr)
  :[$string_addr][0] = :[$string_addr][0] - 32
done
```

In the example above the reference to the string `:test` is passed to the `capitalize` function. The reference is then used to modify the first character.