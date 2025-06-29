
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
uint8_t  dcd_current = BP_ERROR;

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
    if(dcd_current != BP_NUMBER)
      dcd_current = BP_ERROR;
  }
  else if(*dcd_ptr == BP_STRING) {
    dcd_next_ptr = dcd_ptr;
    do {
      if(*dcd_next_ptr++ == BP_BACKSLASH) dcd_next_ptr++;
    } while(*dcd_next_ptr != BP_STRING);
    ++dcd_next_ptr;
    dcd_current = BP_STRING;
  }
  else if(*dcd_ptr > 0) {
    dcd_next_ptr = dcd_ptr + 1;
    dcd_current = *dcd_ptr;
  } else dcd_current = BP_ENDOFINPUT;
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

/* Removes backslash from string ------------------------------------------- */
  void remove_backslash(char *s) {
    uint16_t j = 0;
    for(uint16_t i = 0; s[i] != '\0'; i++) {
      if((s[i] == BP_BACKSLASH) && (s[i + 1] == BP_STRING)) continue;
      s[j] = s[i];
      ++j;
    }
    s[j] = '\0';
  };

/* Decodes a string -------------------------------------------------------- */
bool decoder_string(char *d, uint16_t l, uint16_t o = 0) {
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
  memcpy(d + o, dcd_ptr + 1, string_length);
  d[string_length + o] = 0;
  if(bs) remove_backslash(d);
  return true;
};
