
/* BIPLAN Windows x86 Interface
   _____________________________________________________________________________

    Copyright Giovanni Blu Mitolo and Zbigniew Zasieczny

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

#if defined(_WIN32)

  #include <chrono>
  #include <thread>
  #include <sstream>
  #include "Serial/Serial.h"

  #define OUTPUT 1
  #define INPUT 0
  #define HIGH 1
  #define LOW 0
  #define INPUT_PULLUP 0x2
  #define LSBFIRST 1
  #define MSBFIRST 2

  auto start_ts = std::chrono::high_resolution_clock::now();
  auto start_ts_ms = std::chrono::high_resolution_clock::now();

  uint32_t micros() {
    auto elapsed_usec =
      std::chrono::duration_cast<std::chrono::microseconds>(
        std::chrono::high_resolution_clock::now() - start_ts
      ).count();

    if(elapsed_usec >= UINT32_MAX) {
      start_ts = std::chrono::high_resolution_clock::now();
      return 0;
    } else return (uint32_t) elapsed_usec;
  };

  uint32_t millis() {
    return (uint32_t)
      std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now() - start_ts_ms
      ).count();
  };


  void delayMicroseconds(uint32_t delay_value) {
    auto begin_ts = std::chrono::high_resolution_clock::now();
    while(true) {
      auto elapsed_usec =
        std::chrono::duration_cast<std::chrono::microseconds>(
          std::chrono::high_resolution_clock::now() - begin_ts
        ).count();
      if(elapsed_usec >= delay_value) break;
      std::this_thread::sleep_for(std::chrono::microseconds(50));
    }
  };

  void delay(uint32_t delay_value_ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(delay_value_ms));
  }

  /* String conversion ---------------------------------------------------- */

  #ifndef BPM_ATOL
    #define BPM_ATOL atol
  #endif

  /* Generic constants ---------------------------------------------------- */

  #ifndef A0
    #define A0 0
  #endif

  #ifndef LED_BUILTIN
    #define LED_BUILTIN -1
  #endif

  /* Fallback to WINDOWS-specific functions ------------------------------- */

  #if !defined(BPM_AREF)
    #define BPM_AREF(R)
  #endif

  #if !defined(BPM_AREAD)
    #define BPM_AREAD(P) 0
  #endif

  #if !defined(BPM_IO_WRITE)
    #define BPM_IO_WRITE(P, V)
  #endif

  #if !defined(BPM_IO_READ)
    #define BPM_IO_READ(P) 0
  #endif

  #if !defined(BPM_IO_MODE)
    #define BPM_IO_MODE(P, V)
  #endif

  #if !defined(BPM_IO_PULL_DOWN)
    #define BPM_IO_PULL_DOWN(P)
  #endif

  /* Random --------------------------------------------------------------- */

  #ifndef BPM_RANDOM
    #define BPM_RANDOM(rmx) (int)((1.0 + rmx) * rand() / ( RAND_MAX + 1.0 ) )
    /* Scale rand()'s return value against RAND_MAX using doubles instead of
       a pure modulus to have a more distributed result */
  #endif

  #ifndef BPM_RANDOM_SEED
    #define BPM_RANDOM_SEED srand
  #endif


  /* User input ----------------------------------------------------------- */

  #ifndef BPM_INPUT_TYPE
    #define BPM_INPUT_TYPE Stream * // Not sure what should go here on win
  #endif

  #ifndef BPM_INPUT
    #define BPM_INPUT(S) S->read()
  #endif

  /* Print ---------------------------------------------------------------- */

  #ifndef BPM_PRINT_TYPE
    #define BPM_PRINT_TYPE Stream * // Not sure what should go here on win
  #endif

  #ifndef BPM_PRINT_WRITE
    #define BPM_PRINT_WRITE(S, C) S->print(C)
  #endif

  #ifndef BPM_PRINT_FLUSH
    #define BPM_PRINT_FLUSH(S) S->flush()
  #endif

  /* Serial --------------------------------------------------------------- */

  #ifndef BPM_SERIAL_TYPE
    #define BPM_SERIAL_TYPE Serial *
  #endif

  #ifndef BPM_SERIAL_WRITE
    #define BPM_SERIAL_WRITE(S, C) S->writeByte(&C)
  #endif

  #ifndef BPM_SERIAL_READ
    #define BPM_SERIAL_READ(S) S->getByte()
  #endif

  #ifndef BPM_SERIAL_FLUSH
    #define BPM_SERIAL_FLUSH(S) S->flush()
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
