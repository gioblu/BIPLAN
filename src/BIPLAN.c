
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
  BIP byte-code interpreter */

#pragma once
#include "BIPLAN.h"

#define BP_SYS_REL_BOUNDS(R, B, E) \
  DCD_NEXT; \
  R = bip_relation(); \
  if((R < 0) || (R >= B)) { bip_error(dcd_ptr, E); }

/* SYSTEM CALL WITH 1 RELATION PARAMETER ----------------------------------- */

#define BP_SYS_REL_1(F, T) \
  if(dcd_current == BP_STRING) { \
    bip_read_string(bip_string); \
    for(uint16_t i = 0; i < sizeof(bip_string); i++) \
      F(T, bip_string[i]); \
    BP_EMPTY_STRING; \
  } else if(bip_ignore(BP_STR_ADDR)) { \
    uint8_t id = *(dcd_ptr - 1) - BP_OFFSET; \
    for(uint16_t i = 0; i < sizeof(bip_strings[id]); i++) \
      F(T, bip_strings[id][i]); \
  } else { \
    BP_VAR_T r = bip_relation(); \
    BPM_LTOA(r, bip_string); \
    for(uint16_t i = 0; i < BP_STRING_MAX; i++) \
      F(T, bip_string[i]); \
    BP_EMPTY_STRING; \
  }

/* SYSTEM CALL WITH 1 STRING PARAMETER ------------------------------------- */

#define BP_SYS_STR_1(F, V) \
  DCD_NEXT; \
  if(bip_ignore(BP_VAR_ADDR)) { \
    v = bip_get_variable(*(dcd_ptr - 1) - BP_OFFSET) - 48;\
  } else if(bip_ignore(BP_STR_ADDR)) { \
    V = F(bip_strings[*(dcd_ptr - 1) - BP_OFFSET]); \
  } else if(dcd_current == BP_STRING) { \
    bip_read_string(bip_string); \
    V = F(bip_string); \
    BP_EMPTY_STRING; \
  }

/* SYSTEM CALL WITH 2 EXPRESSION PARAMETER --------------------------------- */
#define BP_SYS_EXP_2(F) \
  BP_VAR_T bip_x = bip_expression(), bip_y; \
  BP_EXPECT(BP_COMMA); \
  bip_y = bip_expression(); \
  F(bip_x, bip_y);

/* EMPTY STRING ------------------------------------------------------------ */
#define BP_EMPTY_STRING \
  for(BP_VAR_T emptstr = 0; emptstr < BP_STRING_MAX; emptstr++) \
    bip_string[emptstr] = 0;

/* EXPECT A CERTAIN CODE, OTHERWISE THROW ERROR ---------------------------- */
#define BP_EXPECT(C) \
  if(C != dcd_current) bip_error(dcd_ptr, BP_ERROR_SYMBOL); \
  else DCD_NEXT;

/* GET VARIABLE ------------------------------------------------------------ */
#define BP_GET_VARIABLE(N, V) \
  if(N >= 0 && N <= BP_VARIABLES) { V =  bip_variables[N]; } \
  else { bip_error(dcd_ptr, BP_ERROR_VARIABLE_GET); }

/* SET VARIABLE ------------------------------------------------------------ */
#define BP_SET_VARIABLE(N, V) \
  if(N >= 0 && N <= BP_VARIABLES) { bip_variables[N] = V; } \
  else { bip_error(dcd_ptr, BP_ERROR_VARIABLE_SET); }

/* UNARY -- ++ ------------------------------------------------------------- */
#define BP_UNARY(V) \
  while(dcd_current == BP_INCREMENT || dcd_current == BP_DECREMENT) { \
    if(dcd_current == BP_INCREMENT) { V++; } else { V--; } \
    DCD_NEXT; \
  }

/* BUFFERS ----------------------------------------------------------------- */
BP_VAR_T           bip_variables     [BP_VARIABLES];
uint8_t            bip_memory        [BP_MEM_SIZE];
char               bip_string        [BP_STRING_MAX];
char               bip_strings       [BP_STRINGS][BP_STRING_MAX];
struct bip_cycle_t bip_cycles        [BP_CYCLE_DEPTH];
struct bip_fun_t   bip_functions     [BP_FUN_DEPTH];
struct bip_def_t   bip_definitions   [BP_FUN_MAX];
bip_files_t        bip_files         [BP_FILES_MAX];
/* STATE ------------------------------------------------------------------- */
char              *bip_program_start  = NULL;
uint8_t            bip_fw_id          = 0;
int                bip_fn_id          = 0;
bool               bip_ended          = false;
uint8_t            bip_return_type    = 0;
/* CALLBACKS --------------------------------------------------------------- */
bip_error_t        bip_error_fun;
BPM_PRINT_T        bip_print_fun;
BPM_INPUT_T        bip_data_in_fun;
BPM_SERIAL_T       bip_serial_fun;

/* END PROGRAM ------------------------------------------------------------- */
void bip_end_call() { BP_EXPECT(BP_END); bip_ended = true; };

/* FINISHED ---------------------------------------------------------------- */
bool bip_finished() { return bip_ended || dcd_finished(); };

/* RUN --------------------------------------------------------------------- */
bool bip_run() { bip_statement(); return !bip_ended;  };

/* RESTART PROGRAM CALL ---------------------------------------------------- */
void bip_restart_call() { bip_set_default(); DCD_INIT(bip_program_start); };

/* ERROR ------------------------------------------------------------------- */
void bip_error(char *position, const char *string) {
  bip_error_fun(position, string);
  bip_ended = true;
};

/* INDEX LINES ------------------------------------------------------------- */
void bip_index_definitions(char* program) {
  uint16_t param, l = 0;
  while(dcd_current != BP_ENDOFINPUT) {
    if(bip_ignore(BP_FUN_DEF)) {
      param = 0;
      l = *(dcd_ptr - 1) - BP_OFFSET;
      for(uint8_t i = 0; i < BP_PARAMS; i++)
        bip_definitions[l].params[i] = BP_PARAMS;
      do {
        if(bip_ignore(BP_VAR_ADDR))
          bip_definitions[l].params[param++] = *(dcd_ptr - 1);
      } while(*dcd_ptr != BP_R_RPARENT);
      bip_definitions[l].address = dcd_ptr + 1;
    } DCD_NEXT;
  }
};

/* PROCESS LABEL STATEMENTS ------------------------------------------------ */
void bip_process_labels(char* program) {
  DCD_INIT(program);
  while(dcd_current != BP_ENDOFINPUT) {
    if(dcd_current == BP_LABEL) bip_statement();
    else DCD_NEXT;
  }
};

/* GET FILE ID ------------------------------------------------------------- */
BP_VAR_T bip_get_file_id() {
  for(uint16_t i = 0; i < BP_FILES_MAX; i++)
    if(bip_files[i].free) {
      bip_files[i].free = false;
      return i;
    }
  bip_error(dcd_ptr, BP_ERROR_FILE_MAX);
  return BP_FILES_MAX;
};

/* INITIALIZE INTERPRETER -------------------------------------------------- */
void bip_init(
  char *program,
  bip_error_t error,
  BPM_PRINT_T print,
  BPM_INPUT_T data_input,
  BPM_SERIAL_T    s
) {
  bip_program_start = program;
  bip_set_default();
  bip_process_labels(program);
  DCD_INIT(program);
  bip_index_definitions(program);
  DCD_INIT(program);
  bip_serial_fun = s;
  bip_error_fun = error;
  bip_print_fun = print;
  bip_data_in_fun = data_input;
};

void bip_set_default() {
  bip_fw_id = 0;
  bip_fn_id = 0;
  bip_ended = false;
  for(BP_VAR_T i = 0; i < BP_MEM_SIZE; i++) bip_memory[i] = 0;
  for(BP_VAR_T i = 0; i < BP_VARIABLES; i++) bip_variables[i] = 0;
  for(BP_VAR_T i = 0; i < BP_STRINGS; i++)
    for(BP_VAR_T c = 0; c < BP_STRING_MAX; c++) bip_strings[i][c] = 0;
  BP_EMPTY_STRING;
};

/* IGNORE A CERTAIN CODE --------------------------------------------------- */
bool bip_ignore(char c) { if((c = (c == dcd_current))) DCD_NEXT; return c; };

/* GET VARIABLE ------------------------------------------------------------ */
BP_VAR_T bip_get_variable(int n) {
  if(n >= 0 && n <= BP_VARIABLES) return bip_variables[n];
  bip_error(dcd_ptr, BP_ERROR_VARIABLE_GET);
  return 0;
};

/* GET ONE CHAR FROM STRING ------------------------------------------------ */
char bip_string_char(int s, int c) {
  if((c >= BP_STRING_MAX) || (s < 0 && s >= BP_STRINGS)) {
    bip_error(dcd_ptr, BP_ERROR_STRING_GET);
    return 0;
  } return bip_strings[s][c];
};

/* NUMERIC VARIABLE: 1234 ---------------------------------------------------*/
BP_VAR_T bip_var_factor() {
  BP_VAR_T v;
  uint8_t id = BP_VARIABLES;
  int8_t pre = 0;
  bool index;
  BP_UNARY(pre);
  DCD_IGNORE(BP_INDEX, index);
  uint8_t type = dcd_current;
  DCD_NEXT;
  id = *(dcd_ptr - 1) - BP_OFFSET;
  if(index && ((type == BP_VAR_ADDR) || (type == BP_STR_ADDR)))
    return id + pre;
  else if(type == BP_VAR_ADDR) {
    BP_GET_VARIABLE(id, v);
    v += pre;
    if(pre != 0) BP_SET_VARIABLE(id, v);
  } else if((type == BP_STR_ADDR) && (dcd_current == BP_ACCESS)) {
    v = bip_string_char(id, bip_access(BP_ACCESS));
    bip_return_type = BP_ACCESS;
  } else {
    bip_return_type = BP_STR_ADDR;
    v = id;
  } return v;
};

/* ACCESS MEMORY VIA INDEX [ ] --------------------------------------------- */
BP_VAR_T bip_access(BP_VAR_T v) {
  BP_EXPECT(v);
  v = bip_relation();
  BP_EXPECT(BP_ACCESS_END);
  return v;
};

/* FACTOR: (n) ------------------------------------------------------------- */
BP_VAR_T bip_factor() {
  BP_VAR_T v = 0, b;
  bool bitwise_not = 0, minus = 0;
  DCD_IGNORE(BP_BITWISE_NOT, bitwise_not);
  DCD_IGNORE(BP_MINUS, minus);
  switch(dcd_current) {
    case BP_NUMBER: v = BPM_ATOL(dcd_ptr); BP_EXPECT(BP_NUMBER); break;
    case BP_VAR_ACC: v = bip_get_variable(bip_access(BP_VAR_ACC)); break;
    case BP_STR_ACC:
      v = bip_access(BP_STR_ACC);
      if(dcd_current == BP_ACCESS)
        v = bip_string_char(v, bip_access(BP_ACCESS));
      break;
    case BP_MEM_ACC: v = bip_memory[bip_access(BP_MEM_ACC)]; break;
    case BP_FILE: v = bip_file_get_call(); break;
    case BP_IO: v = bip_io_get_call(); break;
    case BP_MILLIS: DCD_NEXT; v = (BPM_MILLIS() % BP_VAR_MAX); break;
    case BP_ADC: v = bip_adc_call(); break;
    case BP_RND: DCD_NEXT;  v = bip_random_call(); break;
    case BP_SQRT: DCD_NEXT; v = sqrt(bip_expression()); break;
    case BP_FUNCTION: v = bip_function_call(); DCD_NEXT; break;
    case BP_SERIAL: v = bip_serial_call(); break;
    case BP_INPUT: v = BPM_INPUT(bip_data_in_fun); DCD_NEXT; break;
    case BP_L_RPARENT:
      DCD_NEXT; v = bip_relation(); BP_EXPECT(BP_R_RPARENT); break;
    case BP_RESULT: DCD_NEXT; v = bip_result_get_call(); break;
    case BP_SIZEOF: v = bip_sizeof_call(); break;
    case BP_SYSTEM: v = bip_system_call(); break;
    case BP_ATOL: v = bip_atol_call(); break;
    case BP_NUMERIC:
      DCD_NEXT; v = bip_relation(); v = (v >= 48) && (v <= 57); break;
    default: v = bip_var_factor();
  } v = (minus) ? -v : v;
  return (bitwise_not) ? ~v : v;
};

/* TERM: *, /, % ------------------------------------------------------------*/
BP_VAR_T bip_term() {
  BP_VAR_T f1 = bip_factor(), f2 = 0;
  uint8_t op = dcd_current;
  while(op == BP_MULT || op == BP_DIV || op == BP_MOD) {
    DCD_NEXT;
    f2 = bip_factor();
    if(!f2 && (op == BP_DIV)) bip_error(dcd_ptr, BP_ERROR_DIV_ZERO);
    else {
      switch(op) {
        case BP_MULT: f1 = f1 * f2; break;
        case BP_DIV:  f1 = f1 / f2; break;
        case BP_MOD:  f1 = f1 % f2; break;
      } op = dcd_current;
    }
  } return f1;
};

/* EXPRESSION +, -, &, | ----------------------------------------------------*/
BP_VAR_T bip_expression() {
  BP_VAR_T t1 = bip_term(), t2 = 0;
  uint8_t op = dcd_current;
  while(
    op == BP_PLUS || op == BP_MINUS || op == BP_AND || op == BP_OR ||
    op == BP_XOR || op == BP_L_SHIFT || op == BP_R_SHIFT
  ) {
    DCD_NEXT;
    t2 = bip_term();
    switch(op) {
      case BP_PLUS:    t1 = t1 + t2;  break;
      case BP_MINUS:   t1 = t1 - t2;  break;
      case BP_AND:     t1 = t1 & t2;  break;
      case BP_OR:      t1 = t1 | t2;  break;
      case BP_XOR:     t1 = t1 ^ t2;  break;
      case BP_L_SHIFT: t1 = t1 << t2; break;
      case BP_R_SHIFT: t1 = t1 >> t2; break;
    } op = dcd_current;
  } return t1;
};

/* RELATION <, >, = -------------------------------------------------------- */
BP_VAR_T bip_relation() {
  BP_VAR_T r1 = bip_expression(), r2 = 0;
  uint8_t op = dcd_current;
  while(
    op == BP_EQ || op == BP_NOT_EQ || op == BP_LTOEQ || op == BP_GTOEQ ||
    op == BP_LT || op == BP_GT || op == BP_LOGIC_OR || op == BP_LOGIC_AND
  ) {
    DCD_NEXT;
    r2 = bip_expression();
    switch(op) {
      case BP_NOT_EQ:    r1 = r1 != r2; break;
      case BP_EQ:        r1 = r1 == r2; break;
      case BP_GTOEQ:     r1 = r1 >= r2; break;
      case BP_LTOEQ:     r1 = r1 <= r2; break;
      case BP_LOGIC_OR:  r1 = r1 || r2; break;
      case BP_LOGIC_AND: r1 = r1 && r2; break;
      case BP_LT:        r1 = r1 <  r2; break;
      case BP_GT:        r1 = r1 >  r2; break;
    } op = dcd_current;
  } return r1;
};

/* JUMP -------------------------------------------------------------------- */
void bip_jump_call() { DCD_GOTO(bip_program_start + bip_relation()); }

/* READ SAFELY A STRING ---------------------------------------------------- */
void bip_read_string(char *s) {
  if(!decoder_string(s, sizeof(bip_string)))
    bip_error(dcd_ptr, BP_ERROR_STRING_END);
  else BP_EXPECT(BP_STRING);
};

/* PRINT ------------------------------------------------------------------- */
void bip_print_call() {
  do {
    BP_VAR_T v = 0;
    bip_ignore(BP_COMMA);
    bool is_char = bip_ignore(BP_CHAR);
    if(dcd_current == BP_STR_ACC) {
      v = bip_access(BP_STR_ACC);
      if(dcd_current == BP_ACCESS)
        BPM_PRINT_WRITE(bip_print_fun, bip_strings[v][bip_access(BP_ACCESS)]);
      else BPM_PRINT_WRITE(bip_print_fun, bip_strings[v]);
    } else if(dcd_current == BP_STRING) {
      bip_read_string(bip_string);
      BPM_PRINT_WRITE(bip_print_fun, bip_string);
      BP_EMPTY_STRING;
    } else if(dcd_current == BP_STR_ADDR) {
      v = bip_var_factor();
      if(bip_return_type == BP_ACCESS) {
        if(is_char) BPM_PRINT_WRITE(bip_print_fun, (char)v);
        else BPM_PRINT_WRITE(bip_print_fun, v);
      } else BPM_PRINT_WRITE(bip_print_fun, bip_strings[v]);
    } else if(dcd_current == BP_RESTART) {
      BPM_PRINT_CLEAR;
      DCD_NEXT;
    } else {
      v = bip_relation();
      if(bip_return_type == BP_STR_ADDR)
        BPM_PRINT_WRITE(bip_print_fun, bip_strings[v]);
      else if(is_char) BPM_PRINT_WRITE(bip_print_fun, (char)v);
      else BPM_PRINT_WRITE(bip_print_fun, v);
    }
  } while(dcd_current == BP_COMMA);
};

/* BLOCK CALL -------------------------------------------------------------- */
void bip_skip_block() {
  uint16_t id = 1;
  do {
    if(dcd_current == BP_IF) id++;
    if(dcd_current == BP_ENDIF) id--;
    if((dcd_current == BP_ELSE) && (id == 1)) return;
    if(dcd_current == BP_ENDOFINPUT) bip_error(dcd_ptr, BP_ERROR_BLOCK);
    DCD_NEXT;
  } while(id >= 1);
}

/* IF ---------------------------------------------------------------------- */
void bip_if_call() {
  if((BP_VAR_T)(bip_relation()) > 0) return;
  bip_skip_block();
  if(dcd_current == BP_ELSE) DCD_NEXT;
};

/* ASSIGN VALUE TO VARIABLE ------------------------------------------------ */
void bip_variable_assignment_call() {
  if(dcd_current == BP_VAR_ACC) {
    BP_VAR_T v = bip_access(BP_VAR_ACC);
    BP_SET_VARIABLE(v, bip_relation());
  } else {
    DCD_NEXT;
    uint8_t vi = *(dcd_ptr - 1) - BP_OFFSET;
    BP_SET_VARIABLE(vi, bip_relation());
  }
};

/* ASSIGN VALUE TO STRING -------------------------------------------------- */
void bip_string_assignment_call() {
  int ci = BP_STRING_MAX, si;
  bool str_acc = (dcd_current == BP_STR_ACC);
  DCD_NEXT;
  if(str_acc) {
    si = bip_expression();
    BP_EXPECT(BP_ACCESS_END);
  } else si = *(dcd_ptr - 1) - BP_OFFSET;
  if(dcd_current == BP_ACCESS) ci = bip_access(BP_ACCESS);
  if(ci == BP_STRING_MAX) {
    if(dcd_current == BP_STRING) bip_read_string(bip_strings[si]);
    else if(bip_ignore(BP_STR_ADDR)) {
      ci = *(dcd_ptr - 1) - BP_OFFSET;
      for(uint16_t i = 0; i < sizeof(bip_strings[ci]); i++)
        bip_strings[si][i] = bip_strings[ci][i];
      DCD_NEXT;
    }
  } else {
    if(bip_ignore(BP_STRING)) {
      bip_strings[si][ci] = (char)(*(dcd_ptr - 2));
    } else bip_strings[si][ci] = (uint8_t)bip_expression();
  }
};

/* GENERAL PURPOSE MEMORY ASSIGNMENT --------------------------------------- */
void bip_mem_assignment_call() {
  BP_VAR_T i = bip_access(BP_MEM_ACC);
  if((i >= 0) && (i < BP_MEM_SIZE)) bip_memory[i] = bip_expression();
  else bip_error(dcd_ptr, BP_ERROR_MEM_SET);
};

/* RESULT ------------------------------------------------------------------ */
void bip_result_set_call() {
  if(bip_fn_id > 0) bip_functions[bip_fn_id - 1].result = bip_relation();
  else bip_error(dcd_ptr, BP_ERROR_RESULT_SET);
};

BP_VAR_T bip_result_get_call() {
  if(bip_fn_id > 0)
    return bip_functions[bip_fn_id - 1].result;
  else bip_error(dcd_ptr, BP_ERROR_RESULT_GET);
  return 0;
};

/* RETURN ------------------------------------------------------------------ */
BP_VAR_T bip_return_call() {
  BP_VAR_T rel = 0;
  DCD_NEXT;
  if(bip_fn_id > 0) {
    rel = bip_relation();
    bip_fn_id--;
    for(int i = 0; i < BP_PARAMS; i++)
      if(bip_functions[bip_fn_id].params[i].id != BP_VARIABLES) {
        BP_SET_VARIABLE( // Set back global bip_variables;
          bip_functions[bip_fn_id].params[i].id,
          bip_functions[bip_fn_id].params[i].value
        );
        bip_functions[bip_fn_id].params[i].id = BP_VARIABLES;
        bip_functions[bip_fn_id].params[i].value = 0;
        bip_functions[bip_fn_id].result = 0;
      } else break;
    DCD_GOTO(bip_functions[bip_fn_id].address);
    bip_fw_id = bip_functions[bip_fn_id].cid;
    return rel;
  } else {
    bip_error(dcd_ptr, BP_ERROR_RETURN);
    return 0;
  }
};

/* FUNCTION ---------------------------------------------------------------- */
BP_VAR_T bip_function_call() {
  bip_functions[bip_fn_id].cid = bip_fw_id;
  BP_EXPECT(BP_FUNCTION);
  uint8_t i = 0, f = *(dcd_ptr - 1) - BP_OFFSET, v = BP_VARIABLES;
  if(*dcd_ptr != BP_R_RPARENT) {
    bool r = true;
    do {
      if(bip_definitions[f].params[i] == BP_PARAMS) break;
      v = bip_definitions[f].params[i] - BP_OFFSET;
      bip_functions[bip_fn_id].params[i].id = v;
      if(i < BP_PARAMS) {
        // Stash global variabile value
        BP_GET_VARIABLE(v, bip_functions[bip_fn_id].params[i].value);
        // Set global variable with parameter value
        if(r) BP_SET_VARIABLE(v, bip_relation());
      } else {
        bip_error(dcd_ptr, BP_ERROR_FUNCTION_PARAMS);
        return 0;
      }
      DCD_IGNORE(BP_COMMA, r);
    } while((++i < BP_PARAMS));
  }
  if(bip_fn_id < BP_FUN_DEPTH) {
    bip_functions[bip_fn_id++].address = dcd_ptr;
    DCD_GOTO(bip_definitions[f].address);
    while(dcd_current != BP_RETURN) bip_statement();
    return bip_return_call();
  } else {
    bip_error(dcd_ptr, BP_ERROR_FUNCTION_CALL);
    return 0;
  }
};

/* CONTINUE ---------------------------------------------------------------- */
void bip_continue_call() {
  int16_t id = bip_fw_id;
  while(bip_fw_id <= id) {
    if(dcd_current == BP_NEXT) id--;
    if(dcd_current == BP_WHILE || dcd_current == BP_FOR) id++;
    if(bip_fw_id <= id) DCD_NEXT;
  }
};

/* BREAK ------------------------------------------------------------------- */
void bip_break_call() {
  bip_continue_call();
  DCD_NEXT;
  if(bip_cycles[bip_fw_id - 1].var_id != BP_VARIABLES)
    BP_SET_VARIABLE(
      bip_cycles[bip_fw_id - 1].var_id, bip_cycles[bip_fw_id - 1].var
    );
  bip_cycles[--bip_fw_id].var_id = BP_VARIABLES;
};

/* CYCLE ------------------------------------------------------------------- */
void bip_for_call() {
  uint8_t vi = *(dcd_ptr - 1) - BP_OFFSET;
  BP_VAR_T l, v;
  if(bip_fw_id < BP_CYCLE_DEPTH) {
    v = bip_expression();
    BP_EXPECT(BP_COMMA);
    if((l = bip_expression()) == v) {
      bip_continue_call();
      DCD_NEXT;
      return;
    } // Move global variable in for buffer
    BP_GET_VARIABLE(vi, bip_cycles[++bip_fw_id - 1].var);
    BP_SET_VARIABLE(vi, v); // Save for local variable in global buffer
    bip_cycles[bip_fw_id - 1].to = l + 1;
    bip_cycles[bip_fw_id - 1].var_id = vi;
    if(bip_ignore(BP_COMMA)) bip_cycles[bip_fw_id - 1].step = bip_relation();
    else bip_cycles[bip_fw_id - 1].step = (v < l) ? 1 : -1;
    bip_cycles[bip_fw_id - 1].address = dcd_ptr;
  } else bip_error_fun(dcd_ptr, BP_ERROR_FOR_MAX);
};

/* LABEL ------------------------------------------------------------------- */
void bip_label_call() {
  DCD_NEXT;
  int id = *(dcd_ptr - 1) - BP_OFFSET;
  BP_SET_VARIABLE(id, dcd_ptr - bip_program_start);
};

/* NEXT -------------------------------------------------------------------- */
void bip_next_call() {
  if(bip_fw_id) {
    if(bip_cycles[bip_fw_id - 1].var_id == BP_VARIABLES) {
      char *end = dcd_ptr;
      DCD_GOTO(bip_cycles[bip_fw_id - 1].address);
      if(bip_relation() <= 0) {
        DCD_GOTO(end);
        bip_fw_id--;
      }
    } else {
      uint8_t vi = bip_cycles[bip_fw_id - 1].var_id;
      bip_variables[vi] += bip_cycles[bip_fw_id - 1].step;
      if(bip_variables[vi] != bip_cycles[bip_fw_id - 1].to) {
        DCD_GOTO(bip_cycles[bip_fw_id - 1].address);
      } else { // Set back global variable and reset cycle variable buffer
        if(vi != BP_VARIABLES)
          BP_SET_VARIABLE(vi, bip_cycles[bip_fw_id - 1].var);
        bip_cycles[--bip_fw_id].var_id = BP_VARIABLES;
      }
    }
  } else bip_error(dcd_ptr, BP_ERROR_NEXT);
};

/* WHILE ------------------------------------------------------------------- */
void bip_while_call() {
  char *start = dcd_ptr;
  if(bip_relation() > 0) {
    if(bip_fw_id < BP_CYCLE_DEPTH) bip_cycles[bip_fw_id++].address = start;
    else bip_error(dcd_ptr, BP_ERROR_WHILE_MAX);
  } else bip_break_call();
};

/* INPUT/OUTPUT FUNCTIONS -------------------------------------------------- */
BP_VAR_T bip_adc_call() {
  DCD_NEXT;
  char c = dcd_current;
  if(c == BP_READ) {
    DCD_NEXT;
    BP_VAR_T p = bip_expression();
    return BPM_AREAD(p);
  } return 0;
};

BP_VAR_T bip_io_get_call() {
  DCD_NEXT;
  BP_EXPECT(BP_READ);
  BP_VAR_T v = bip_expression();
  return BPM_IO_READ(v);
};

void bip_io_set_call() {
  char c = dcd_current;
  DCD_NEXT;
  if(dcd_current == BP_WRITE) {
    BP_SYS_EXP_2(BPM_IO_WRITE);
  } else if(dcd_current == BP_OPEN) {
    BP_SYS_EXP_2(BPM_IO_MODE);
  }
};

/* CURSOR ------------------------------------------------------------------ */
void bip_cursor_call() {
  BP_VAR_T r = bip_expression();
  BP_EXPECT(BP_COMMA);
  BPM_PRINT_CURSOR(r, bip_expression());
};

/* FILE SYSTEM FUNCTIONS --------------------------------------------------- */
void bip_file_set_call() {
  DCD_NEXT;
  BP_VAR_T r;
  if(dcd_current == BP_CLOSE) {
    BP_SYS_REL_BOUNDS(r, BP_FILES_MAX, BP_ERROR_FILE_MAX);
    if(!bip_ended) {
      BPM_FILE_CLOSE(bip_files[r].file);
      bip_files[r].free = true;
    }
  } else {
    BP_SYS_REL_BOUNDS(r, BP_FILES_MAX, BP_ERROR_FILE_MAX);
    if(!bip_ended) {
      BP_EXPECT(BP_COMMA);
      BP_SYS_REL_1(BPM_FILE_WRITE, bip_files[r].file);
    }
  }
};

BP_VAR_T bip_file_get_call() {
  DCD_NEXT;
  if(dcd_current == BP_OPEN) {
    DCD_NEXT;
    BP_VAR_T f = bip_get_file_id();
    if(f == BP_FILES_MAX) return BP_FILES_MAX;
    if(dcd_current == BP_STRING) {
      bip_read_string(bip_string);
      BP_EXPECT(BP_COMMA);
      BP_VAR_T v = bip_relation();
      BPM_FILE_OPEN(bip_files[f].file, bip_string, v);
      BP_EMPTY_STRING;
    } else if(bip_ignore(BP_STR_ADDR)) {
      uint8_t id = *(dcd_ptr - 1) - BP_OFFSET;
      BP_EXPECT(BP_COMMA);
      BP_VAR_T v = bip_relation();
      BPM_FILE_OPEN(bip_files[f].file, bip_strings[id], v);
    }
    if(bip_files[f].file == NULL) bip_error(dcd_ptr, BP_ERROR_FILE_OPEN);
    return f;
  } else if (dcd_current == BP_READ) {
    BP_VAR_T r;
    BP_SYS_REL_BOUNDS(r, BP_FILES_MAX, BP_ERROR_FILE_MAX);
    if(!bip_ended) return BPM_FILE_READ(bip_files[r].file);
  } return 0;
};

/* SERIAL SYSTEM FUNCTIONS ------------------------------------------------- */
BP_VAR_T bip_serial_call() {
  DCD_NEXT;
  char c = dcd_current;
  BP_VAR_T r;
  DCD_NEXT;
  if(c == BP_WRITE) {
    BP_SYS_REL_1(BPM_SERIAL_WRITE, bip_serial_fun);
  } else if(c == BP_READ) {
    BPM_SERIAL_READ(bip_serial_fun);
    DCD_NEXT;
  }
};

/* STRING LENGTH CALL ------------------------------------------------------ */
BP_VAR_T bip_sizeof_call() {
  DCD_NEXT;
  if(bip_ignore(BP_STR_ADDR)) {
    BP_VAR_T l = strlen(bip_strings[*(dcd_ptr - 1) - BP_OFFSET]);
    return l;
  } else if(dcd_current == BP_STR_ACC)
    return strlen(bip_strings[bip_access(BP_STR_ACC)]);
  else if(bip_ignore(BP_VAR_ADDR)) return sizeof(BP_VAR_T);
  return 0;
};

/* RANDOM CALL (Expects one parameter: the exclusive maximum value) -------- */
BP_VAR_T bip_random_call() {
  BP_VAR_T a = bip_expression(), b = BPM_RANDOM(a);
  return b;
};

/* ATOL - LTOA ------------------------------------------------------------- */
BP_VAR_T bip_atol_call() {
  BP_VAR_T v = 0;
  BP_SYS_STR_1(BPM_ATOL, v);
  return v;
};

uint16_t bip_ltoa_call() {
  BP_VAR_T v = bip_relation(), s = 0;
  BP_EXPECT(BP_COMMA);
  DCD_NEXT;
  s = *(dcd_ptr - 1) - BP_OFFSET;
  if((s < 0) || (s >= BP_STRINGS)) bip_error(dcd_ptr, BP_ERROR_STRING_GET);
  else BPM_LTOA(v, bip_strings[s]);
  return s;
};

/* SYSTEM (Passes a :string or string literal to the environment) ---------- */
BP_VAR_T bip_system_call() {
  BP_VAR_T v = 0;
  BP_SYS_STR_1(BPM_SYSTEM, v);
  return v;
};

/* STATEMENTS: (print, if, return, for, while...) -------------------------- */
void bip_statement() {
  bip_return_type = 0;
  switch(dcd_current) {
    case BP_LABEL:      DCD_NEXT; bip_label_call(); return;
    case BP_SEMICOLON:  ; // Same as BP_ENDIF
    case BP_ENDIF:      DCD_NEXT; return;
    case BP_ELSE:       DCD_NEXT; return bip_skip_block();
    case BP_FUNCTION:   bip_function_call(); BP_EXPECT(BP_R_RPARENT);
                        return;
    case BP_VAR_ACC: ;  // assignment by reference
    case BP_VAR_ADDR:   return bip_variable_assignment_call();
    case BP_STR_ACC: ;  // assignment by reference
    case BP_STR_ADDR:   return bip_string_assignment_call();
    case BP_MEM_ACC:    return bip_mem_assignment_call();
    case BP_INCREMENT:  ; // same as decrement
    case BP_DECREMENT:  bip_var_factor();  return;
    case BP_IF:         DCD_NEXT; return bip_if_call();
    case BP_FOR:        DCD_NEXT; return bip_for_call();
    case BP_WHILE:      DCD_NEXT; return bip_while_call();
    case BP_NEXT:       DCD_NEXT; return bip_next_call();
    case BP_JUMP:       DCD_NEXT; return bip_jump_call();
    case BP_BREAK:      return bip_break_call();
    case BP_CONTINUE:   return bip_continue_call();
    case BP_FILE:       return bip_file_set_call();
    case BP_PRINT:      DCD_NEXT; return bip_print_call();
    case BP_IO:         DCD_NEXT; return bip_io_set_call();
    case BP_DELAY:      DCD_NEXT; BPM_DELAY(bip_expression()); return;
    case BP_CURSOR:     DCD_NEXT; return bip_cursor_call();
    case BP_LTOA:       DCD_NEXT; bip_ltoa_call(); return;
    case BP_RESTART:    return bip_restart_call();
    case BP_RESULT:     DCD_NEXT; return bip_result_set_call();
    case BP_END:        return bip_end_call();
    default: bip_error(dcd_ptr, BP_ERROR_STATEMENT);
  }
};
