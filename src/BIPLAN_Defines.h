
/* ______     ______           ______   _
  |      | | |      | |              | | \    |
  |_____/  | |______| |        ______| |  \   |
  |     \  | |        |       |      | |   \  |
  |______| | |        |______ |______| |    \_|
  Byte coded Interpreted Programming Language
  Giovanni Blu Mitolo 2017-2020 - gioscarab@gmail.com
      _____              _________________________
     |     |            |_________________________|
     |     |_______________||__________    ___||_________ |
   __|_____|               ||          |__|   ||         ||
  /________|_______________||_________________||__       |D
    o                   |_________________________|______/|
                                           \ /            |
                                            O
  BIPLAN Copyright (c) 2017-2019, Giovanni Blu Mitolo All rights reserved.
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

#include "utils/errors/BIPLAN_Errors.h"

/* VARIABLE TYPE - Change if required ------------------------------------- */

#ifndef BP_VAR_TYPE
  #define BP_VAR_TYPE int32_t
#endif

#include "interfaces/BIPLAN_Interfaces.h"

/* VARIABLES AMOUNT - Higher if required ---------------------------------- */

#ifndef BP_VARIABLES
  #define BP_VARIABLES 112
#endif

/* STRINGS AMOUNT - Higher if required ------------------------------------ */

#ifndef BP_STRINGS
  #define BP_STRINGS 20
#endif

/* VARIABLE ADDRESSES INDEXING OFFSET ---------------------------------------
   Default starts from decimal 14 to provide up to 112 (14-126) addresses.
   Use BP_ADDRESS_OFFSET 48 for debugging
 -------------------------------------------------------------------------- */

#ifndef BP_ADDRESS_OFFSET
  #define BP_ADDRESS_OFFSET 48
#endif

/* VARIABLE NAME LENGTH - Higher if required ------------------------------ */

#ifndef BP_MAX_VARIABLE_LENGTH
  #define BP_MAX_VARIABLE_LENGTH 20
#endif

/* MAX FUNCTIONS ---------------------------------------------------------- */

#ifndef BP_MAX_FUNCTIONS
  #define BP_MAX_FUNCTIONS 20
#endif

/* FUNCTION NAME MAXIMUM LENGTH ------------------------------------------- */

#ifndef BP_MAX_FUNCTION_NAME_LENGTH
  #define BP_MAX_FUNCTION_NAME_LENGTH 15
#endif

/* FUNCTION PARAMETERS AMOUNT - Higher if required ------------------------ */

#ifndef BP_PARAMS
  #define BP_PARAMS 6
#endif

/* FUNCTION CALL MAXIMUM DEPTH - Higher if required ----------------------- */

#ifndef BP_FUN_DEPTH
  #define BP_FUN_DEPTH 20
#endif

/* MAXIMUM LENGTH OF NUMBER --------------------------------------------------
   int  or int16_t BP_NUM_MAX_LENGTH = 6
   long or int32_t BP_NUM_MAX_LENGTH = 11 */

#ifndef BP_NUM_MAX_LENGTH
  #define BP_NUM_MAX_LENGTH 6
#endif

/* STRING MAX LENGTH - Higher if required --------------------------------- */

#ifndef BP_STRING_MAX_LENGTH
  #define BP_STRING_MAX_LENGTH 60
#endif

/* FOR MAXIMUM DEPTH - Higher if required --------------------------------- */

#ifndef BP_CYCLE_DEPTH
  #define BP_CYCLE_DEPTH 20
#endif

/* BYTE CODE -------------------------------------------------------------- */
#define BP_ERROR        0
#define BP_ENDOFINPUT   1
                           // Decimal  2
                           // Decimal  3
                           // Decimal  4
                           // Decimal  5
                           // Decimal  6
                           // Decimal  7
                           // Decimal  8
                           // Decimal  9
                           // Decimal 10
                           // Decimal 11
                           // Decimal 12
#define BP_CR         '\n' // Decimal 13
#define BP_ELSE        '!' // Decimal 33
#define BP_STRING      '"' // Decimal 34
#define BP_REM         '#' // Decimal 35
// VARIABLE IN BIPLAN   $     Decimal 36
#define BP_MOD         '%' // Decimal 37
#define BP_AND         '&' // Decimal 38
                           // Decimal 39
#define BP_L_RPARENT   '(' // Decimal 40
#define BP_R_RPARENT   ')' // Decimal 41
#define BP_MULT        '*' // Decimal 42
#define BP_PLUS        '+' // Decimal 43
#define BP_COMMA       ',' // Decimal 44
#define BP_MINUS       '-' // Decimal 45
                           // Decimal 46
#define BP_DIV         '/' // Decimal 47
// NUMBERS              0     Decimal 48
// NUMBERS              1     Decimal 49
// NUMBERS              2     Decimal 50
// NUMBERS              3     Decimal 51
// NUMBERS              4     Decimal 52
// NUMBERS              5     Decimal 53
// NUMBERS              6     Decimal 54
// NUMBERS              7     Decimal 55
// NUMBERS              8     Decimal 56
// NUMBERS              9     Decimal 57
// STRING IN BIPLAN     :     Decimal 58
#define BP_SEMICOLON   ';' // Decimal 59
#define BP_LT          '<' // Decimal 60
// EQUALS TO            =     Decimal 61
#define BP_GT          '>' // Decimal 62
#define BP_IF          '?' // Decimal 63
#define BP_FOR         '@' // Decimal 64
#define BP_LOGIC_AND   'A' // Decimal 65
#define BP_BREAK       'B' // Decimal 66
#define BP_DECREMENT   'C' // Decimal 67
#define BP_DELAY       'D' // Decimal 68
#define BP_DWRITE      'E' // Decimal 69
#define BP_ENDIF       'F' // Decimal 70
#define BP_DREAD       'G' // Decimal 71
#define BP_GTOEQ       'H' // Decimal 72
#define BP_LTOEQ       'I' // Decimal 73
#define BP_AGET        'J' // Decimal 74
#define BP_R_SHIFT     'K' // Decimal 75
#define BP_L_SHIFT     'L' // Decimal 76
#define BP_MILLIS      'M' // Decimal 77
#define BP_BITWISE_NOT 'N' // Decimal 78
#define BP_LOGIC_OR    'O' // Decimal 79
#define BP_PINMODE     'P' // Decimal 80
#define BP_EQ          'Q' // Decimal 81
#define BP_RND         'R' // Decimal 82
#define BP_STR_ACCESS  'S' // Decimal 83
#define BP_NOT_EQ      'T' // Decimal 84
                           // Decimal 85
#define BP_VAR_ACCESS  'V' // Decimal 86
                           // Decimal 87
                           // Decimal 88
                           // Decimal 89
                           // Decimal 90
#define BP_ACCESS      '[' // Decimal 91
//               BACKSLASH    Decimal 92
#define BP_ACCESS_END  ']' // Decimal 93
#define BP_XOR         '^' // Decimal 94
                     // _     Decimal 95
#define BP_INCREMENT   '`' // Decimal 96
#define BP_SERIAL_AV   'a' // Decimal 97
#define BP_CHAR        'b' // Decimal 98
#define BP_CONTINUE    'c' // Decimal 99
                           // Decimal 100
#define BP_INPUT       'e' // Decimal 101
#define BP_FUN_DEF     'f' // Decimal 102
#define BP_SERIAL_TX   'g' // Decimal 103
                           // Decimal 104
#define BP_INPUT_AV    'i' // Decimal 105
                           // Decimal 106
                           // Decimal 107
                           // Decimal 108
#define BP_SIZEOF      'm' // Decimal 109
#define BP_NEXT        'n' // Decimal 110
                           // Decimal 111
#define BP_PRINT       'p' // Decimal 112
#define BP_STOI        'q' // Decimal 113
#define BP_RETURN      'r' // Decimal 114
#define BP_SQRT        's' // Decimal 115
#define BP_S_ADDRESS   't' // Decimal 116
#define BP_SERIAL_RX   'u' // Decimal 117
#define BP_ADDRESS     'v' // Decimal 118
#define BP_WHILE       'w' // Decimal 119
#define BP_END         'x' // Decimal 120
                           // Decimal 121
#define BP_RESTART     'z' // Decimal 122
#define BP_BLOCK       '{' // Decimal 123
#define BP_OR          '|' // Decimal 124
#define BP_BLOCK_END   '}' // Decimal 125
#define BP_FUNCTION    '~' // Decimal 126
                           // Decimal 127
#define BP_NUMBER     128


// #define BP_ABS
// #define BP_MIN
// #define BP_MAX
// #define BP_MAP

// #define BP_AWRITE TODO
// #define BP_SFLUSH TODO
// #define BP_SBEGIN TODO

// #define BP_LOAD Program
// #define BP_SAVE
// #define BP_CLEAR
// #define BP_LIST
// #define BP_RUN

/* DATA TYPES ------------------------------------------------------------- */

typedef void (*error_type)(char *position, const char *string);
