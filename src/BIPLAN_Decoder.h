
/* BIPLAN CR.1 (Byte coded Interpreted Programming Language)

      _____              _________________________
     |   | |            |_________________________|
     |   | |_______________||__________   \___||_________ |
   __|___|_|               ||          |__|   ||     |   ||
  /________|_______________||_________________||__   |   |D
    (O)                 |_________________________|__|___/|
                                           \ /            |
                                           (O)

  Giovanni Blu Mitolo 2017-2025 - gioscarab@gmail.com
  BIP bytecode decoder */

#pragma once
#include "BIPLAN_Defines.h"

char    *dcd_ptr;
char    *dcd_next_ptr;
uint8_t  dcd_current = BP_ENDOFINPUT;

/* Get next code from BIP code --------------------------------------------- */
BP_FUN_T void dcd_next_code() {
  if(
    *dcd_ptr == BP_VAR_ADDR ||
    *dcd_ptr == BP_STR_ADDR ||
    *dcd_ptr == BP_FOR_ADDR ||
    *dcd_ptr == BP_FUNCTION ||
    *dcd_ptr == BP_FUN_DEF  ||
    *dcd_ptr == BP_FOR
  ) {
    dcd_next_ptr = dcd_ptr + 2;
    dcd_current =  *dcd_ptr;
  }
  // if digit (0-9)
  else if(*dcd_ptr >= 48 && *dcd_ptr <= 57) {
    for(uint8_t i = 0; i < BP_NUM_MAX; ++i)
      if(dcd_ptr[i] < 48 || dcd_ptr[i] > 57) { // If not digit (0-9)
        dcd_next_ptr = dcd_ptr + i;
        dcd_current = BP_NUMBER;
        break;
      }
  }
  else if(*dcd_ptr == BP_STRING) {
    dcd_next_ptr = dcd_ptr;
    do {
      if(*dcd_next_ptr++ == BP_BACKSLASH) dcd_next_ptr++;
    } while(*dcd_next_ptr != BP_STRING);
    ++dcd_next_ptr;
    dcd_current = BP_STRING;
  } else {
    dcd_current = *dcd_ptr;
    if(*dcd_ptr > 0) dcd_next_ptr = dcd_ptr + 1;
  }
};

/* Moves decoder to a certain position in the program ---------------------- */
#define DCD_GOTO(P) \
  dcd_ptr = P; \
  dcd_next_code();

/* Ignores a certain code -------------------------------------------------- */
#define DCD_IGNORE(C, V) \
  if(V = (C == dcd_current)) { DCD_NEXT; }

/* Initializes the decoder ------------------------------------------------- */
#define DCD_INIT(P) \
  DCD_GOTO(P); \
  dcd_next_code();

/* Gets the next code from BIP code ---------------------------------------- */
#define DCD_NEXT \
  dcd_ptr = dcd_next_ptr; \
  dcd_next_code();

/* Removes backslashes from strings ---------------------------------------- */
void remove_backslash(char *s) {
  char *src = s;
  char *dst = s;
  while(*src != 0) {
    if((uint8_t)*src == BP_BACKSLASH && (uint8_t)*(src + 1) == BP_STRING) {
      src++;
      continue;
    }
    *dst++ = *src++;
  }
  *dst = 0;
}

/* Decodes a string from BIP bytecode in memory ---------------------------- */
bool decoder_string(char *d, uint16_t l) {
  char *string_end = strchr(dcd_ptr + 1, BP_STRING);
  bool backslash = false;
  while(string_end && *(string_end - 1) == BP_BACKSLASH) {
    backslash = true;
    string_end = strchr(string_end + 1, BP_STRING);
  }
  if(!string_end) return false;
  uint16_t string_length = string_end - dcd_ptr - 1;
  if(l == 0 || string_length >= l) return false;
  memcpy(d, dcd_ptr + 1, string_length);
  d[string_length] = 0;
  if(backslash) remove_backslash(d);
  return true;
}