
#### What is an interface?
BIPLAN uses interfaces to agnostically handle low level system calls using the preprocessor, abstracting all architecture related implementation and enhancing portability without affecting the memory footprint. An interface is simply a file containing a set of common macros pointing to dedicated functions. Interfaces provide users with an easy way to port BIPLAN on virtually every architecture able to execute a compiled C++ program, simply filling a list of method definitions.

Here as an example, the Arduino interface already present in BIPLAN:
```cpp
// Use an architecture related constant to conditionally include the interface
#if defined(ARDUINO)
  #include <Arduino.h>
  #include "BP_IO.h"
  // Architecture related necessary files inclusion

  /* IO methods definition ------------------------------------------------- */

  #if !defined(BP_ANALOG_READ)
    #define BP_ANALOG_READ analogRead
  #endif

  #if !defined(BP_IO_WRITE)
    #define BP_IO_WRITE digitalWrite
  #endif

  #if !defined(BP_IO_READ)
    #define BP_IO_READ digitalRead
  #endif

  #if !defined(BP_IO_MODE)
    #define BP_IO_MODE pinMode
  #endif

  #if !defined(BP_IO_PULL_DOWN)
    #define BP_IO_PULL_DOWN(P) \
      do { \
        digitalWrite(P, LOW); \
        pinMode(P, INPUT); \
      } while(0)
  #endif

  /* Random ----------------------------------------------------------------- */

  #ifndef BP_RANDOM
    #define BP_RANDOM random
  #endif

  #ifndef BP_RANDOM_SEED
    #define BP_RANDOM_SEED randomSeed
  #endif

  /* Serial ----------------------------------------------------------------- */

  #ifndef BP_SERIAL_AVAILABLE
    #define BP_SERIAL_AVAILABLE(S) S->available()
  #endif

  #ifndef BP_SERIAL_WRITE
    #define BP_SERIAL_WRITE(S, C) S->write(C)
  #endif

  #ifndef BP_SERIAL_READ
    #define BP_SERIAL_READ(S) S->read()
  #endif

  #ifndef BP_SERIAL_FLUSH
    #define BP_SERIAL_FLUSH(S) S->flush()
  #endif

  /* Timing ----------------------------------------------------------------- */

  #ifndef BP_DELAY_MICROSECONDS
    #define BP_DELAY_MICROSECONDS delayMicroseconds
  #endif

  #ifndef BP_MICROS
    #define BP_MICROS micros
  #endif
#endif
```
