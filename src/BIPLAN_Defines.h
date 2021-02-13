
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

#include "utils/errors/BIPLAN_Errors.h"

/* VARIABLE TYPE - Change if required (signed only) ----------------------- */

#ifndef BP_VAR_TYPE
  #define BP_VAR_TYPE long
#endif

#ifndef BP_VAR_MAX
  #define BP_VAR_MAX (BP_VAR_TYPE)((unsigned BP_VAR_TYPE) ~ 0 >> 1)
#endif

#include "interfaces/BIPLAN_Interfaces.h"

/* KEYWORD MAXIMUM LENGTH ------------------------------------------------- */

#ifndef BP_MAX_KEYWORD_LENGTH
  #define BP_MAX_KEYWORD_LENGTH 20
#endif

/* ADDRESSES INDEXING OFFSET ---------------------------------------------- */

#ifndef BP_OFFSET
  #define BP_OFFSET 35
#endif

/* VARIABLES AMOUNT - Higher if required (MAX 92) ------------------------- */

#ifndef BP_VARIABLES
  #define BP_VARIABLES 50
#endif

/* STRINGS AMOUNT - Higher if required (MAX 92) --------------------------- */

#ifndef BP_STRINGS
  #define BP_STRINGS 20
#endif

/* FUNCTIONS AMOUNT - Higher if required (MAX 92) ------------------------- */

#ifndef BP_MAX_FUNCTIONS
  #define BP_MAX_FUNCTIONS 20
#endif

/* FUNCTION PARAMETERS AMOUNT - Higher if required ------------------------ */

#ifndef BP_PARAMS
  #define BP_PARAMS 6
#endif

/* FUNCTION CALL MAXIMUM DEPTH - Higher if required ----------------------- */

#ifndef BP_FUN_DEPTH
  #define BP_FUN_DEPTH 20
#endif

/* MAXIMUM LENGTH OF NUMBER ----------------------------------------------- */

#ifndef BP_NUM_MAX_LENGTH
  #define BP_NUM_MAX_LENGTH 20 // Handle 64 bits machine limit
#endif

/* STRING MAX LENGTH - Higher if required --------------------------------- */

#ifndef BP_STRING_MAX_LENGTH
  #define BP_STRING_MAX_LENGTH 60
#endif

/* FOR MAXIMUM DEPTH - Higher if required --------------------------------- */

#ifndef BP_CYCLE_DEPTH
  #define BP_CYCLE_DEPTH 20
#endif

/* MACHINE AND HUMAN-READABLE LANGUAGE SYNTAX -----------------------------
_______________________________________________________________________
 CONSTANT NAME                                    | DECIMAL     | USED |
__________________________________________________|_____________|______| */
#define BP_ERROR              0                   //  0         | USED |
#define BP_ENDOFINPUT         1                   //  1         | USED |
                                                  //  2         |      |
                                                  //  3         |      |
                                                  //  4         |      |
                                                  //  5         |      |
                                                  //  6         |      |
                                                  //  7         |      |
                                                  //  8         |      |
                                                  //  9         |      |
                                                  // 10         |      |
                                                  // 11         |      |
                                                  // 12         |      |
#define BP_CR               '\n'                  // 13         |      |
                                                  // 14         |      |
                                                  // 15         |      |
                                                  // 16         |      |
                                                  // 17         |      |
                                                  // 18         |      |
                                                  // 19         |      |
                                                  // 20         |      |
                                                  // 21         |      |
                                                  // 22         |      |
                                                  // 23         |      |
                                                  // 24         |      |
                                                  // 25         |      |
                                                  // 26         |      |
                                                  // 27         |      |
                                                  // 28         |      |
                                                  // 29         |      |
                                                  // 30         |      |
                                                  // 31         |      |
//______________________________________________________________|______|
#define BP_SPACE             ' '                  // 32         | USED |
// USED BY HUMAN-READABLE AS SEPARATOR            //            |      |
//______________________________________________________________|______|
#define BP_ELSE              '!'                  // 33         | USED |
#define BP_ELSE_HUMAN        "else "              //            |      |
//______________________________________________________________|______|
#define BP_STRING            '"'                  // 34         | USED |
//______________________________________________________________|______|
#define BP_REM               '#'                  // 35         | USED |
//______________________________________________________________|______|
#define BP_ADDRESS           '$'                  // 36         | USED |
// USED IN HUMAN-READABLE AS VARIABLE ID          //            |      |
//______________________________________________________________|______|
#define BP_MOD               '%'                  // 37         | USED |
//______________________________________________________________|______|
#define BP_AND               '&'                  // 38         | USED |
//______________________________________________________________|______|
                          //  '                      39         |      |
//______________________________________________________________|______|
#define BP_L_RPARENT         '('                  // 40         | USED |
//______________________________________________________________|______|
#define BP_R_RPARENT         ')'                  // 41         | USED |
//______________________________________________________________|______|
#define BP_MULT              '*'                  // 42         | USED |
//______________________________________________________________|______|
#define BP_PLUS              '+'                  // 43         | USED |
//______________________________________________________________|______|
#define BP_COMMA             ','                  // 44         | USED |
//______________________________________________________________|______|
#define BP_MINUS             '-'                  // 45         | USED |
//______________________________________________________________|______|
                           // .                   // 46         |      |
//______________________________________________________________|______|
#define BP_DIV               '/'                  // 47         | USED |
//______________________________________________________________|______|
// NUMBERS                    0                   // 48         | USED |
// NUMBERS                    1                   // 49         | USED |
// NUMBERS                    2                   // 50         | USED |
// NUMBERS                    3                   // 51         | USED |
// NUMBERS                    4                   // 52         | USED |
// NUMBERS                    5                   // 53         | USED |
// NUMBERS                    6                   // 54         | USED |
// NUMBERS                    7                   // 55         | USED |
// NUMBERS                    8                   // 56         | USED |
// NUMBERS                    9                   // 57         | USED |
//______________________________________________________________|______|
#define BP_S_ADDRESS         ':'                  // 58         | USED |
// USED IN BOTH HUMAN-READABLE AND MACHINE LANGUAGE FOR STRING  |      |
//______________________________________________________________|______|
#define BP_SEMICOLON         ';'                  // 59         | USED |
//______________________________________________________________|______|
#define BP_LT                '<'                  // 60         | USED |
//______________________________________________________________|______|
#define BP_ASSIGN_HUMAN      '='                  // 61         | USED |
// USED IN HUMAN-READABLE FOR ASSIGNMENT          //            |      |
//______________________________________________________________|______|
#define BP_GT                '>'                  // 62         | USED |
//______________________________________________________________|______|
#define BP_IF                '?'                  // 63         | USED |
#define BP_IF_HUMAN          "if"                 //            |      |
//______________________________________________________________|______|
#define BP_FOR               '@'                  // 64         | USED |
#define BP_FOR_HUMAN         "for"                //            |      |
//______________________________________________________________|______|
#define BP_LOGIC_AND         'A'                  // 65         | USED |
#define BP_LOGIC_AND_HUMAN   "&&"                 //            |      |
//______________________________________________________________|______|
#define BP_BREAK             'B'                  // 66         | USED |
#define BP_BREAK_HUMAN       "break"              //            |      |
//______________________________________________________________|______|
#define BP_DECREMENT         'C'                  // 67         | USED |
#define BP_DECREMENT_HUMAN   "--"                 //            |      |
//______________________________________________________________|______|
#define BP_DELAY             'D'                  // 68         | USED |
#define BP_DELAY_HUMAN       "delay"              //            |      |
//______________________________________________________________|______|
#define BP_DWRITE            'E'                  // 69         | USED |
#define BP_DWRITE_HUMAN      "digitalWrite"       //            |      |
//______________________________________________________________|______|
#define BP_ENDIF             'F'                  // 70         | USED |
#define BP_ENDIF_HUMAN       "end"                //            |      |
//______________________________________________________________|______|
#define BP_DREAD             'G'                  // 71         | USED |
#define BP_DREAD_HUMAN       "digitalRead"        //            |      |
//______________________________________________________________|______|
#define BP_GTOEQ             'H'                  // 72         | USED |
#define BP_GTOEQ_HUMAN       ">="                 //            |      |
//______________________________________________________________|______|
#define BP_LTOEQ             'I'                  // 73         | USED |
#define BP_LTOEQ_HUMAN       "<="                 //            |      |
//______________________________________________________________|______|
#define BP_AGET              'J'                  // 74         | USED |
#define BP_AGET_HUMAN        "analogRead"         //            |      |
//______________________________________________________________|______|
#define BP_R_SHIFT           'K'                  // 75         | USED |
#define BP_R_SHIFT_HUMAN     ">>"                 //            |      |
//______________________________________________________________|______|
#define BP_L_SHIFT           'L'                  // 76         | USED |
#define BP_L_SHIFT_HUMAN     "<<"                 //            |      |
//______________________________________________________________|______|
#define BP_MILLIS            'M'                  // 77         | USED |
#define BP_MILLIS_HUMAN      "millis"             //            |      |
//______________________________________________________________|______|
#define BP_BITWISE_NOT       'N'                  // 78         | USED |
#define BP_BITWISE_NOT_HUMAN "~"                  //            |      |
//______________________________________________________________|______|
#define BP_LOGIC_OR          'O'                  // 79         | USED |
#define BP_LOGIC_OR_HUMAN    "||"                 //            |      |
//______________________________________________________________|______|
#define BP_PINMODE           'P'                  // 80         | USED |
#define BP_PINMODE_HUMAN     "pinMode"            //            |      |
//______________________________________________________________|______|
#define BP_EQ                'Q'                  // 81         | USED |
#define BP_EQ_HUMAN          "=="                 //            |      |
//______________________________________________________________|______|
#define BP_RND               'R'                  // 82         | USED |
#define BP_RND_HUMAN         "random"             //            |      |
//______________________________________________________________|______|
#define BP_STR_ACCESS        'S'                  // 83         | USED |
#define BP_STR_ACCESS_HUMAN ":["                  //            |      |
//______________________________________________________________|______|
#define BP_NOT_EQ            'T'                  // 84         | USED |
#define BP_NOT_EQ_HUMAN      "!="                 //            |      |
//______________________________________________________________|______|
                           // U                      85         |      |
//______________________________________________________________|______|
#define BP_VAR_ACCESS        'V'                  // 86         | USED |
#define BP_VAR_ACCESS_HUMAN  "$["                 //            |      |
//______________________________________________________________|______|
                           // W                   // 87         |      |
                           // X                   // 88         |      |
                           // Y                   // 89         |      |
                           // Z                   // 90         |      |
//______________________________________________________________|______|
#define BP_ACCESS            '['                  // 91         | USED |
//______________________________________________________________|______|
//                     BACKSLASH                  // 92         | USED |
//______________________________________________________________|______|
#define BP_ACCESS_END        ']'                  // 93         | USED |
//______________________________________________________________|______|
#define BP_XOR               '^'                  // 94         | USED |
//______________________________________________________________|______|
#define BP_INDEX             '_'                  // 95         | USED |
#define BP_INDEX_HUMAN       "index"              //            |      |
//______________________________________________________________|______|
#define BP_INCREMENT         '`'                  // 96         | USED |
#define BP_INCREMENT_HUMAN   "++"                 //            |      |
//______________________________________________________________|______|
//                            a                   // 97         |      |
//______________________________________________________________|______|
#define BP_CHAR              'b'                  // 98         | USED |
#define BP_CHAR_HUMAN        "char "              //            |      |
//______________________________________________________________|______|
#define BP_CONTINUE          'c'                  // 99         | USED |
#define BP_CONTINUE_HUMAN    "continue"           //            |      |
//______________________________________________________________|______|
                           // d                   // 100        |      |
//______________________________________________________________|______|
#define BP_INPUT             'e'                  // 101        | USED |
#define BP_INPUT_HUMAN       "input"              //            |      |
//______________________________________________________________|______|
#define BP_FUN_DEF           'f'                  // 102        | USED |
#define BP_FUN_DEF_HUMAN     "function "          //            |      |
//______________________________________________________________|______|
#define BP_SERIAL_TX         'g'                  // 103        | USED |
#define BP_SERIAL_TX_HUMAN   "serialWrite"        //            |      |
//______________________________________________________________|______|
                           // h                   // 104        |      |
//______________________________________________________________|______|
#define BP_NUMERIC           'i'                  // 105        | USED |
#define BP_NUMERIC_HUMAN     "numeric"            //            |      |
//______________________________________________________________|______|
#define BP_JUMP              'j'                  // 106        | USED |
#define BP_JUMP_HUMAN        "jump"               //            |      |
//______________________________________________________________|______|
                           // k                   // 107        |      |
//______________________________________________________________|______|
#define BP_LABEL             'l'                  // 108        | USED |
#define BP_LABEL_HUMAN       "label"              //            |      |
//______________________________________________________________|______|
#define BP_SIZEOF            'm'                  // 109        | USED |
#define BP_SIZEOF_HUMAN      "sizeof"             //            |      |
//______________________________________________________________|______|
#define BP_NEXT              'n'                  // 110        | USED |
#define BP_NEXT_HUMAN        "next"               //            |      |
//______________________________________________________________|______|
                           // o                   // 111        |      |
//______________________________________________________________|______|
#define BP_PRINT             'p'                  // 112        | USED |
#define BP_PRINT_HUMAN       "print"              //            |      |
//______________________________________________________________|______|
#define BP_ATOL              'q'                  // 113        | USED |
#define BP_ATOL_HUMAN        "number"             //            |      |
//______________________________________________________________|______|
#define BP_RETURN            'r'                  // 114        | USED |
#define BP_RETURN_HUMAN      "return"             //            |      |
//______________________________________________________________|______|
#define BP_SQRT              's'                  // 115        | USED |
#define BP_SQRT_HUMAN        "sqrt"               //            |      |
//______________________________________________________________|______|
                           // t                   // 116        |      |
//______________________________________________________________|______|
#define BP_SERIAL_RX         'u'                  // 117        | USED |
#define BP_SERIAL_RX_HUMAN   "serialRead"         //            |      |
//______________________________________________________________|______|
                          // 'v'                  // 118        |      |
//______________________________________________________________|______|
#define BP_WHILE             'w'                  // 119        | USED |
#define BP_WHILE_HUMAN       "while"              //            |      |
//______________________________________________________________|______|
#define BP_END               'x'                  // 120        | USED |
#define BP_END_HUMAN         "stop"               //            |      |
//______________________________________________________________|______|
                           // y                   // 121        |      |
//______________________________________________________________|______|
#define BP_RESTART           'z'                  // 122        | USED |
#define BP_RESTART_HUMAN     "restart"            //            |      |
//______________________________________________________________|______|
                           // {                   // 123        |      |
//______________________________________________________________|______|
#define BP_OR                '|'                  // 124        | USED |
//______________________________________________________________|______|
                           // }                   // 125        |      |
//______________________________________________________________|______|
#define BP_FUNCTION          '~'                  // 126        | USED |
// sum(2 + 2) -> ~0(2 + 2)                        //            |      |
//______________________________________________________________|______|
                                                  // 127        |      |
//______________________________________________________________|______|
#define BP_NUMBER           128                   // 128        | USED |
//______________________________________________________________|______|

// TODO
// system call to have easier access to user input from console/serial
// #define BP_AWRITE
// #define BP_SFLUSH
// #define BP_SBEGIN
// #define BP_ABS
// #define BP_MIN
// #define BP_MAX
// #define BP_MAP

/* DATA TYPES ------------------------------------------------------------- */

typedef void (*error_type)(char *position, const char *string);
