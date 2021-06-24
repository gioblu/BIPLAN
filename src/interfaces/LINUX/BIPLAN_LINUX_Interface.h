
/* BIPLAN Linux Interface
   13/04/2020 - callalilychen, Use termios2 for generic baudrate support
   ___________________________________________________________________________

    Copyright Giovanni Blu Mitolo and Fred Larsen

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

#if defined(LINUX) || defined(ANDROID)
  #include <string.h>
  #include <unistd.h>
  #include <fcntl.h>
  #include <sys/ioctl.h>
  #include <thread>
  #include <math.h>
  #include <stdio.h>

  #define OUTPUT 1
  #define INPUT 0
  #define HIGH 1
  #define LOW 0
  #define INPUT_PULLUP 0x2
  #define LSBFIRST 1
  #define MSBFIRST 2

  uint32_t micros();

  uint32_t millis();

  void delayMicroseconds(uint32_t delay_value);

  void delay(uint32_t delay_value_ms);

  /* Open serial port ----------------------------------------------------- */

  int serialOpen(const char *device, const int baud);

  /* Returns the number of bytes of data available to be read in the buffer */

  int serialDataAvailable(const int fd);

  /* Reads a character from the serial buffer ----------------------------- */

  int serialGetCharacter(const int fd);

  /* itoa ----------------------------------------------------------------- */
  char *custom_itoa(int num, char *str);

  #ifndef BPM_LINUX_SEPARATE_DEFINITION
    #include "BIPLAN_LINUX_Interface.inl"
  #endif

  /* String conversion ---------------------------------------------------- */

  #ifndef BPM_ITOA
    #define BPM_ITOA fast_itoa
  #endif

  #ifndef BPM_ATOL
    #define BPM_ATOL fast_atol
  #endif

  #ifndef BPM_LTOA
    #define BPM_LTOA(B, L) sprintf(B, "%ld", L);
  #endif

  /* Generic constants ---------------------------------------------------- */

  #ifndef A0
    #define A0 0
  #endif

  #ifndef LED_BUILTIN
    #define LED_BUILTIN -1
  #endif

  /* LINUX IO system calls ------------------------------------------------ */


  #if !defined(BPM_AREF)
    #define BPM_AREF(R)
  #endif

  #if !defined(BPM_AREAD)
    #define BPM_AREAD(R) 0
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

  /* Print ---------------------------------------------------------------- */

  #ifndef BPM_PRINT_T
    #define BPM_PRINT_T int
  #endif

  #ifndef BPM_PRINT_WRITE
    #define BPM_PRINT_WRITE(S, C) std::cerr << C
  #endif

  #ifndef BPM_PRINT_CLEAR
    #define BPM_PRINT_CLEAR printf("\e[1;1H\e[2J");
  #endif

  #ifndef BPM_PRINT_CURSOR
    #define BPM_PRINT_CURSOR(X, Y) printf("\033[%d;%dH", (Y), (X));
  #endif

  /* Serial --------------------------------------------------------------- */

  #ifndef BPM_SERIAL_T
    #define BPM_SERIAL_T int16_t
  #endif

  #ifndef BPM_SERIAL_WRITE
    #define BPM_SERIAL_WRITE(S, C) write(S, &C, 1)
  #endif

  #ifndef BPM_SERIAL_READ
    #define BPM_SERIAL_READ(S) serialGetCharacter(S)
  #endif

  #ifndef BPM_SERIAL_FLUSH
    #define BPM_SERIAL_FLUSH(S) tcflush(S, TCIOFLUSH)
  #endif

  /* User input ----------------------------------------------------------- */

  #ifndef BPM_INPUT_T
    #define BPM_INPUT_T int
  #endif

  #ifndef BPM_INPUT
    #define BPM_INPUT(S) getchar_unlocked()
  #endif

  /* Files ---------------------------------------------------------------- */

  #ifndef BPM_FILE_T
    #define BPM_FILE_T FILE
  #endif

  #ifndef BPM_FILE_OPEN
    #define BPM_FILE_OPEN(T, P, M) \
      switch(M) { \
        case 0:  T = fopen(P, "r");   break; \
        case 1:  T = fopen(P, "rb");  break; \
        case 2:  T = fopen(P, "r+");  break; \
        case 3:  T = fopen(P, "rb+"); break; \
        case 4:  T = fopen(P, "w");   break; \
        case 5:  T = fopen(P, "wb");  break; \
        case 6:  T = fopen(P, "w+");  break; \
        case 7:  T = fopen(P, "wb+"); break; \
        case 8:  T = fopen(P, "a");   break; \
        case 9:  T = fopen(P, "ab");  break; \
        case 10: T = fopen(P, "a+");  break; \
        case 11: T = fopen(P, "ab+"); break; \
      };
  #endif

  #ifndef BPM_FILE_WRITE
    #define BPM_FILE_WRITE(T, V) fprintf(T,"%c", V);
  #endif

  #ifndef BPM_FILE_READ
    #define BPM_FILE_READ(T) fgetc(T);
  #endif

  #ifndef BPM_FILE_CLOSE
    #define BPM_FILE_CLOSE(T) fclose(T);
  #endif

  /* System --------------------------------------------------------------- */

  #ifndef BPM_SYSTEM
    #define BPM_SYSTEM(P) system(P)
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
