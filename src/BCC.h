
#pragma once
#include "BIPLAN_Defines.h"

typedef void (*bcc_error_t)(uint16_t line, const char *p, const char *s);

extern bcc_error_t bcc_error_callback;
void bcc_error(uint16_t line, const char *position, const char *string);
uint16_t bcc_line(const char *prog, const char *pos);
void bcc_check_undefined_functions(const char *prog);
int bcc_check_delimeter(const char *prog, char a, char b, int ignore);
void bcc_find_end(char *prog);
int bcc_in_string(const char *prog, const char *pos);
void bcc_remove(char *prog, char v1, char v2, char v3, char v4);
void bcc_remove_comments(char *prog);
void bcc_compile_char_constants(char *prog);
char *bcc_compile_step(char *prog, char *pos, const char *key, const char *code, char post, int addr, char end, uint8_t kl);
void bcc_compile(char *prog, const char *key, const char *code, char post, int addr, char end);
void bcc_compile_char(char *prog, const char *key, char code, char post, int addr);
char *bcc_find_longest_var_name(char *prog, char var_type);
char *bcc_compile_variable(char *prog, char *position, char var_type);
void bcc_compile_variables(char *prog, char var_type);
char *bcc_find_longest_keyword(char *prog, int t);
int bcc_compile_function_step(char *prog);
void bcc_compile_functions(char *prog);
void bcc_compile_for(char *prog);
int bcc_compile_macro(char *prog);
void bcc_compile_macros(char *prog);
char *bcc_compile_include(char *prog, char *pos);
void bcc_compile_includes(char *prog);
int bcc_pre_compilation_checks(const char *prog);
void bcc_post_compilation_checks(const char *prog);
void bcc_compile_syntax(char *prog);
void bcc_compile_system_functions(char *prog);
int bcc_run(char *prog);

/* State ------------------------------------------------------------------- */
extern int  bcc_fail;
extern char bcc_var_id;
extern char bcc_string_id;
extern char bcc_fun_id;
extern char *bcc_stop;

/* System functions structure with human-readable and compiled versions ---- */
struct bcc_keyword_char_code {
  const char *human;
  char code;
  uint8_t len;
};

/* System functions table with human-readable and compiled versions -------- */
static const struct bcc_keyword_char_code bcc_sys_functions[] = {
  {BP_RND_HUMAN, BP_RND, 6},
  {BP_MILLIS_HUMAN, BP_MILLIS, 6},
  {BP_DELAY_HUMAN, BP_DELAY, 5},
  {BP_SERIAL_HUMAN, BP_SERIAL, 6},
  {BP_CONTINUE_HUMAN, BP_CONTINUE, 8},
  {BP_RESTART_HUMAN, BP_RESTART, 7},
  {BP_RETURN_HUMAN, BP_RETURN, 6},
  {BP_SYSTEM_HUMAN, BP_SYSTEM, 6},
  {BP_CURSOR_HUMAN, BP_CURSOR, 6},
  {BP_LTOA_HUMAN, BP_LTOA, 6},
  {BP_ATOL_HUMAN, BP_ATOL, 6},
  {BP_INPUT_HUMAN, BP_INPUT, 5},
  {BP_BREAK_HUMAN, BP_BREAK, 5},
  {BP_PRINT_HUMAN, BP_PRINT, 5},
  {BP_WHILE_HUMAN, BP_WHILE, 5},
  {BP_ENDIF_HUMAN, BP_ENDIF, 3},
  {BP_SIZEOF_HUMAN, BP_SIZEOF, 4},
  {BP_WRITE_HUMAN, BP_WRITE, 5},
  {BP_INDEX_HUMAN, BP_INDEX, 5},
  {BP_CLOSE_HUMAN, BP_CLOSE, 5},
  {BP_READ_HUMAN, BP_READ, 4},
  {BP_OPEN_HUMAN, BP_OPEN, 4},
  {BP_NEXT_HUMAN, BP_NEXT, 4},
  {BP_FILE_HUMAN, BP_FILE, 4},
  {BP_CHAR_HUMAN, BP_CHAR, 5},
  {BP_ELSE_HUMAN, BP_ELSE, 4},
  {BP_END_HUMAN, BP_END, 4},
  {BP_FOR_HUMAN, BP_FOR, 3},
  {BP_ADC_HUMAN, BP_ADC, 3},
  {BP_IF_HUMAN, BP_IF, 2},
  {BP_IO_HUMAN, BP_IO, 2},
  {BP_TO_HUMAN, BP_COMMA, 2},
  {BP_DONE_HUMAN, BP_DONE, 4},
  {NULL, 0, 0}
};

/* Syntax table with human-readable and compiled versions ------------------ */
static const struct bcc_keyword_char_code bcc_syntax[] = {
  {BP_STR_ACC_HUMAN, BP_STR_ACC, 2},
  {BP_VAR_ACC_HUMAN, BP_VAR_ACC, 2},
  {BP_MEM_ACC_HUMAN, BP_MEM_ACC, 4},
  {BP_EQ_HUMAN, BP_EQ, 2},
  {BP_NOT_EQ_HUMAN, BP_NOT_EQ, 2},
  {BP_GTOEQ_HUMAN, BP_GTOEQ, 2},
  {BP_LTOEQ_HUMAN, BP_LTOEQ, 2},
  {BP_LOGIC_OR_HUMAN, BP_LOGIC_OR, 2},
  {BP_LOGIC_AND_HUMAN, BP_LOGIC_AND, 2},
  {BP_R_SHIFT_HUMAN, BP_R_SHIFT, 2},
  {BP_L_SHIFT_HUMAN, BP_L_SHIFT, 2},
  {"=", BP_SPACE, 1},
  {BP_INCREMENT_HUMAN, BP_INCREMENT, 2},
  {BP_DECREMENT_HUMAN, BP_DECREMENT, 2},
  {BP_BITWISE_NOT_HUMAN, BP_BITWISE_NOT, 1},
  {NULL, 0, 0}
};
