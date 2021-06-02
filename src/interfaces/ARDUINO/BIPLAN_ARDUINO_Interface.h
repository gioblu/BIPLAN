
/* BIPLAN Arduino Interface
   ___________________________________________________________________________

    Copyright 2018-2019 Giovanni Blu Mitolo gioscarab@gmail.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License. */

#pragma once

#if defined(ARDUINO)
  #include "Arduino.h"

  /* String conversion ---------------------------------------------------- */

  #ifndef BPM_ATOL
    #define BPM_ATOL atol
  #endif

  /* Arduino IO system calls ---------------------------------------------- */

  #ifndef BPM_AREF
    #define BPM_AREF analogReference
  #endif

  #ifndef BPM_AREAD
    #define BPM_AREAD analogRead
  #endif

  #ifndef BPM_IO_WRITE
    #define BPM_IO_WRITE digitalWrite
  #endif

  #ifndef BPM_IO_READ
    #define BPM_IO_READ digitalRead
  #endif

  #ifndef BPM_IO_MODE
    #define BPM_IO_MODE pinMode
  #endif

  /* Random --------------------------------------------------------------- */

  #ifndef BPM_RANDOM
    #define BPM_RANDOM random
  #endif

  #ifndef BPM_RANDOM_SEED
    #define BPM_RANDOM_SEED randomSeed
  #endif

  /* Print ---------------------------------------------------------------- */

  #ifndef BPM_PRINT_T
    #define BPM_PRINT_T Stream *
  #endif

  #ifndef BPM_PRINT_WRITE
    #define BPM_PRINT_WRITE(S, C) S->print(C)
  #endif

  #ifndef BPM_PRINT_FLUSH
    #define BPM_PRINT_FLUSH(S) S->flush()
  #endif

  /* Serial --------------------------------------------------------------- */

  #ifndef BPM_SERIAL_T
    #define BPM_SERIAL_T Stream *
  #endif

  #ifndef BPM_SERIAL_AVAILABLE
    #define BPM_SERIAL_AVAILABLE(S) S->available()
  #endif

  #ifndef BPM_SERIAL_READ
    #define BPM_SERIAL_READ(S) S->read()
  #endif

  #ifndef BPM_SERIAL_WRITE
    #define BPM_SERIAL_WRITE(S, D) S->write(D)
  #endif

  /* User input ----------------------------------------------------------- */

  #ifndef BPM_INPUT_T
    #define BPM_INPUT_T Stream *
  #endif

  #ifndef BPM_INPUT
    #define BPM_INPUT(S) S->read()
  #endif

  /* Timing --------------------------------------------------------------- */

  #ifndef BPM_DELAY
    #define BPM_DELAY delay
  #endif

  #ifndef BPM_DELAY_MICROSECONDS
    #define BPM_DELAY_MICROSECONDS delayMicroseconds
  #endif

  #ifndef BPM_MICROS
    #define BPM_MICROS micros
  #endif

  #ifndef BPM_MILLIS
    #define BPM_MILLIS millis
  #endif

#endif
