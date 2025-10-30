
#pragma once
#include "BIPLAN_Defines.h"

typedef void (*bcc_error_t)(uint16_t line, const char *p, const char *s);

extern bcc_error_t bcc_error_callback;
void bcc_error(uint16_t line, const char *position, const char *string);
uint16_t bcc_line(const char *prog, const char *pos);
int bcc_check_delimeter(const char *prog, char a, char b, int ignore);
void bcc_find_end(char *prog);
int bcc_in_string(const char *prog, const char *pos);
void bcc_remove(char *prog, char v1, char v2, char v3, char v4);
void bcc_remove_comments(char *prog);
void bcc_compile_char_constants(char *prog);
char *bcc_compile_step(char *prog, char *pos, const char *key, const char *code, char post, int addr, char end);
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
int bcc_run(char *prog);

extern int  bcc_fail;
extern char bcc_var_id;
extern char bcc_string_id;
extern char bcc_fun_id;
extern char *bcc_stop;

