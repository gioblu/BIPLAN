### Documentation
- [Bytecode](/documentation/bytecode.md)
- [Configuration](/documentation/configuration.md)
- [Performance](/documentation/performance.md)
- [Comments](/documentation/comments.md) [`//`](/documentation/comments.md)
- [Conditions](/documentation/conditions.md) [`if`](/documentation/conditions.md) [`else`](/documentation/conditions.md) [`end`](/documentation/conditions.md)
- [Constants](/documentation/constants.md) [`true`](/documentation/constants.md) [`false`](/documentation/constants.md) [`HIGH`](/documentation/constants.md) [`LOW`](/documentation/constants.md) [`INPUT`](/documentation/constants.md) [`OUTPUT`](/documentation/constants.md)
- [Cycles](/documentation/cycles.md) [`for`](/documentation/cycles.md#for) [`while`](/documentation/cycles.md#while) [`next`](/documentation/cycles.md#next) [`break`](/documentation/cycles.md#break) [`continue`](/documentation/cycles.md#continue)
- [Functions](/documentation/functions.md) [`function`](/documentation/functions.md) [`locals`](/documentation/functions.md) [`return`](/documentation/functions.md)  [`done`](/documentation/functions.md)
- [Macros](/documentation/macros.md) [`macro`](/documentation/macros.md#pre-processor-macros)
- [Numeric variables](/documentation/numeric-variables.md) [`@`](/documentation/numeric-variables.md) [`@[]`](/documentation/numeric-variables.md)
- [Operators](/documentation/operators.md) [`+`](/documentation/operators.md) [`-`](/documentation/operators.md) [`*`](/documentation/operators.md) [`/`](/documentation/operators.md) [`%`](/documentation/operators.md) [`==`](/documentation/operators.md) [`!=`](/documentation/operators.md) [`>`](/documentation/operators.md) [`>=`](/documentation/operators.md) [`<`](/documentation/operators.md) [`<=`](/documentation/operators.md) [`&&`](/documentation/operators.md) [`||`](/documentation/operators.md) [`&`](/documentation/operators.md) [`|`](/documentation/operators.md) [`^`](/documentation/operators.md) [`>>`](/documentation/operators.md) [`<<`](/documentation/operators.md) [`++`](/documentation/operators.md) [`--`](/documentation/operators.md) [`~`](/documentation/operators.md) [`not`](/documentation/operators.md)
- [Strings](/documentation/strings.md) [`:`](/documentation/strings.md) [`:[]`](/documentation/strings.md)
- [System functions](/documentation/system-functions.md) [`adc read`](/documentation/system-functions.md#adc-read) [`args`](/documentation/system-functions.md#args) [`char`](/documentation/system-functions.md#print) [`cursor`](/documentation/system-functions.md#print) [`delay`](/documentation/system-functions.md#delay) [`file close`](/documentation/system-functions.md#file-close) [`file open`](/documentation/system-functions.md#file-open) [`file read`](/documentation/system-functions.md#file-read) [`file write`](/documentation/system-functions.md#file-write) [`pipe close`](/documentation/system-functions.md#pipe-close) [`pipe open`](/documentation/system-functions.md#pipe-open) [`pipe read`](/documentation/system-functions.md#pipe-read) [`pipe write`](/documentation/system-functions.md#pipe-write) [`include`](/documentation/system-functions.md#include) [`index`](/documentation/system-functions.md#index) [`input`](/documentation/system-functions.md#input) [`io open`](/documentation/system-functions.md#io-open) [`io read`](/documentation/system-functions.md#io-read) [`io write`](/documentation/system-functions.md#digitalWrite) [`mem`](/documentation/system-functions.md#mem)  [`millis`](/documentation/system-functions.md#millis) [`number`](/documentation/system-functions.md#number) [`numeric`](/documentation/system-functions.md#numeric) [`print`](/documentation/system-functions.md#print) [`random`](/documentation/system-functions.md#random) [`restart`](/documentation/system-functions.md#restart) [`serial open`](/documentation/system-functions.md#serial-open) [`serial read`](/documentation/system-functions.md#serial-read) [`serial write`](/documentation/system-functions.md#serial-write) [`size`](/documentation/system-functions.md#size)  [`stop`](/documentation/system-functions.md#stop) [`string`](/documentation/system-functions.md#string)
- [Unary operators](/documentation/unary-operators.md) [`++`](/documentation/unary-operators.md) [`--`](/documentation/unary-operators.md)

## Performance

The table below contains the results of the [benchmarks](/examples/LINUX/benchmarks/) developed to compare 20 different programs implemented in BIPLAN and Python:

| Language | Bytecode size | Compilation | Interpretation | Startup |
| -------- | ------------- | ----------- | -------------- | ------- |
| BIPLAN   | 1.12KB        | 431.58ms    | 2366.70ms      | 7ms     |
| Python   | 8.17KB        | 1631.59ms   | 3172.99ms      | 48ms    |

1. The BIP bytecode format is **7.32 times more compact** than python's `pyc`
2. `biplan` compiles **3.7 times faster** than `python3`
3. `biplan` starts up **6.8 times faster** than `python3`
3. `biplan` interprets **1.3 times faster** than `python3`

BIPLAN is more efficient than Python and many other interpreted languages. It is particularry well suited for applications that require very fast startup time, efficiency, minimal resource footprint and small binary sizes.

When `biplan` is compiled using the target `fast` it is around 30 times faster than python and will compile to bip bytecode that is around 7 times more compact than pyc. To determine the performance of `biplan` I have implemented [benchmarks](/examples/LINUX/benchmarks/) that compare the compilation time and footprint of 20 different programs implemented in BIPLAN and Python, this is the output on my machine:

```
 ______________________________________________________________________
|                                       |                |             |
| Benchmark: Compilation time           | biplan compile | python3     |
|_______________________________________|________________|_____________|
|                                       |                |             |
|  1. Hello world!                      | 18.07ms        | 210.54ms    |
|  2. For loop incrementing global      | 17.62ms        | 69.06ms     |
|  3. For loop nested if                | 17.87ms        | 69.90ms     |
|  4. For prints index                  | 17.66ms        | 69.60ms     |
|  5. While loop incrementing global    | 25.53ms        | 79.40ms     |
|  6. While increment and break         | 18.96ms        | 68.59ms     |
|  7. Read elapsed time cyclically      | 17.86ms        | 69.72ms     |
|  8. Get size of string                | 18.02ms        | 71.99ms     |
|  9. Check if numeric                  | 34.97ms        | 69.32ms     |
| 10. Basic math operations             | 23.40ms        | 82.58ms     |
| 11. Bitwise operations                | 17.75ms        | 70.24ms     |
| 12. Bitshift operations               | 18.43ms        | 69.51ms     |
| 13. Function call within condition    | 19.29ms        | 69.93ms     |
| 14. Function calls another function   | 19.00ms        | 70.61ms     |
| 15. Function leap year                | 17.71ms        | 70.12ms     |
| 16. Write character of string         | 19.17ms        | 69.50ms     |
| 17. Read character of string          | 17.78ms        | 69.37ms     |
| 18. For computing prime numbers       | 37.35ms        | 67.91ms     |
| 19. Non-recursive fibonacci           | 17.93ms        | 70.75ms     |
| 20. Factorial 20                      | 17.30ms        | 74.12ms     |
| 21. Pipes                             | 19.91ms        | 68.81ms     |
|_______________________________________|________________|_____________|
                                          431.58ms         1631.59ms

biplan is 3.78 times faster than python3 compile.

 _________________________________________________________________
|                                      |             |            |
| Benchmark: Bytecode size             |  bip size   |  pyc size  |
|______________________________________|_____________|____________|
|                                      |             |            |
|  1. Hello world!                     | 26B         | 279B       |
|  2. For loop incrementing global     | 21B         | 328B       |
|  3. For loop nested if               | 26B         | 303B       |
|  4. For prints index                 | 18B         | 299B       |
|  5. While loop incrementing global   | 21B         | 308B       |
|  6. While increment and break        | 20B         | 272B       |
|  7. Read elapsed time cyclically     | 21B         | 361B       |
|  8. Get size of string               | 40B         | 307B       |
|  9. Check if numeric                 | 110B        | 323B       |
| 10. Basic math operations            | 60B         | 381B       |
| 11. Bitwise operations               | 53B         | 369B       |
| 12. Bitshift operations              | 30B         | 303B       |
| 13. Function call within condition   | 75B         | 464B       |
| 14. Function calls another function  | 92B         | 607B       |
| 15. Function leap year               | 72B         | 536B       |
| 16. Write character of string        | 68B         | 323B       |
| 17. Read character of string         | 71B         | 322B       |
| 18. For computing prime numbers      | 106B        | 520B       |
| 19. Non-recursive fibonacci          | 61B         | 565B       |
| 20. Factorial 20                     | 47B         | 491B       |
| 21. Pipes                            | 105B        | 702B       |
|______________________________________|_____________|____________|
| Total footprint                      | 1.12KB      | 8.17KB     |
|______________________________________|_____________|____________|

Footprint: bip is 7.32 times smaller than pyc.
```

When `biplan` is compiled using the target `fast` it interprets bip bytecode 1.3 times faster than python. To determine the performance of BIPLAN I have implemented [benchmarks](/examples/LINUX/benchmarks/) that compare the execution time of 20 different programs implemented in BIPLAN and Python, this is the output on my machine:

```
 ________________________________________________________________________________
|                                       |             |             |            |
| Benchmark: Interpretation time        |  BIPLAN     |  Python     | Iterations |
|_______________________________________|_____________|_____________|____________|
|                                       |             |             |            |
|  1. Hello world!                      | 81.55ms     | 135.89ms    | 100000     |
|  2. For loop incrementing global      | 9.62ms      | 71.17ms     | 100000     |
|  3. For loop nested if                | 18.44ms     | 74.04ms     | 100000     |
|  4. For prints index                  | 73.19ms     | 158.94ms    | 100000     |
|  5. While loop incrementing global    | 18.86ms     | 69.60ms     | 10000      |
|  6. While increment and break         | 24.60ms     | 68.55ms     | 10000      |
|  7. Read elapsed time cyclically      | 15.63ms     | 87.61ms     | 100000     |
|  8. Get size of string                | 13.14ms     | 76.14ms     | 100000     |
|  9. Check if numeric                  | 54.20ms     | 71.54ms     | 100000     |
| 10. Basic math operations             | 41.68ms     | 122.57ms    | 100000     |
| 11. Bitwise operations                | 39.43ms     | 113.40ms    | 100000     |
| 12. Bitshift operations               | 22.83ms     | 77.33ms     | 100000     |
| 13. Function call within condition    | 46.56ms     | 86.55ms     | 100000     |
| 14. Function calls another function   | 58.78ms     | 98.93ms     | 100000     |
| 15. Function leap year                | 75.26ms     | 97.41ms     | 100000     |
| 16. Write character of string         | 22.30ms     | 83.99ms     | 100000     |
| 17. Read character of string          | 316.75ms    | 227.03ms    | 100000     |
| 18. For computing prime numbers       | 746.80ms    | 725.51ms    | 100000     |
| 19. Non-recursive fibonacci           | 534.39ms    | 482.48ms    | 100000     |
| 20. Factorial 20                      | 152.60ms    | 244.22ms    | 100000     |
|_______________________________________|_____________|_____________|____________|
                                          2366.70ms     3172.99ms

BIPLAN is 1.34 times faster than Python.
```