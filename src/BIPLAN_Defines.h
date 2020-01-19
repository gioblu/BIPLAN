
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

/* VARIABLES AMOUNT - Higher if required (MAX 125, 79 helps debugging) ---- */

#ifndef BP_VARIABLES
  #define BP_VARIABLES 79
#endif

/* STRINGS AMOUNT - Higher if required ------------------------------------ */

#ifndef BP_STRINGS
  #define BP_STRINGS 20
#endif

/* VARIABLE ADDRESSES INDEXING OFFSET -------------------------------------- */

#ifndef BP_ADDRESS_OFFSET
  #define BP_ADDRESS_OFFSET (127 - BP_VARIABLES)
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
#define BP_ERROR        0  // Decimal  0  | USED |
#define BP_ENDOFINPUT   1  // Decimal  1  | USED |
                           // Decimal  2  |      |
                           // Decimal  3  |      |
                           // Decimal  4  |      |
                           // Decimal  5  |      |
                           // Decimal  6  |      |
                           // Decimal  7  |      |
                           // Decimal  8  |      |
                           // Decimal  9  |      |
                           // Decimal 10  |      |
                           // Decimal 11  |      |
                           // Decimal 12  |      |
#define BP_CR         '\n' // Decimal 13  |      |
                           // Decimal 14  |      |
                           // Decimal 15  |      |
                           // Decimal 16  |      |
                           // Decimal 17  |      |
                           // Decimal 18  |      |
                           // Decimal 19  |      |
                           // Decimal 20  |      |
                           // Decimal 21  |      |
                           // Decimal 22  |      |
                           // Decimal 23  |      |
                           // Decimal 24  |      |
                           // Decimal 25  |      |
                           // Decimal 26  |      |
                           // Decimal 27  |      |
                           // Decimal 28  |      |
                           // Decimal 29  |      |
                           // Decimal 30  |      |
                           // Decimal 31  |      |
                    // SPACE  Decimal 32  |      |
#define BP_ELSE        '!' // Decimal 33  | USED |
#define BP_STRING      '"' // Decimal 34  | USED |
#define BP_REM         '#' // Decimal 35  | USED |
                     // $     Decimal 36  |      |
#define BP_MOD         '%' // Decimal 37  | USED |
#define BP_AND         '&' // Decimal 38  | USED |
                     // '     Decimal 39  |      |
#define BP_L_RPARENT   '(' // Decimal 40  | USED |
#define BP_R_RPARENT   ')' // Decimal 41  | USED |
#define BP_MULT        '*' // Decimal 42  | USED |
#define BP_PLUS        '+' // Decimal 43  | USED |
#define BP_COMMA       ',' // Decimal 44  | USED |
#define BP_MINUS       '-' // Decimal 45  | USED |
                     // .     Decimal 46  |      |
#define BP_DIV         '/' // Decimal 47  | USED |
// NUMBERS              0     Decimal 48  | USED |
// NUMBERS              1     Decimal 49  | USED |
// NUMBERS              2     Decimal 50  | USED |
// NUMBERS              3     Decimal 51  | USED |
// NUMBERS              4     Decimal 52  | USED |
// NUMBERS              5     Decimal 53  | USED |
// NUMBERS              6     Decimal 54  | USED |
// NUMBERS              7     Decimal 55  | USED |
// NUMBERS              8     Decimal 56  | USED |
// NUMBERS              9     Decimal 57  | USED |
                     // :     Decimal 58  |      |
#define BP_SEMICOLON   ';' // Decimal 59  | USED |
#define BP_LT          '<' // Decimal 60  | USED |
                     // =     Decimal 61  |      |
#define BP_GT          '>' // Decimal 62  | USED |
#define BP_IF          '?' // Decimal 63  | USED |
#define BP_FOR         '@' // Decimal 64  | USED |
#define BP_LOGIC_AND   'A' // Decimal 65  | USED |
#define BP_BREAK       'B' // Decimal 66  | USED |
#define BP_DECREMENT   'C' // Decimal 67  | USED |
#define BP_DELAY       'D' // Decimal 68  | USED |
#define BP_DWRITE      'E' // Decimal 69  | USED |
#define BP_ENDIF       'F' // Decimal 70  | USED |
#define BP_DREAD       'G' // Decimal 71  | USED |
#define BP_GTOEQ       'H' // Decimal 72  | USED |
#define BP_LTOEQ       'I' // Decimal 73  | USED |
#define BP_AGET        'J' // Decimal 74  | USED |
#define BP_R_SHIFT     'K' // Decimal 75  | USED |
#define BP_L_SHIFT     'L' // Decimal 76  | USED |
#define BP_MILLIS      'M' // Decimal 77  | USED |
#define BP_BITWISE_NOT 'N' // Decimal 78  | USED |
#define BP_LOGIC_OR    'O' // Decimal 79  | USED |
#define BP_PINMODE     'P' // Decimal 80  | USED |
#define BP_EQ          'Q' // Decimal 81  | USED |
#define BP_RND         'R' // Decimal 82  | USED |
#define BP_STR_ACCESS  'S' // Decimal 83  | USED |
#define BP_NOT_EQ      'T' // Decimal 84  | USED |
                     // U     Decimal 85  |      |
#define BP_VAR_ACCESS  'V' // Decimal 86  | USED |
                     // W     Decimal 87  |      |
                     // X     Decimal 88  |      |
                     // Y     Decimal 89  |      |
                     // Z     Decimal 90  |      |
#define BP_ACCESS      '[' // Decimal 91  | USED |
//               BACKSLASH    Decimal 92  | USED |
#define BP_ACCESS_END  ']' // Decimal 93  | USED |
#define BP_XOR         '^' // Decimal 94  | USED |
                     // _     Decimal 95  |      |
#define BP_INCREMENT   '`' // Decimal 96  | USED |
#define BP_SERIAL_AV   'a' // Decimal 97  | USED |
#define BP_CHAR        'b' // Decimal 98  | USED |
#define BP_CONTINUE    'c' // Decimal 99  | USED |
                     // d     Decimal 100 |      |
#define BP_INPUT       'e' // Decimal 101 | USED |
#define BP_FUN_DEF     'f' // Decimal 102 | USED |
#define BP_SERIAL_TX   'g' // Decimal 103 | USED |
                     // h     Decimal 104 |      |
#define BP_INPUT_AV    'i' // Decimal 105 | USED |
                     // j     Decimal 106 |      |
                     // k     Decimal 107 |      |
                     // l     Decimal 108 |      |
#define BP_SIZEOF      'm' // Decimal 109 | USED |
#define BP_NEXT        'n' // Decimal 110 | USED |
                     // o     Decimal 111 |      |
#define BP_PRINT       'p' // Decimal 112 | USED |
#define BP_STOI        'q' // Decimal 113 | USED |
#define BP_RETURN      'r' // Decimal 114 | USED |
#define BP_SQRT        's' // Decimal 115 | USED |
#define BP_S_ADDRESS   't' // Decimal 116 | USED |
#define BP_SERIAL_RX   'u' // Decimal 117 | USED |
#define BP_ADDRESS     'v' // Decimal 118 | USED |
#define BP_WHILE       'w' // Decimal 119 | USED |
#define BP_END         'x' // Decimal 120 | USED |
                     // y     Decimal 121 |      |
#define BP_RESTART     'z' // Decimal 122 | USED |
#define BP_BLOCK       '{' // Decimal 123 | USED |
#define BP_OR          '|' // Decimal 124 | USED |
#define BP_BLOCK_END   '}' // Decimal 125 | USED |
#define BP_FUNCTION    '~' // Decimal 126 | USED |
                           // Decimal 127 |      |
#define BP_NUMBER     128  // Decimal 128 | USED |

// TODO
// #define BP_AWRITE
// #define BP_SFLUSH
// #define BP_SBEGIN

// EVAL
// #define BP_ABS
// #define BP_MIN
// #define BP_MAX
// #define BP_MAP

/* DATA TYPES ------------------------------------------------------------- */

typedef void (*error_type)(char *position, const char *string);
