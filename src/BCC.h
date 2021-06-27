
/* ______     ______           ______   _
  |      | | |      | |              | | \    |
  |_____/  | |______| |        ______| |  \   |
  |     \  | |        |       |      | |   \  |
  |______| | |        |______ |______| |    \_| CR.1
  BIPLAN (Byte coded Interpreted Programming Language)
  Giovanni Blu Mitolo 2017-2021 - gioscarab@gmail.com
      _____              _________________________
     |   | |            |_________________________|
     |   | |_______________||__________   \___||_________ |
   __|___|_|               ||          |__|   ||     |   ||
  /________|_______________||_________________||__   |   |D
    (O)                 |_________________________|__|___/|
                                           \ /            |
                                           (O)
  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.

  BCC (BIPLAN Compiler Collection) - BIPLAN to BIP compiler  */

#pragma once
#include "BIPLAN_Defines.h"
#include "BCC.h"

/* ACCEPTABLE KEYWORD CHARACTER ------------------------------------------ */
#define BCC_IS_KEYWORD(C) \
  ((C >= 'a' && C <= 'z') || (C >= 'A' && C <= 'Z') || (C == '_'))

/* ACCEPTABLE KEYWORD CHARACTER ------------------------------------------ */
#define BCC_IS_ADDRESS(C) ( \
  (C == BP_VAR_ADDR) || (C == BP_STR_ADDR) || \
  (C == BP_FUNCTION) || (C == BP_FUN_DEF) \
)

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
  bool check_delimeter(char *prog, char a, char b, char c = 0) {
    uint16_t ia = 0, ib = 0;
    char *p = prog;
    while(*p != 0) {
      if(!is_in_string(prog, p) && !BCC_IS_ADDRESS(*(p - 1))) {
        if(*p == a) ia++;
        if((*p == b) || (*p == c)) ib++;
      } p++;
    } return (ia == ib);
  };

  /* CHECK IF POINTER IS IN A STRING -------------------------------------- */
  bool is_in_string(char *prog, char *pos) {
    bool in_str = false;
    char *p = prog;
    while(pos >= p) {
      // Returns false if " is found outside a string
      if((pos == p) && (*p == BP_STRING) && !in_str) return in_str;
      if(*p == BP_STRING) in_str = !in_str;
      p++;
    } return in_str;
  };

  /* REMOVE CHARACTER FROM PROGRAM ---------------------------------------- */
  void remove(char *s, char v) {
    if(fail) return;
    char *i = s, *j = s;
    bool in_str = false;
    while(*j != 0) {
      *i = *j++;
      if(*i == BP_STRING) in_str = !in_str;
      if(*i != v) i++;
      else if(in_str) i++;
    } *i = 0;
  };

  /* REMOVE COMMENTS FROM PROGRAM ----------------------------------------- */
  void remove_comments(char *prog) {
    if(fail) return;
    char *i = prog, *j = prog;
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

  /* COMPILE CHARACTER CONSTANTS '@' -> 64 --------------------------------- */
  void compile_char_constants(char *prog) {
    char *p = prog, b[3] = {};
    while(*p != 0) {
      if(!is_in_string(prog, p) && (*p == BP_SINGLE_QUOTE)) {
        if(*(p + 2) != BP_SINGLE_QUOTE) {
          error(0, BP_ERROR_SINGLE_QUOTE);
          return;
        }
        BPM_ITOA(*(++p), b);
        p--;
        for(uint8_t i = 0; i < 3; i++)
          *(p++) = (((b + i) == NULL) || !b[i]) ? BP_SPACE : b[i];
      } else p++;
    }
  };

  /* COMPILE PROGRAM KEYWORD IN BIP MACHINE LANGUAGE ---------------------- */
  char *compile_pass(
    char *prog,
    char *pos,
    const char *key,
    const char *code,
    char post = 0,
    bool pre = 0
  ) {
    char *p;
    uint8_t kl = strlen(key), cl = strlen(code);
    p = strstr(pos, key);
    if(p && *p) {
      if(is_in_string(prog, p) || (pre && BCC_IS_ADDRESS(*(p - 1)))) {
        p = strstr(p + kl, key);
        if(p && *p) return p;
        else return NULL;
      }
      for(uint16_t i = 0; i < kl; i++, p++)
        if(i < cl && code[i]) *p = code[i];
        else *p = BP_SPACE;
      if(post) {
        while(*p == BP_SPACE) p++;
        if(*p == post) *p = BP_SPACE;
      }
      return p;
    } else return NULL;
  };

  void compile(
    char *prog, const char *key, const char *code, char post = 0, bool pre = 0
  ) {
    if(fail) return;
    char *p = prog;
    while(p) p = compile_pass(prog, p, key, code, post, pre);
  };

  void compile_char(
    char *prog, const char *key, const char code, char post = 0, bool pre = 0
  ) {
    if(fail) return;
    char *p = prog;
    const char c[2] = {code, 0};
    while(p) p = compile_pass(prog, p, key, (const char *)c, post, pre);
  };

  /* COMPILE PROGRAM VARIABLE IN BIP MACHINE LANGUAGE $v -> $# ------------- */
  char *compile_variable(char *prog, char *position, char var_type) {
    char *p, str[BP_KEYWORD_MAX], code[4] = {var_type, 0, 0, 0};
    uint8_t n;
    if((p = find_longest_var_name(prog, var_type)) != NULL) {
      str[n++] = var_type;
      str[n++] = *(++p);
      if(var_type == BP_VAR_ADDR) if(BCC_IS_ADDRESS(var_id)) var_id++;
      else if(BCC_IS_ADDRESS(string_id)) string_id++;
      *(p++) = (var_type == BP_VAR_ADDR) ? var_id : string_id;
      for(uint16_t i = 0; i < BP_KEYWORD_MAX - 1; i++, p++)
        if(BCC_IS_KEYWORD(*p)) {
          str[n++] = *p;
          *p = BP_SPACE;
          if((i == (BP_KEYWORD_MAX - 2)) && (BCC_IS_KEYWORD(*(p + 1)))) {
            error(0, BP_ERROR_VARIABLE_NAME);
            return NULL;
          }
        } else break;
      if(n) {
        str[n] = 0;
        code[1] = (var_type == BP_VAR_ADDR) ? var_id : string_id;
        code[2] = 0;
        compile(position, str, code, 0, 1);
        p = strstr(position, str);
        if((p && *p) && !is_in_string(prog, p)) return p;
        if(var_type == BP_VAR_ADDR) var_id++; else string_id++;
        return (char *)position;
      } return p;
    } return NULL;
  };

  void compile_variables(char *prog, char var_type) {
    if(fail) return;
    char *p = prog;
    while(p) p = compile_variable(prog, p, var_type);
  };

  char *find_longest_var_name(char *prog, char var_type) {
    char *p = prog, *longest = 0;
    uint8_t result = 0;
    while(*p != 0)
      if(*(p++) == var_type) {
        if(is_in_string(prog, p - 1) || BCC_IS_ADDRESS(*(p - 2))) continue;
        uint8_t i = 0;
        while(BCC_IS_KEYWORD(*p)) {
          i++;
          p++;
        }
        if(i > result) {
          longest = p - (i + 1);
          result = i;
        }
      }
    if(result) return (char *)longest;
    else return NULL;
  };

  /* COMPILE FOR ------------------------------------------------------------
     from @ $# to @  # (BP_VAR_ADDR is removed) */
  void compile_for(char *prog) {
    char c[2] = {BP_FOR, 0};
    compile(prog, c, c, BP_VAR_ADDR, 1);
  };

  /* COMPILE FUNCTION IN BIP MACHINE LANGUAGE ----------------------------- */
  char *compile_function_pass(char *prog, char *pos) {
    char fn_keyword[BP_KEYWORD_MAX];
    char fn_address[3];
    char *p = strstr(pos, BP_FUN_DEF_HUMAN);
    uint8_t keyword_length = 0;
    if(p && *p) {
      if(is_in_string(prog, p)) {
        p = strstr(p + 1, BP_FUN_DEF_HUMAN);
        if(p && *p) return p;
        else return NULL;
      }
      if(BCC_IS_ADDRESS(fun_id)) fun_id++;
      *(p++) = BP_FUN_DEF;
      *(p++) = fun_id;
      while(*p != BP_SPACE) *(p++) = BP_SPACE;
      while(p++ && (*p != BP_L_RPARENT)) {
        fn_keyword[keyword_length++] = *p;
        *p = BP_SPACE;
      } // Remove commas from definition
      *p = BP_SPACE;
      while((*p != BP_R_RPARENT) || BCC_IS_ADDRESS(*(p - 1))) {
        if((*p == BP_COMMA) && !BCC_IS_ADDRESS(*(p - 1))) *p = BP_SPACE;
        p++;
      }
      if(keyword_length) {
        if(keyword_length >= BP_KEYWORD_MAX) {
          error(0, BP_ERROR_FUNCTION_NAME);
          return NULL;
        }
        fn_keyword[keyword_length] = 0;
        fn_address[0] = BP_FUNCTION;
        fn_address[1] = fun_id++;
        fn_address[2] = 0;
        compile(prog, fn_keyword, fn_address, BP_L_RPARENT);
        p = strstr(pos, fn_keyword);
        if(p && *p) return p;
        else return NULL;
      } return p;
    } else return NULL;
  };

  void compile_functions(char *prog) {
    if(fail) return;
    char *pos = prog;
    while(pos) pos = compile_function_pass(prog, pos);
  };

  /* PRE-COMPILATION CHECKS ----------------------------------------------- */
  bool pre_compilation_checks(char *prog) {
    if(!check_delimeter(prog, BP_L_RPARENT, BP_R_RPARENT))
      error(0, BP_ERROR_ROUND_PARENTHESIS);  // Check () parentheses
    if(!check_delimeter(prog, BP_ACCESS, BP_ACCESS_END))
      error(0, BP_ERROR_SQUARE_PARENTHESIS); // Check [] parentheses
    if(!check_delimeter(prog, BP_STRING, BP_STRING))
      error(0, BP_ERROR_STRING_END);         // Check "" string separator
    return !fail;
  };

  /* POST-COMPILATION CHECKS ----------------------------------------------- */
  void post_compilation_checks(char *prog) {
    if(!check_delimeter(prog, BP_NEXT, BP_FOR, BP_WHILE))
      error(0, BP_ERROR_NEXT);  // Check for/while-next
    if(!check_delimeter(prog, BP_IF, BP_ENDIF))
      error(0, BP_ERROR_BLOCK); // Check if-end
    // Check variables, strings and functions buffer bounds
    if((fun_id - BP_OFFSET) >= BP_FUN_MAX) error(0, BP_ERROR_FUNCTION_MAX);
    if((string_id - BP_OFFSET) >= BP_STRINGS) error(0, BP_ERROR_STRING_MAX);
    if((var_id - BP_OFFSET) >= BP_VARIABLES) error(0, BP_ERROR_VARIABLE_MAX);
  };

  /* RUN COMPILATION ------------------------------------------------------ */
  bool run(char *prog) {
    remove_comments(prog);
    // Compile character constants in their decimal value using itoa
    compile_char_constants(prog);
    if(!pre_compilation_checks(prog)) return false;
    // :string $variable @memory reference access
    compile_char(prog, BP_STR_ACC_HUMAN, BP_STR_ACC);
    compile_char(prog, BP_VAR_ACC_HUMAN, BP_VAR_ACC);
    compile_char(prog, BP_MEM_ACC_HUMAN, BP_MEM_ACC);
    // Logic == != >= <= || &&
    compile_char(prog, BP_EQ_HUMAN, BP_EQ);
    compile_char(prog, BP_NOT_EQ_HUMAN, BP_NOT_EQ);
    compile_char(prog, BP_GTOEQ_HUMAN, BP_GTOEQ);
    compile_char(prog, BP_LTOEQ_HUMAN, BP_LTOEQ);
    compile_char(prog, BP_LOGIC_OR_HUMAN, BP_LOGIC_OR);
    compile_char(prog, BP_LOGIC_AND_HUMAN, BP_LOGIC_AND);
    // Bitwise >> <<
    compile_char(prog, BP_R_SHIFT_HUMAN, BP_R_SHIFT);
    compile_char(prog, BP_L_SHIFT_HUMAN, BP_L_SHIFT);
    // Remove syntactic sugar
    compile_char(prog, "=", ' ');
    // Unary ++ --
    compile_char(prog, BP_INCREMENT_HUMAN, BP_INCREMENT);
    compile_char(prog, BP_DECREMENT_HUMAN, BP_DECREMENT);
    // Bitwise not !
    compile_char(prog, BP_BITWISE_NOT_HUMAN, BP_BITWISE_NOT);
    // Encode variables and functions
    compile_variables(prog, BP_VAR_ADDR);
    compile_variables(prog, BP_STR_ADDR);
    for(uint8_t i = 0; i < BP_FUN_MAX; i++) compile_functions(prog);
    // System calls
    compile_char(prog, BP_RND_HUMAN, BP_RND);
    compile_char(prog, BP_MILLIS_HUMAN, BP_MILLIS);
    compile_char(prog, BP_DELAY_HUMAN, BP_DELAY);
    compile_char(prog, BP_SQRT_HUMAN, BP_SQRT);
    // Language syntax
    compile_char(prog, BP_SERIAL_HUMAN, BP_SERIAL);
    compile_char(prog, BP_RESULT_HUMAN, BP_RESULT);
    compile_char(prog, BP_CONTINUE_HUMAN, BP_CONTINUE);
    compile_char(prog, BP_RESTART_HUMAN, BP_RESTART);
    compile_char(prog, BP_NUMERIC_HUMAN, BP_NUMERIC);
    compile_char(prog, BP_RETURN_HUMAN, BP_RETURN);
    compile_char(prog, BP_SYSTEM_HUMAN, BP_SYSTEM);
    compile_char(prog, BP_CURSOR_HUMAN, BP_CURSOR);
    compile_char(prog, "locals:", ' ');
    compile_char(prog, BP_ATOL_HUMAN, BP_ATOL);
    compile_char(prog, BP_INPUT_HUMAN, BP_INPUT);
    compile_char(prog, BP_BREAK_HUMAN, BP_BREAK);
    compile_char(prog, BP_PRINT_HUMAN, BP_PRINT);
    compile_char(prog, BP_WHILE_HUMAN, BP_WHILE);
    compile_char(prog, BP_ENDIF_HUMAN, BP_ENDIF);
    compile_char(prog, BP_SIZEOF_HUMAN, BP_SIZEOF);
    compile_char(prog, BP_WRITE_HUMAN, BP_WRITE);
    compile_char(prog, BP_INDEX_HUMAN, BP_INDEX);
    compile_char(prog, BP_CLOSE_HUMAN, BP_CLOSE);
    compile_char(prog, BP_READ_HUMAN, BP_READ);
    compile_char(prog, BP_OPEN_HUMAN, BP_OPEN);
    compile_char(prog, BP_NEXT_HUMAN, BP_NEXT);
    compile_char(prog, BP_FILE_HUMAN, BP_FILE);
    compile_char(prog, BP_CHAR_HUMAN, BP_CHAR);
    compile_char(prog, BP_ELSE_HUMAN, BP_ELSE);
    compile_char(prog, BP_JUMP_HUMAN, BP_JUMP);
    compile_char(prog, BP_LABEL_HUMAN, BP_LABEL);
    compile_char(prog, BP_END_HUMAN, BP_END);
    compile_char(prog, BP_FOR_HUMAN, BP_FOR);
    // Remove BP_VAR_ADDR that follows for
    compile_for(prog);
    compile_char(prog, BP_ADC_HUMAN, BP_ADC);
    compile_char(prog, "step", BP_COMMA);
    compile(prog, "not", "1-");
    compile_char(prog, BP_IF_HUMAN, BP_IF);
    compile_char(prog, BP_IO_HUMAN, BP_IO);
    compile_char(prog, "to", BP_COMMA);
    // Constants
    compile(prog, "OUTPUT", "1");
    compile(prog, "INPUT", "0");
    compile(prog, "HIGH", "1");
    compile(prog, "LOW", "0");
    compile(prog, "EOF", "-1");
    compile(prog, "false", "0");
    compile(prog, "true", "1");
    compile(prog, "LF", "10");
    compile(prog, "CR", "13");
    // Remove tabs, spaces, line feed and carriage return
    remove(prog, BP_CR);
    remove(prog, BP_LF);
    remove(prog, BP_SPACE);
    remove(prog, BP_TAB);
    // Reset indexes
    var_id = BP_OFFSET;
    string_id = BP_OFFSET;
    fun_id = BP_OFFSET;
    post_compilation_checks(prog);
    return !fail;
  };
};
