
/* BIPLAN CR.1 (Byte coded Interpreted Programming Language)

      _____              _________________________
     |   | |            |_________________________|
     |   | |_______________||__________   \___||_________ |
   __|___|_|               ||          |__|   ||     |   ||
  /________|_______________||_________________||__   |   |D
    (O)                 |_________________________|__|___/|
                                           \ /            |
                                           (O)

  Giovanni Blu Mitolo 2017-2021 - gioscarab@gmail.com
  BIP interpreter bounds and byte-code symbols */

#pragma once

#include "utils/errors/BIPLAN_Errors.h"

/* BIPLAN maximum program size --------------------------------------------- */

#ifndef BP_MAX_PROGRAM_SIZE
  #define BCC_MAX_PROGRAM_SIZE 2000
#endif

/* BIPLAN memory size ------------------------------------------------------ */

#ifndef BP_MEM_SIZE
  #define BP_MEM_SIZE 1024
#endif

/* Variable type, change if required (signed only) ------------------------- */

#ifndef BP_VAR_T
  #define BP_VAR_T long
#endif

#ifndef BP_VAR_MAX
  #define BP_VAR_MAX (BP_VAR_T)((unsigned BP_VAR_T) ~ 0 >> 1)
#endif

#include "interfaces/BIPLAN_Interfaces.h"

/* Keyword maximum length -------------------------------------------------- */

#ifndef BP_KEYWORD_MAX
  #define BP_KEYWORD_MAX 20
#endif

/* Files maximum amount ---------------------------------------------------- */

#ifndef BP_FILES_MAX
  #define BP_FILES_MAX 10
#endif

/* ASCII addresses offset (avoid the first 34 ASCII characters) ------------ */

#ifndef BP_OFFSET
  #define BP_OFFSET 35
#endif

/* Variables amount, set higher if required (max 88 - BP_PARAMS) ----------- */

#ifndef BP_VARIABLES
  #define BP_VARIABLES 50
#endif

/* Strings amount, set higher if required (max 88 - BP_ARGS) --------------- */

#ifndef BP_STRINGS
  #define BP_STRINGS 20
#endif

/* Preprocessor macros maximum length -------------------------------------- */

#ifndef BP_MACRO_MAX
  #define BP_MACRO_MAX 255
#endif

/* Program arguments amount, set higher if required (max 88 - BP_STRINGS) */
/* handle args: https://www.thegeekstuff.com/2013/01/c-argc-argv/ */
#ifndef BP_ARGS
  #define BP_ARGS 5
#endif

/* Functions amount, set higher if required (max 88) ----------------------- */

#ifndef BP_FUN_MAX
  #define BP_FUN_MAX 20
#endif

/* Function parameters amount, set higher if required ---------------------- */

#ifndef BP_PARAMS
  #define BP_PARAMS 10
#endif

/* Function call maximum depth, set higher if required --------------------- */

#ifndef BP_FUN_DEPTH
  #define BP_FUN_DEPTH 20
#endif

/* Maximum length of a number (represented as a string) -------------------- */

#ifndef BP_NUM_MAX
  #define BP_NUM_MAX 20 // Handle 64 bits machine limit
#endif

/* String maximum length, set higher if required --------------------------- */

#ifndef BP_STRING_MAX
  #define BP_STRING_MAX 60
#endif

/* Cycle (for, while) maximum depth, higher if required -------------------- */

#ifndef BP_CYCLE_DEPTH
  #define BP_CYCLE_DEPTH 20
#endif

/* Pre-processor macro symbol ---------------------------------------------- */

#ifndef BP_MACRO_DEF
  #define BP_MACRO_DEF "macro"
#endif


/* BIP and BIPLAN language syntax ---------------------------------------------
_______________________________________________________________________
 Constant name                                    | Decimal     | used |
__________________________________________________|_____________|______| */
#define BP_ERROR              0                   //  0         | used |
#define BP_ENDOFINPUT         1                   //  1         | used |
                                                  //  2         |      |
                                                  //  3         |      |
                                                  //  4         |      |
                                                  //  5         |      |
                                                  //  6         |      |
                                                  //  7         |      |
                                                  //  8         |      |
#define BP_TAB                9                   //  9         |      |
#define BP_LF               '\n'                  // 10         |      |
                                                  // 11         |      |
                                                  // 12         |      |
#define BP_CR               '\r'                  // 13         |      |
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
#define BP_SPACE             ' '                  // 32         | used |
// Used by BIPLAN as separator                    //            |      |
//______________________________________________________________|______|
#define BP_ELSE              '!'                  // 33         | used |
#define BP_ELSE_HUMAN        "else"               //            |      |
//______________________________________________________________|______|
#define BP_STRING            '"'                  // 34         | used |
//______________________________________________________________|______|
#define BP_REM               '#'                  // 35         | used |
//______________________________________________________________|______|
#define BP_VAR_ADDR_HUMAN    '$'                  // 36         | used |
// Used by BIPLAN as variable identifier                        |      |
//______________________________________________________________|______|
#define BP_MOD               '%'                  // 37         | used |
//______________________________________________________________|______|
#define BP_AND               '&'                  // 38         | used |
//______________________________________________________________|______|
#define BP_SINGLE_QUOTE      '\''                 // 39         |      |
//______________________________________________________________|______|
#define BP_L_RPARENT         '('                  // 40         | used |
//______________________________________________________________|______|
#define BP_R_RPARENT         ')'                  // 41         | used |
//______________________________________________________________|______|
#define BP_MULT              '*'                  // 42         | used |
//______________________________________________________________|______|
#define BP_PLUS              '+'                  // 43         | used |
//______________________________________________________________|______|
#define BP_COMMA             ','                  // 44         | used |
//______________________________________________________________|______|
#define BP_MINUS             '-'                  // 45         | used |
//______________________________________________________________|______|
                           // .                   // 46         |      |
//______________________________________________________________|______|
#define BP_DIV               '/'                  // 47         | used |
//______________________________________________________________|______|
// NUMBERS                    0                   // 48         | used |
// NUMBERS                    1                   // 49         | used |
// NUMBERS                    2                   // 50         | used |
// NUMBERS                    3                   // 51         | used |
// NUMBERS                    4                   // 52         | used |
// NUMBERS                    5                   // 53         | used |
// NUMBERS                    6                   // 54         | used |
// NUMBERS                    7                   // 55         | used |
// NUMBERS                    8                   // 56         | used |
// NUMBERS                    9                   // 57         | used |
//______________________________________________________________|______|
#define BP_STR_ADDR          ':'                  // 58         | used |
// used in BIPLAN and BIP as string identifier                  |      |
//______________________________________________________________|______|
#define BP_SEMICOLON         ';'                  // 59         | used |
//______________________________________________________________|______|
#define BP_LT                '<'                  // 60         | used |
//______________________________________________________________|______|
#define BP_ASSIGN_HUMAN      '='                  // 61         | used |
// Used in BIPLAN for assignment (syntactic sugar)              |      |
//______________________________________________________________|______|
#define BP_GT                '>'                  // 62         | used |
//______________________________________________________________|______|
#define BP_IF                '?'                  // 63         | used |
#define BP_IF_HUMAN          "if"                 //            |      |
//______________________________________________________________|______|
#define BP_FOR               '@'                  // 64         | used |
#define BP_GLOBAL_HUMAN      '@'                  //            |      |
#define BP_FOR_HUMAN         "for"                //            |      |
//______________________________________________________________|______|
#define BP_LOGIC_AND         'A'                  // 65         | used |
#define BP_LOGIC_AND_HUMAN   "&&"                 //            |      |
//______________________________________________________________|______|
#define BP_BREAK             'B'                  // 66         | used |
#define BP_BREAK_HUMAN       "break"              //            |      |
//______________________________________________________________|______|
#define BP_DECREMENT         'C'                  // 67         | used |
#define BP_DECREMENT_HUMAN   "--"                 //            |      |
//______________________________________________________________|______|
#define BP_DELAY             'D'                  // 68         | used |
#define BP_DELAY_HUMAN       "delay"              //            |      |
//______________________________________________________________|______|
#define BP_IO                'E'                  // 69         | used |
#define BP_IO_HUMAN          "io"                 //            |      |
//______________________________________________________________|______|
#define BP_ENDIF             'F'                  // 70         | used |
#define BP_ENDIF_HUMAN       "end"                //            |      |
//______________________________________________________________|______|
                           // G                   // 71         |      |
//______________________________________________________________|______|
#define BP_GTOEQ             'H'                  // 72         | used |
#define BP_GTOEQ_HUMAN       ">="                 //            |      |
//______________________________________________________________|______|
#define BP_LTOEQ             'I'                  // 73         | used |
#define BP_LTOEQ_HUMAN       "<="                 //            |      |
//______________________________________________________________|______|
#define BP_ADC               'J'                  // 74         | used |
#define BP_ADC_HUMAN         "adc"                //            |      |
//______________________________________________________________|______|
#define BP_R_SHIFT           'K'                  // 75         | used |
#define BP_R_SHIFT_HUMAN     ">>"                 //            |      |
//______________________________________________________________|______|
#define BP_L_SHIFT           'L'                  // 76         | used |
#define BP_L_SHIFT_HUMAN     "<<"                 //            |      |
//______________________________________________________________|______|
#define BP_MILLIS            'M'                  // 77         | used |
#define BP_MILLIS_HUMAN      "millis"             //            |      |
//______________________________________________________________|______|
#define BP_BITWISE_NOT       'N'                  // 78         | used |
#define BP_BITWISE_NOT_HUMAN "~"                  //            |      |
//______________________________________________________________|______|
#define BP_LOGIC_OR          'O'                  // 79         | used |
#define BP_LOGIC_OR_HUMAN    "||"                 //            |      |
//______________________________________________________________|______|
                           // P                   // 80         |      |
//______________________________________________________________|______|
#define BP_EQ                'Q'                  // 81         | used |
#define BP_EQ_HUMAN          "=="                 //            |      |
//______________________________________________________________|______|
#define BP_RND               'R'                  // 82         | used |
#define BP_RND_HUMAN         "random"             //            |      |
//______________________________________________________________|______|
#define BP_STR_ACC           'S'                  // 83         | used |
#define BP_STR_ACC_HUMAN     ":["                 //            |      |
//______________________________________________________________|______|
#define BP_NOT_EQ            'T'                  // 84         | used |
#define BP_NOT_EQ_HUMAN      "!="                 //            |      |
//______________________________________________________________|______|
#define BP_MEM_ACC           'U'                  // 85         | used |
#define BP_MEM_ACC_HUMAN     "mem["               //            |      |
//______________________________________________________________|______|
#define BP_VAR_ACC           'V'                  // 86         | used |
#define BP_VAR_ACC_HUMAN     "@["                 //            |      |
//______________________________________________________________|______|
#define BP_WRITE             'W'                  // 87         | used |
#define BP_WRITE_HUMAN       "write"              //            |      |
//______________________________________________________________|______|
#define BP_READ              'X'                  // 88         | used |
#define BP_READ_HUMAN        "read"               //            |      |
//______________________________________________________________|______|
#define BP_OPEN              'Y'                  // 89         | used |
#define BP_OPEN_HUMAN        "open"               //            |      |
//______________________________________________________________|______|
#define BP_CLOSE             'Z'                  // 90         | used |
#define BP_CLOSE_HUMAN       "close"              //            |      |
//______________________________________________________________|______|
#define BP_ACCESS            '['                  // 91         | used |
//______________________________________________________________|______|
#define BP_BACKSLASH         '\\'                 // 92         | used |
//______________________________________________________________|______|
#define BP_ACCESS_END        ']'                  // 93         | used |
//______________________________________________________________|______|
#define BP_XOR               '^'                  // 94         | used |
//______________________________________________________________|______|
//                            _                   // 97         |      |
//______________________________________________________________|______|
#define BP_INCREMENT         '`'                  // 96         | used |
#define BP_INCREMENT_HUMAN   "++"                 //            |      |
//______________________________________________________________|______|
#define BP_INDEX             'a'                  // 97         | used |
#define BP_INDEX_HUMAN       "index"              //            |      |
//______________________________________________________________|______|
#define BP_CHAR              'b'                  // 98         | used |
#define BP_CHAR_HUMAN        "char "              //            |      |
//______________________________________________________________|______|
#define BP_CONTINUE          'c'                  // 99         | used |
#define BP_CONTINUE_HUMAN    "continue"           //            |      |
//______________________________________________________________|______|
                           // d                   // 100        |      |
//______________________________________________________________|______|
#define BP_INPUT             'e'                  // 101        | used |
#define BP_INPUT_HUMAN       "input"              //            |      |
//______________________________________________________________|______|
#define BP_FUN_DEF           'f'                  // 102        | used |
#define BP_FUN_DEF_HUMAN     "function "          //            |      |
//______________________________________________________________|______|
#define BP_SERIAL            'g'                  // 103        | used |
#define BP_SERIAL_HUMAN      "serial"             //            |      |
//______________________________________________________________|______|
#define BP_LTOA              'h'                  // 104        | used |
#define BP_LTOA_HUMAN        "string"             //            |      |
//______________________________________________________________|______|
#define BP_NUMERIC           'i'                  // 105        | used |
#define BP_NUMERIC_HUMAN     "numeric"            //            |      |
//______________________________________________________________|______|
#define BP_JUMP              'j'                  // 106        | used |
#define BP_JUMP_HUMAN        "jump"               //            |      |
//______________________________________________________________|______|
#define BP_SYSTEM            'k'                  // 107        | used |
#define BP_SYSTEM_HUMAN      "system"             //            |      |
//______________________________________________________________|______|
#define BP_LABEL             'l'                  // 108        | used |
#define BP_LABEL_HUMAN       "label"              //            |      |
//______________________________________________________________|______|
#define BP_SIZEOF            'm'                  // 109        | used |
#define BP_SIZEOF_HUMAN      "size"               //            |      |
//______________________________________________________________|______|
#define BP_NEXT              'n'                  // 110        | used |
#define BP_NEXT_HUMAN        "next"               //            |      |
//______________________________________________________________|______|
#define BP_FILE              'o'                  // 111        | used |
#define BP_FILE_HUMAN        "file"               //            |      |
//______________________________________________________________|______|
#define BP_PRINT             'p'                  // 112        | used |
#define BP_PRINT_HUMAN       "print"              //            |      |
//______________________________________________________________|______|
#define BP_ATOL              'q'                  // 113        | used |
#define BP_ATOL_HUMAN        "number"             //            |      |
//______________________________________________________________|______|
#define BP_RETURN            'r'                  // 114        | used |
#define BP_RETURN_HUMAN      "return"             //            |      |
//______________________________________________________________|______|
#define BP_SQRT              's'                  // 115        | used |
#define BP_SQRT_HUMAN        "sqrt"               //            |      |
//______________________________________________________________|______|
#define BP_RESULT            't'                  // 116        |      |
#define BP_RESULT_HUMAN      "result"             //            |      |
//______________________________________________________________|______|
                          // 'u'                  // 117        |      |
//______________________________________________________________|______|
                          // 'v'                  // 118        |      |
//______________________________________________________________|______|
#define BP_WHILE             'w'                  // 119        | used |
#define BP_WHILE_HUMAN       "while"              //            |      |
//______________________________________________________________|______|
#define BP_END               'x'                  // 120        | used |
#define BP_END_HUMAN         "stop"               //            |      |
//______________________________________________________________|______|
#define BP_CURSOR            'y'                  // 121        | used |
#define BP_CURSOR_HUMAN      "cursor"             //            |      |
//______________________________________________________________|______|
#define BP_RESTART           'z'                  // 122        | used |
#define BP_RESTART_HUMAN     "restart"            //            |      |
//______________________________________________________________|______|
#define BP_VAR_ADDR          '{'                  // 123        |      |
//______________________________________________________________|______|
#define BP_OR                '|'                  // 124        | used |
//______________________________________________________________|______|
                           // }                   // 125        |      |
//______________________________________________________________|______|
#define BP_FUNCTION          '~'                  // 126        | used |
// sum(2 + 2) -> ~#2+2)                           //            |      |
//______________________________________________________________|______|
                                                  // 127        |      |
//______________________________________________________________|______|
#define BP_NUMBER           128                   // 128        | used |
//______________________________________________________________|______|


// TODO - Condense codes serial, write, read, open, close

// #define BP_CLRSCR
// #define BP_GOTOXY
// #define BP_AWRITE
// #define BP_SFLUSH
// #define BP_SBEGIN
// #define BP_ABS
// #define BP_MIN
// #define BP_MAX
// #define BP_MAP

/* Data types -------------------------------------------------------------- */

typedef void (*bip_error_t)(char *position, const char *string);

struct bip_param_t {
  BP_VAR_T value;
  uint8_t id = BP_VARIABLES;
};

struct bip_fun_t {
  char *address;
  uint8_t cid;
  bip_param_t params[BP_PARAMS];
  BP_VAR_T result;
};

struct bip_def_t {
  char *address;
  uint16_t params[BP_PARAMS];
};

struct bip_cycle_t {
  char *address;
  BP_VAR_T var = 0;
  uint8_t var_id = BP_VARIABLES;
  BP_VAR_T step = 0;
  BP_VAR_T to = 0;
};

struct bip_files_t {
  BPM_FILE_T *file;
  bool free = true;
};
