
/* PJON RaspeberryPi Interface
   _____________________________________________________________________________

    Copyright 2018 Giovanni Blu Mitolo gioscarab@gmail.com

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

#if defined(RPI)
  #include <inttypes.h>
  #include <stdlib.h>
  #include <string.h>
  #include <wiringPi.h>
  #include <wiringSerial.h>

  /* Generic constants ---------------------------------------------------- */

  #ifndef A0
    #define A0 0
  #endif

  #ifndef LED_BUILTIN
    #define LED_BUILTIN -1
  #endif

  /* Fallback to WiringPi core functions ---------------------------------- */

  #if !defined(BPM_AREF)
    #define BPM_AREF(R)
  #endif

  #if !defined(BPM_AREAD)
    #define BPM_AREAD(P) analogRead(P)
  #endif

  #if !defined(BPM_IO_WRITE)
    #define BPM_IO_WRITE digitalWrite
  #endif

  #if !defined(BPM_IO_READ)
    #define BPM_IO_READ digitalRead
  #endif

  #if !defined(BPM_IO_MODE)
    #define BPM_IO_MODE pinMode
  #endif

  #if !defined(BPM_IO_PULL_DOWN)
    #define BPM_IO_PULL_DOWN(P) { \
      BPM_IO_MODE(P, INPUT); \
      pullUpDnControl(P, PUD_DOWN); \
    }
  #endif

  /* Random ----------------------------------------------------------------- */

  #ifndef BPM_RANDOM
    #define BPM_RANDOM(randMax) (int)((1.0 + randMax) * rand() / ( RAND_MAX + 1.0 ) )
    /* Scale rand()'s return value against RAND_MAX using doubles instead of
       a pure modulus to have a more distributed result */
  #endif

  #ifndef BPM_RANDOM_SEED
    #define BPM_RANDOM_SEED srand
  #endif

  /* Serial ----------------------------------------------------------------- */

  #ifndef BPM_PRINT_TYPE
    #define BPM_PRINT_TYPE int16_t 
  #endif

  #ifndef BPM_SERIAL_AVAILABLE
    #define BPM_SERIAL_AVAILABLE(S) serialDataAvail(S)
  #endif

  #ifndef BPM_SERIAL_WRITE
    #define BPM_SERIAL_WRITE(S, C) serialPutchar(S, C)
  #endif

  #ifndef BPM_SERIAL_READ
    #define BPM_SERIAL_READ(S) serialGetchar(S)
  #endif

  #ifndef BPM_SERIAL_FLUSH
    #define BPM_SERIAL_FLUSH(S) serialFlush(S)
  #endif

  /* Timing ----------------------------------------------------------------- */

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
