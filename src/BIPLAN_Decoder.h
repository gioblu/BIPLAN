
/* BIPLAN CR.1 (Byte coded Interpreted Programming Language)

      _____              _________________________
     |   | |            |_________________________|
     |   | |_______________||__________   \___||_________ |
   __|___|_|               ||          |__|   ||     |   ||
  /________|_______________||_________________||__   |   |D
    (O)                 |_________________________|__|___/|
                                           \ /            |
                                           (O)

  Giovanni Blu Mitolo 2017-2022 - gioscarab@gmail.com
  BIP byte-code decoder */

#pragma once
#include "BIPLAN_Defines.h"
#include <ctype.h>
#include <stdlib.h>

char    *dcd_ptr;
char    *dcd_next_ptr;
uint8_t  dcd_current = BP_ERROR;

/* Checks if the decoder encountered the end of the program ---------------- */
uint8_t dcd_finished() {
  return *dcd_ptr == 0 || dcd_current == BP_ENDOFINPUT;
};

/* Get next code from BIP code --------------------------------------------- */
static uint8_t dcd_next_code() {
  if(
    *dcd_ptr == BP_VAR_ADDR ||
    *dcd_ptr == BP_STR_ADDR ||
    *dcd_ptr == BP_FOR_ADDR ||
    *dcd_ptr == BP_FUNCTION ||
    *dcd_ptr == BP_FUN_DEF  ||
    *dcd_ptr == BP_FOR
  ) {
    dcd_next_ptr = dcd_ptr + 2;
    return *dcd_ptr;
  }
  // if digit (0-9)
  if(*dcd_ptr >= 48 && *dcd_ptr <= 57) {
    for(uint8_t i = 0; i < BP_NUM_MAX; ++i)
      if(dcd_ptr[i] < 48 || dcd_ptr[i] > 57) { // If not digit (0-9)
        dcd_next_ptr = dcd_ptr + i;
        return BP_NUMBER;
      }
    return BP_ERROR;
  }
  if(*dcd_ptr == BP_STRING) {
    dcd_next_ptr = dcd_ptr;
    do {
      if(*dcd_next_ptr++ == BP_BACKSLASH) dcd_next_ptr++;
    } while(*dcd_next_ptr != BP_STRING);
    ++dcd_next_ptr;
    return BP_STRING;
  }
  if(*dcd_ptr > 0) {
    dcd_next_ptr = dcd_ptr + 1;
    return *dcd_ptr;
  } else return BP_ENDOFINPUT;
  return BP_ERROR;
};

/* Gets the next code from BIP code ---------------------------------------- */
#define DCD_NEXT \
  dcd_ptr = dcd_next_ptr; \
  dcd_current = dcd_next_code();

/* Moves decoder to a certain position in the program ---------------------- */
#define DCD_GOTO(P) \
  dcd_ptr = P; \
  dcd_current = dcd_next_code();

/* Initializes the decoder ------------------------------------------------- */
#define DCD_INIT(P) \
  DCD_GOTO(P); \
  dcd_current = dcd_next_code();

/* Ignores a certain code -------------------------------------------------- */
#define DCD_IGNORE(C, V) \
  if(V = (C == dcd_current)) { DCD_NEXT; }

/* Removes backslash from string ------------------------------------------- */
  void remove_backslash(char *s) {
    uint16_t j = 0;
    for(uint16_t i = 0; s[i] != '\0'; i++) {
      if(s[i] != BP_BACKSLASH) {
        s[j] = s[i];
        ++j;
      }
    }
    s[j] = '\0';
  };

/* Decodes a string -------------------------------------------------------- */
bool decoder_string(char *d, uint16_t l) {
  char *string_end;
  uint16_t string_length;
  bool bs = false;
  if(dcd_current != BP_STRING) return false;
  string_end = strchr(dcd_ptr + 1, BP_STRING);
  while(*(string_end - 1) == BP_BACKSLASH && (bs = true))
    string_end = strchr(string_end + 1, BP_STRING);
  if(string_end == NULL) return false;
  string_length = string_end - dcd_ptr - 1;
  if(l < string_length) string_length = l;
  memcpy(d, dcd_ptr + 1, string_length);
  d[string_length] = 0;
  if(bs) remove_backslash(d);
  return true;
};
