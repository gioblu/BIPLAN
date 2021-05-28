
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
  BIPLAN Copyright (c) 2017-2021, Giovanni Blu Mitolo All rights reserved.
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

/* ACCEPTABLE KEYWORD CHARACTER ------------------------------------------ */
#define BCC_KEYWORD_CHAR(C) \
  (C >= 'a' && C <= 'z') || (C >= 'A' && C <= 'Z') || (C == '_')

class BCC {
public:
  char var_id = BP_OFFSET;
  char string_id = BP_OFFSET;
  char fun_id = BP_OFFSET;
  bip_error_t error_callback = NULL;
  bool fail = false;

  BCC() { };

  /* ERROR ----------------------------------------------------------------- */
  void error(char *position, const char *string) {
    error_callback(position, string);
    fail = true;
  };

  /* CHECK DELIMETER ------------------------------------------------------- */
  bool check_delimeter(char *program, char a, char b, char c = 0) {
    uint16_t ia = 0, ib = 0;
    char *p = program;
    while(*p != 0) {
      if(!is_in_string(program, p)) {
        if(*p == a) ia++;
        if((*p == b) || (*p == c)) ib++;
      } p++;
    } return (ia == ib);
  };

  bool check_delimeter(char *program, char a) {
    uint16_t i = 0;
    char *p = program;
    while(*p != 0) {
      if(!is_in_string(program, p)) if(*p == a) i++;
      p++;
    } return ((i % 2) == 0);
  };

  /* CHECK IF POINTER IS IN A STRING -------------------------------------- */
  bool is_in_string(char *program, char *a) {
    bool in_str = false;
    char *p = program;
    while(a >= p) {
      /* if the last character to be checked is a string and it is not within
         a string, the function returns false */
      if((a == p) && (*p == BP_STRING) && !in_str) return in_str;
      if(*p == BP_STRING) in_str = !in_str;
      p++;
    } return in_str;
  };

  /* REMOVE CHARACTER FROM PROGRAM ---------------------------------------- */
  void remove(char *s, char v) {
    if(fail) return;
    char *i = s;
    char *j = s;
    bool in_str = false;
    while(*j != 0) {
      *i = *j++;
      if(*i == BP_STRING) in_str = !in_str;
      if(*i != v) i++;
      else if(in_str) i++;
    } *i = 0;
  };

  /* REMOVE COMMENTS FROM PROGRAM ----------------------------------------- */
  void remove_comments(char *program) {
    if(fail) return;
    char *i = program;
    char *j = program;
    bool in_str = false;
    while(*j != 0) {
      *i = *j++;
      if(*i == BP_STRING) in_str = !in_str;
      if(*i != BP_REM) i++;
      else {
        if(in_str) i++;
        else while((*j != BP_CR) && (*j != BP_LF)) (void)(*j++);
      }
    } *i = 0;
  };

  /* COMPILE PROGRAM KEYWORD IN BIP MACHINE LANGUAGE ---------------------- */
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
    if(fail) return;
    char *position = program;
    while(position) position =
      encode_pass(program, position, keyword, code);
  };

  void encode_char(char *program, const char *keyword, const char code) {
    if(fail) return;
    char *position = program;
    const char c[2] = {code, 0};
    while(position) position =
      encode_pass(program, position, keyword, (const char *)c);
  };

  /* COMPILE PROGRAM VARIABLE IN BIP MACHINE LANGUAGE --------------------- */
  char *minifier_variable_pass(char *program, char *position, char var_type) {
    char *p;
    char str[BP_KEYWORD_MAX];
    char code[4] = {var_type, 0, 0, 0};
    uint8_t n;
    if((p = find_longest_var_name(program, var_type)) != NULL) {
      str[0] = var_type;
      p++;
      str[1] = *p;
      *p = (var_type == BP_VAR_ADDR) ? var_id : string_id;
      p++;
      n = 2;
      for(uint16_t i = 0; i < BP_KEYWORD_MAX - 1; i++, p++) {
        if(BCC_KEYWORD_CHAR(*p)) {
          // Add space instead of keyword (will be removed by remove_spaces)
          str[n++] = *p;
          *p = BP_SPACE;
          // Check maximum variable name length
          if((i == (BP_KEYWORD_MAX - 2)) && (BCC_KEYWORD_CHAR(*(p + 1)))) {
            error(0, BP_ERROR_VARIABLE_NAME);
            fail = true;
            return NULL;
          }
        } else break;
      }
      if(n) {
        // Encode variable address followed by space " "
        str[n] = 0;
        code[1] = (var_type == BP_VAR_ADDR) ? var_id : string_id;
        code[2] = 0;
        encode(position, str, code);
        p = strstr(position, str);
        if((p && *p) && !is_in_string(program, p)) return p;
        if(var_type == BP_VAR_ADDR) var_id++; else string_id++;
        return (char *)position;
      } return p;
    } return NULL;
  };

  void encode_variables(char *program, char var_type) {
    if(fail) return;
    char *position = program;
    while(position) position =
      minifier_variable_pass(program, position, var_type);
  };

  char *find_longest_var_name(char *program, char var_type) {
    char   *position = program;
    uint8_t result = 0;
    char   *result_position = 0;
    while(*position != 0) {
      if(*(position++) == var_type) {
        // Avoid substitution in strings
        if(is_in_string(program, position)) continue;
        uint8_t i = 0;
        while(BCC_KEYWORD_CHAR(*position)) {
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

  /* COMPILE FUNCTION IN BIP MACHINE LANGUAGE ----------------------------- */
  char *encode_function_pass(char *program, char *position) {
    char function_keyword[BP_KEYWORD_MAX];
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
        if(keyword_length >= BP_KEYWORD_MAX) {
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
    if(fail) return;
    char *position = program;
    while(position) position = encode_function_pass(program, position);
  };

  /* PRE-COMPILATION CHECKS ----------------------------------------------- */
  bool pre_compilation_checks(char *program) {
    if(!check_delimeter(program, BP_L_RPARENT, BP_R_RPARENT))
      error(0, BP_ERROR_ROUND_PARENTHESIS);  // Check () parentheses
    if(!check_delimeter(program, BP_ACCESS, BP_ACCESS_END))
      error(0, BP_ERROR_SQUARE_PARENTHESIS); // Check [] parentheses
    if(!check_delimeter(program, BP_STRING))
      error(0, BP_ERROR_STRING_END);         // Check "" string separator
    return !fail;
  };

  /* POST-COMPILATION CHECKS ----------------------------------------------- */
  void post_compilation_checks(char *program) {
    if(!check_delimeter(program, BP_NEXT, BP_FOR, BP_WHILE))
      error(0, BP_ERROR_NEXT);  // Check for/while-next
    if(!check_delimeter(program, BP_IF, BP_ENDIF))
      error(0, BP_ERROR_BLOCK); // Check if-end
    // Check variables, strings and functions buffer bounds
    if((fun_id - BP_OFFSET) >= BP_FUN_MAX)
      error(0, BP_ERROR_FUNCTION_MAX);
    if((string_id - BP_OFFSET) >= BP_STRINGS)
      error(0, BP_ERROR_STRING_MAX);
    if((var_id - BP_OFFSET) >= BP_VARIABLES)
      error(0, BP_ERROR_VARIABLE_MAX);
  };

  /* RUN COMPILATION ------------------------------------------------------ */
  bool run(char *program) {
    // Remove comments
    remove_comments(program);
    // Pre-compilation error check
    if(!pre_compilation_checks(program)) return false;
    // String reference access
    encode_char(program, BP_STR_ACC_HUMAN, BP_STR_ACC);
    // Variable reference access
    encode_char(program, BP_VAR_ACC_HUMAN, BP_VAR_ACC);
    // Memory reference access
    encode_char(program, BP_MEM_ACC_HUMAN, BP_MEM_ACC);
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
    encode_char(program, "=", ' ');
    // Unary
    encode_char(program, BP_INCREMENT_HUMAN, BP_INCREMENT);
    encode_char(program, BP_DECREMENT_HUMAN, BP_DECREMENT);
    // Bitwise not
    encode_char(program, BP_BITWISE_NOT_HUMAN, BP_BITWISE_NOT);
    // Encode variables
    encode_variables(program, BP_VAR_ADDR);
    encode_variables(program, BP_STR_ADDR);
    // Minify functions
    for(uint8_t i = 0; i < BP_FUN_MAX; i++)
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
    // Language syntax
    encode_char(program, BP_SERIAL_RX_HUMAN, BP_SERIAL_RX);
    encode_char(program, BP_SERIAL_TX_HUMAN, BP_SERIAL_TX);
    encode_char(program, BP_FILE_OPEN_HUMAN, BP_FILE_OPEN);
    encode_char(program, BP_FILE_READ_HUMAN, BP_FILE_READ);
    encode_char(program, BP_FILE_WRITE_HUMAN, BP_FILE_WRITE);
    encode_char(program, BP_CONTINUE_HUMAN, BP_CONTINUE);
    encode_char(program, BP_RESTART_HUMAN, BP_RESTART);
    encode_char(program, BP_NUMERIC_HUMAN, BP_NUMERIC);
    encode_char(program, BP_RETURN_HUMAN, BP_RETURN);
    encode_char(program, BP_ATOL_HUMAN, BP_ATOL);
    encode_char(program, BP_INPUT_HUMAN, BP_INPUT);
    encode_char(program, BP_BREAK_HUMAN, BP_BREAK);
    encode_char(program, BP_PRINT_HUMAN, BP_PRINT);
    encode_char(program, BP_WHILE_HUMAN, BP_WHILE);
    encode_char(program, BP_ENDIF_HUMAN, BP_ENDIF);
    encode_char(program, BP_SIZEOF_HUMAN, BP_SIZEOF);
    encode_char(program, BP_INDEX_HUMAN, BP_INDEX);
    encode_char(program, BP_NEXT_HUMAN, BP_NEXT);
    encode_char(program, BP_CHAR_HUMAN, BP_CHAR);
    encode_char(program, BP_ELSE_HUMAN, BP_ELSE);
    encode_char(program, BP_JUMP_HUMAN, BP_JUMP);
    encode_char(program, BP_LABEL_HUMAN, BP_LABEL);
    encode_char(program, BP_END_HUMAN, BP_END);
    encode_char(program, BP_FOR_HUMAN, BP_FOR);
    encode_char(program, BP_IF_HUMAN, BP_IF);
    encode_char(program, "to", BP_COMMA);
    encode_char(program, "step", BP_COMMA);
    encode(program, "not", "1-");
    // Constants
    encode(program, "OUTPUT", "1");
    encode(program, "INPUT", "0");
    encode(program, "HIGH", "1");
    encode(program, "LOW", "0");
    encode(program, "false", "0");
    encode(program, "true", "1");
    encode(program, "LF", "10");
    encode(program, "CR", "13");
    // Remove tabs, spaces, line feed and carriage return
    remove(program, BP_CR);
    remove(program, BP_LF);
    remove(program, BP_SPACE);
    remove(program, BP_TAB);
    // Reset indexes
    var_id = BP_OFFSET;
    string_id = BP_OFFSET;
    fun_id = BP_OFFSET;
    // Post-compilation error check
    post_compilation_checks(program);
    return !fail;
  };
};
