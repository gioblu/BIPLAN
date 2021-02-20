
/* ______     ______           ______   _
  |      | | |      | |              | | \    |
  |_____/  | |______| |        ______| |  \   |
  |     \  | |        |       |      | |   \  |
  |______| | |        |______ |______| |    \_| CR.1
  Byte coded Interpreted Programming Language
  Giovanni Blu Mitolo 2017-2020 - gioscarab@gmail.com
      _____              _________________________
     |   | |            |_________________________|
     |   | |_______________||__________   \___||_________ |
   __|___|_|               ||          |__|   ||     |   ||
  /________|_______________||_________________||__   |   |D
    (O)                 |_________________________|__|___/|
                                           \ /            |
                                           (O)
  BIPLAN Copyright (c) 2017-2020, Giovanni Blu Mitolo All rights reserved.
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
#include "BCC.h"
#include <ctype.h>
#include <stdlib.h>

char    *decoder_ptr;
char    *decoder_next_ptr;
uint8_t  decoder_current = BP_ERROR;

/* DECODER FINISHED ------------------------------------------------------- */
uint8_t decoder_finished() {
  return *decoder_ptr == 0 || decoder_current == BP_ENDOFINPUT;
};

/* GET CURRENT CODE ------------------------------------------------------- */
uint8_t decoder_get() { return decoder_current; };

/* DECODER POSITION ------------------------------------------------------- */
char *decoder_position() { return decoder_ptr; };

/* GET NEXT CODE ---------------------------------------------------------- */
uint8_t get_next_code() {
  // if digit (0-9)
  if(*decoder_ptr >= 48 && *decoder_ptr <= 57) {
    for(uint8_t i = 0; i < BP_NUM_MAX_LENGTH; ++i)
      if(decoder_ptr[i] < 48 || decoder_ptr[i] > 57) { // If not digit (0-9)
        decoder_next_ptr = decoder_ptr + i;
        return BP_NUMBER;
      }
    return BP_ERROR;
  }
  if(*decoder_ptr == BP_STRING) {
    decoder_next_ptr = decoder_ptr;
    do {
      ++decoder_next_ptr;
    } while(*decoder_next_ptr != BP_STRING);
    ++decoder_next_ptr;
    return BP_STRING;
  }
  if(
    *decoder_ptr == BP_ADDRESS ||
    *decoder_ptr == BP_S_ADDRESS ||
    *decoder_ptr == BP_FUNCTION ||
		*decoder_ptr == BP_FUN_DEF
  ) {
    decoder_next_ptr = decoder_ptr + 2;
    return *decoder_ptr;
  }
  if(*decoder_ptr > 0) {
    decoder_next_ptr = decoder_ptr + 1;
    return *decoder_ptr;
  } else return BP_ENDOFINPUT;
  return BP_ERROR;
};

/* GET NEXT CODE ---------------------------------------------------------- */
void decoder_next() {
  decoder_ptr = decoder_next_ptr;
  decoder_current = get_next_code();
};

/* MOVE DECODER TO A CERTAIN ZONE OF THE PROGRAM -------------------------- */
void decoder_goto(char *program) {
  decoder_ptr = program;
  decoder_current = get_next_code();
};

/* INITIALIZE DECODER ----------------------------------------------------- */
void decoder_init(char *program) {
  decoder_goto(program);
  decoder_current = get_next_code();
};

/* DECODE STRING ---------------------------------------------------------- */
void decoder_string(char *d, uint16_t l) {
  char *string_end;
  uint16_t string_length;
  if(decoder_current != BP_STRING) return;
  string_end = strchr(decoder_ptr + 1, BP_STRING);
  if(string_end == NULL) return;
  string_length = string_end - decoder_ptr - 1;
  if(l < string_length) string_length = l;
  memcpy(d, decoder_ptr + 1, string_length);
  d[string_length] = 0;
};
