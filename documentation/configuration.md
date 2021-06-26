### Documentation
- **[Configuration](/documentation/configuration.md)**
- [Comments](/documentation/comments.md) [`#`](/documentation/comments.md)
- [Conditions](/documentation/conditions.md) [`if`](/documentation/conditions.md) [`else`](/documentation/conditions.md) [`end`](/documentation/conditions.md)
- [Constants](/documentation/constants.md) [`true`](/documentation/constants.md) [`false`](/documentation/constants.md) [`HIGH`](/documentation/constants.md) [`LOW`](/documentation/constants.md) [`INPUT`](/documentation/constants.md) [`OUTPUT`](/documentation/constants.md)
- [Cycles](/documentation/cycles.md) [`for`](/documentation/cycles.md#for) [`while`](/documentation/cycles.md#while) [`next`](/documentation/cycles.md#next) [`break`](/documentation/cycles.md#break) [`continue`](/documentation/cycles.md#continue)
- [Functions](/documentation/functions.md) [`function`](/documentation/functions.md) [`locals`](/documentation/functions.md) [`result`](/documentation/functions.md) [`return`](/documentation/functions.md)
- [Numeric variables](/documentation/numeric-variables.md) [`$`](/documentation/numeric-variables.md) [`$[]`](/documentation/numeric-variables.md)
- [Operators](/documentation/operators.md) [`+`](/documentation/operators.md) [`-`](/documentation/operators.md) [`*`](/documentation/operators.md) [`/`](/documentation/operators.md) [`%`](/documentation/operators.md) [`==`](/documentation/operators.md) [`!=`](/documentation/operators.md) [`>`](/documentation/operators.md) [`>=`](/documentation/operators.md) [`<`](/documentation/operators.md) [`<=`](/documentation/operators.md) [`&&`](/documentation/operators.md) [`||`](/documentation/operators.md) [`&`](/documentation/operators.md) [`|`](/documentation/operators.md) [`^`](/documentation/operators.md) [`>>`](/documentation/operators.md) [`<<`](/documentation/operators.md) [`++`](/documentation/operators.md) [`--`](/documentation/operators.md) [`~`](/documentation/operators.md) [`not`](/documentation/operators.md)
- [Strings](/documentation/strings.md) [`:`](/documentation/strings.md) [`:[]`](/documentation/strings.md)
- [System functions](/documentation/system-functions.md) [`adc read`](/documentation/system-functions.md#adc-read) [`char`](/documentation/system-functions.md#print) [`delay`](/documentation/system-functions.md#delay) [`file close`](/documentation/system-functions.md#file-close) [`file open`](/documentation/system-functions.md#file-open) [`file read`](/documentation/system-functions.md#file-read) [`file write`](/documentation/system-functions.md#file-write) [`jump`](/documentation/system-functions.md#jump) [`io open`](/documentation/system-functions.md#io-open) [`io read`](/documentation/system-functions.md#io-read) [`io write`](/documentation/system-functions.md#digitalWrite) [`index`](/documentation/system-functions.md#index) [`input`](/documentation/system-functions.md#input) [`millis`](/documentation/system-functions.md#millis) [`print`](/documentation/system-functions.md#print) [`random`](/documentation/system-functions.md#random) [`restart`](/documentation/system-functions.md#restart) [`serial open`](/documentation/system-functions.md#serial-open) [`serial read`](/documentation/system-functions.md#serial-read) [`serial write`](/documentation/system-functions.md#serial-write) [`size`](/documentation/system-functions.md#size) [`sqrt`](/documentation/system-functions.md#sqrt) [`stop`](/documentation/system-functions.md#stop) [`system`](/documentation/system-functions.md#system)
- [Unary operators](/documentation/unary-operators.md) [`++`](/documentation/unary-operators.md) [`--`](/documentation/unary-operators.md)

## Configuration

### Numeric variables
BIPLAN supports only one numeric variable type that is by default `long` but can be easily changed with the use of constants:
```cpp
// Sets the BIPLAN numeric type to int
#define BP_VAR_T int
#include "BIPLAN.h"
```
Each variable is just an entry of a statically allocated array. The `BP_VARIABLES` constant can be used as shown below to configure the maximum amount of variables available:
```cpp
#define BP_VARIABLES 50
#include "BIPLAN.h"
```
BIPLAN supports up to 92 variables defined by the user, such as `$my_var = 1` although it can get or set more variables using the access operator [`$[]`](/documentation/numeric-variables.md).

---

### Strings
Each string is just an entry of a statically allocated array, the `BP_STRINGS` constant can be used as shown below to configure the maximum amount of strings available:
```cpp
#define BP_STRINGS 50
#include "BIPLAN.h"
```
BIPLAN supports up to 92 strings defined by the user, such as `:my_string = "Hello world!"` although it can get or set more strings using the access operator [`:[]`](/documentation/strings.md). The maximum length of strings can be configured as follows:
```cpp
// Sets BIPLAN string maximum length to 50
#define BP_STRING_MAX 50
#include "BIPLAN.h"
```

---

### Functions
Each function is just an entry of a global array of functions. The `BP_FUNCTIONS` constant can be used as shown below to configure the maximum amount of functions available:
```cpp
#define BP_FUNCTIONS 50
#include "BIPLAN.h"
```
The maximum amount of parameters available can be configured as follows:
```cpp
#define BP_PARAMS 5
#include "BIPLAN.h"
```
The maximum function call depth can be configured as follows:
```cpp
#define BP_FUN_DEPTH 5
#include "BIPLAN.h"
```
BIPLAN supports a maximum amount of 92 functions defined by the user.

---
### Keyword length
You can configure the maximum length of user-defined keywords using the `BP_KEYWORD_MAX` as follows:

```cpp
#ifndef BP_KEYWORD_MAX
  #define BP_KEYWORD_MAX 20
#endif
```
