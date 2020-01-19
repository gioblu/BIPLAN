### Documentation
- **[Configuration](/documentation/configuration.md)**
- [Comments](/documentation/comments.md)
- [Conditions](/documentation/conditions.md)
- [Constants](/documentation/constants.md)
- [Cycles](/documentation/cycles.md)
- [Functions](/documentation/functions.md)
- [Numeric variables](/documentation/numeric-variables.md)
- [Operators](/documentation/operators.md)
- [Strings](/documentation/strings.md)
- [System functions](/documentation/system-functions.md)
- [Unary operators](/documentation/unary-operators.md)

## Configuration

### Numeric variables
BIPLAN supports only one numeric variable type that is by default `int32_t` but can be easily changed with the use of contants:
```cpp
// Sets the BIPLAN numeric type to uint32_t
#define BP_VAR_TYPE uint32_t
#include "BIPLAN.h"
```
Each variable is just an entry of a global array of variables. The `BP_VARIABLES` constant can be used as shown below to configure the maximum amount of variables available:
```cpp
#define BP_VARIABLES 50
#include "BIPLAN.h"
```
BIPLAN supports a maximum amount of 125 global variables.

The maximum length of variable names can be configured as follows:
```cpp
#define BP_MAX_VARIABLE_LENGTH 10
#include "BIPLAN.h"
```

### Strings
BIPLAN has a static buffer of strings, which maximum length can be easily configured as follows:
```cpp
// Sets BIPLAN strings maximum length to 50
#define BP_STRING_MAX_LENGTH 50
#include "BIPLAN.h"
```
Each string is just an entry of a global array of string. The `BP_STRINGS` constant can be used as shown below to configure the maximum amount of strings available:
```cpp
#define BP_STRINGS 50
#include "BIPLAN.h"
```
BIPLAN supports a maximum amount of 125 global strings.

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
The maximum length of function names can be configured as follows:
```cpp
#define BP_MAX_FUNCTION_NAME_LENGTH 10
#include "BIPLAN.h"
```
