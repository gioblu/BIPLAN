
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
#include "BIPLAN_Defines.h"
#include "BCC.h"

class BCC {
public:
  char var_id = BP_OFFSET;
  char string_id = BP_OFFSET;
  char fun_id = BP_OFFSET;
  error_type error_callback = NULL;
  bool fail = false;

  BCC() { };

  /* ERROR ----------------------------------------------------------------- */
  void error(char *position, const char *string) {
    error_callback(position, string);
  };

  /* ACCEPTABLE KEYWORD CHARACTER ------------------------------------------ */

  bool keyword_char(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_');
  };

  /* CHECK DELIMETERS ------------------------------------------------------ */
  bool check_delimeter(char *program, char a, char b) {
    uint16_t ia = 0;
    uint16_t ib = 0;
    char *p = program;
    while(*p != 0) {
      if((*p == a) && !is_in_string(program, p)) ia++;
      if((*p == b) && !is_in_string(program, p)) ib++;
      p++;
    } return (ia == ib);
  };

  /* CHECK IF POINTER IS IN A STRING -------------------------------------- */
  bool is_in_string(char *program, char *a) {
    bool in_str = false;
    char *p = program;
    while(a > p) {
      if(*p == BP_STRING) in_str = !in_str;
      p++;
    } return in_str;
  };

  /* REMOVE SPACES FROM PROGRAM ------------------------------------------- */
  void remove_spaces(char *s) {
    if(fail) return; // Abort if an error occurred
    char *i = s;
    char *j = s;
    bool in_str = false;
    while(*j != 0) {
      *i = *j++;
      if(*i == BP_STRING) in_str = !in_str;
      if(*i != BP_SPACE) i++;
      else if(in_str) i++;
    } *i = 0;
  };

  /* REMOVE CARRIAGE RETURN FROM PROGRAM ---------------------------------- */
  void remove_cr(char *s) {
    if(fail) return; // Abort if an error occurred
    char *i = s;
    char *j = s;
    bool in_str = false;
    while(*j != 0) {
      *i = *j++;
      if(*i == BP_STRING) in_str = !in_str;
      if(*i != '\n') i++;
      else if(in_str) i++;
    } *i = 0;
  };

  /* REMOVE COMMENTS FROM PROGRAM ----------------------------------------- */
  void remove_comments(char *s) {
    if(fail) return; // Abort if an error occurred
    char *i = s;
    char *j = s;
    bool in_str = false;
    while(*j != 0) {
      *i = *j++;
      if(*i == BP_STRING) in_str = !in_str;
      if(*i != BP_REM) i++;
      else {
        if(in_str) i++;
        else {
          while(*j != BP_CR) (void)(*j++);
          //(void)(*j++);
        }
      }
    } *i = 0;
  };

  /* ENCODE PROGRAM KEYWORD IN BYTECODE ----------------------------------- */
  char *encode_pass(
    char *program,
    char *position,
    const char *keyword,
    const char *code
  ) {
    char *p;
    uint8_t kl = strlen(keyword);
    uint8_t cl = strlen(code);
    p = strstr(position, keyword);
    if(p && *p) {
      if(is_in_string(program, p)) {
        p = strstr(p + kl, keyword);
        if(p && *p) return p;
        else return NULL;
      }
      for(uint16_t i = 0; i < kl; i++, p++)
        if(i < cl && code[i]) *p = code[i];
        else *p = BP_SPACE;
      return p;
    } else return NULL;
  };

  void encode(char *program, const char *keyword, const char *code) {
    if(fail) return; // Abort if an error occurred
    char *position = program;
    while(position) position =
      encode_pass(program, position, keyword, code);
  };

  void encode_char(char *program, const char *keyword, const char code) {
    if(fail) return; // Abort if an error occurred
    char *position = program;
    const char c[2] = {code, 0};
    while(position) position =
      encode_pass(program, position, keyword, (const char *)c);
  };

  /* ENCODE PROGRAM VARIABLE IN BYTECODE ---------------------------------- */
  char *minifier_variable_pass(char *program, char *position, bool var_type) {
    char *p;
    char str[BP_MAX_KEYWORD_LENGTH];
    char code[4] = {(var_type) ? BP_ADDRESS : BP_S_ADDRESS, 0, 0, 0};
    uint8_t n;
    if((p = find_longest_var_name(program, var_type)) != NULL) {
      str[0] = (var_type) ? BP_ADDRESS : BP_S_ADDRESS;
      p++;
      str[1] = *p;
      *p = (var_type) ? var_id : string_id;
      p++;
      n = 2;
      for(uint16_t i = 0; i < BP_MAX_KEYWORD_LENGTH - 1; i++, p++) {
        if(keyword_char(*p)) {
          // Add space instead of keyword (will be removed by remove_spaces)
          str[n++] = *p;
          *p = BP_SPACE;
          // Check maximum variable name length
          if((i == (BP_MAX_KEYWORD_LENGTH - 2)) && keyword_char(*(p + 1))) {
            error(0, BP_ERROR_VARIABLE_NAME);
            fail = true;
            return NULL;
          }
        } else break;
      }
      if(n) {
        // Encode variable address followed by space " "
        str[n] = 0;
        code[1] = (var_type) ? var_id : string_id;
        code[2] = 0;
        encode(position, str, code);
        p = strstr(position, str);
        if((p && *p) && !is_in_string(program, p)) return p;
        if(var_type) var_id++; else string_id++;
        return (char *)position;
      } return p;
    } return NULL;
  };

  void encode_variables(char *program, bool type) {
    if(fail) return; // Abort if an error occurred
    char *position = program;
    while(position) position =
      minifier_variable_pass(program, position, type);
  };

  char *find_longest_var_name(char *program, bool type) {
    char   *position = program;
    uint8_t result = 0;
    char   *result_position = 0;
    while(*position != 0) {
      if(*(position++) == ((type) ? BP_ADDRESS : BP_S_ADDRESS)) {
        // Avoid substitution in strings
        if(is_in_string(program, position)) continue;
        uint8_t i = 0;
        while(keyword_char(*position)) {
          i++;
          position++;
        }
        if(i > result) {
          result_position = position - (i + 1);
          result = i;
        }
      }
    }
    if(result)
      return (char *)result_position;
    else return NULL;
  };

  /* ENCODE FUNCTION IN BYTECODE ------------------------------------------ */
  char *encode_function_pass(char *program, char *position) {
    char function_keyword[BP_MAX_KEYWORD_LENGTH];
    char function_address[3];
    char *p = strstr(position, BP_FUN_DEF_HUMAN);
    uint8_t keyword_length = 0;
    if(p && *p) {
      if(is_in_string(program, p)) {
        p = strstr(p + 1, BP_FUN_DEF_HUMAN);
        if(p && *p) return p;
        else return NULL;
      }
      *p = BP_FUN_DEF;
      p++;
      *p = fun_id;
      p++;
      while(*p != BP_SPACE) {
        *p = BP_SPACE;
        p++;
      }
      while(p++ && (*p != BP_L_RPARENT)) {
        function_keyword[keyword_length] = *p;
        *p = BP_SPACE;
        keyword_length++;
      }
      if(keyword_length) {
        // Check keyword length
        if(keyword_length >= BP_MAX_KEYWORD_LENGTH) {
          error(0, BP_ERROR_FUNCTION_NAME);
          fail = true;
          return NULL;
        }
        // Encode address
        function_keyword[keyword_length] = 0;
        function_address[0] = BP_FUNCTION;
        function_address[1] = fun_id++;
        function_address[2] = 0;
        encode(program, function_keyword, function_address);
        p = strstr(position, function_keyword);
        if(p && *p) return p;
        else return NULL;
      } return p;
    } else return NULL;
  };

  void encode_functions(char *program) {
    if(fail) return; // Abort if an error occurred
    char *position = program;
    while(position) position = encode_function_pass(program, position);
  };

  /* RUN COMPILATION ------------------------------------------------------ */
  void run(char *program) {
    // Initial program consistency checks
    if(!check_delimeter(program, BP_L_RPARENT, BP_R_RPARENT)) {
      error(0, BP_ERROR_ROUND_PARENTHESIS);
      return;
    }
    // Remove comments
    remove_comments(program);
    // String reference access
    encode_char(program, BP_STR_ACCESS_HUMAN, BP_STR_ACCESS);
    // Variable reference access
    encode_char(program, BP_VAR_ACCESS_HUMAN, BP_VAR_ACCESS);
    // Encode variables
    encode_variables(program, false);
    encode_variables(program, true);
    // Logic
    encode_char(program, BP_EQ_HUMAN, BP_EQ);
    encode_char(program, BP_NOT_EQ_HUMAN, BP_NOT_EQ);
    encode_char(program, BP_GTOEQ_HUMAN, BP_GTOEQ);
    encode_char(program, BP_LTOEQ_HUMAN, BP_LTOEQ);
    encode_char(program, BP_LOGIC_OR_HUMAN, BP_LOGIC_OR);
    encode_char(program, BP_LOGIC_AND_HUMAN, BP_LOGIC_AND);
    // Bitwise
    encode_char(program, BP_R_SHIFT_HUMAN, BP_R_SHIFT);
    encode_char(program, BP_L_SHIFT_HUMAN, BP_L_SHIFT);
    // Remove syntactic sugar
    encode(program, "=", "");
    // Unary
    encode_char(program, BP_INCREMENT_HUMAN, BP_INCREMENT);
    encode_char(program, BP_DECREMENT_HUMAN, BP_DECREMENT);
    // Bitwise not
    encode_char(program, BP_BITWISE_NOT_HUMAN, BP_BITWISE_NOT);
    // Minify functions
    for(uint8_t i = 0; i < BP_MAX_FUNCTIONS; i++)
      encode_functions(program);
    // System calls
    encode_char(program, BP_AGET_HUMAN, BP_AGET);
    encode_char(program, BP_DWRITE_HUMAN, BP_DWRITE);
    encode_char(program, BP_DREAD_HUMAN, BP_DREAD);
    encode_char(program, BP_PINMODE_HUMAN, BP_PINMODE);
    encode_char(program, BP_RND_HUMAN, BP_RND);
    encode_char(program, BP_MILLIS_HUMAN, BP_MILLIS);
    encode_char(program, BP_DELAY_HUMAN, BP_DELAY);
    encode_char(program, BP_SQRT_HUMAN, BP_SQRT);
    // Constants
    encode(program, "OUTPUT", "1");
    encode(program, "INPUT", "0");
    encode(program, "HIGH", "1");
    encode(program, "LOW", "0");
    encode(program, "false", "0");
    encode(program, "true", "1");
    // Language syntax
    encode_char(program, BP_SERIAL_AV_HUMAN, BP_SERIAL_AV);
    encode_char(program, BP_SERIAL_RX_HUMAN, BP_SERIAL_RX);
    encode_char(program, BP_SERIAL_TX_HUMAN, BP_SERIAL_TX);
    encode_char(program, BP_INPUT_AV_HUMAN, BP_INPUT_AV);
    encode_char(program, BP_CONTINUE_HUMAN, BP_CONTINUE);
    encode_char(program, BP_RESTART_HUMAN, BP_RESTART);
    encode_char(program, BP_RETURN_HUMAN, BP_RETURN);
    encode_char(program, BP_STOI_HUMAN, BP_STOI);
    encode_char(program, BP_INPUT_HUMAN, BP_INPUT);
    encode_char(program, BP_BREAK_HUMAN, BP_BREAK);
    encode_char(program, BP_PRINT_HUMAN, BP_PRINT);
    encode_char(program, BP_WHILE_HUMAN, BP_WHILE);
    encode_char(program, BP_ENDIF_HUMAN, BP_ENDIF);
    encode_char(program, BP_SIZEOF_HUMAN, BP_SIZEOF);
    encode_char(program, BP_NEXT_HUMAN, BP_NEXT);
    encode_char(program, BP_CHAR_HUMAN, BP_CHAR);
    encode_char(program, BP_ELSE_HUMAN, BP_ELSE);
    encode_char(program, BP_END_HUMAN, BP_END);
    encode_char(program, BP_FOR_HUMAN, BP_FOR);
    encode_char(program, BP_IF_HUMAN, BP_IF);
    encode_char(program, "to", BP_COMMA);
    encode_char(program, "step", BP_COMMA);
    encode(program, "not", "1-");
    // Remove spaces
    remove_spaces(program);
    remove_cr(program);
    // End compilation program consistency checks
    if(!check_delimeter(program, BP_IF, BP_ENDIF))
      error(0, BP_ERROR_BLOCK);
    // Check variables, strings and functions buffer bounds
    if((fun_id - BP_OFFSET) >= BP_MAX_FUNCTIONS)
      error(0, BP_ERROR_FUNCTION_MAX);
    if((string_id - BP_OFFSET) >= BP_STRINGS)
      error(0, BP_ERROR_STRING_MAX);
    if((var_id - BP_OFFSET) >= BP_VARIABLES)
      error(0, BP_ERROR_VARIABLE_MAX);
    // Reset indexes
    var_id = BP_OFFSET;
    string_id = BP_OFFSET;
    fun_id = BP_OFFSET;
  };
};
