
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
#include "BIPLAN_Decoder.h"

class BIPLAN_Interpreter {
  public:
  /* TYPES ----------------------------------------------------------------- */
  struct param_t { BP_VAR_TYPE value; uint8_t id = BP_VARIABLES; };
  struct fun_t { char *address; uint8_t cycle_id; param_t params[BP_PARAMS]; };
  struct def_t { char *address; uint16_t params[BP_PARAMS]; };

  struct cycle_type {
    char *address;
    BP_VAR_TYPE var = 0;
    uint8_t var_id = BP_VARIABLES;
    BP_VAR_TYPE step = 0;
    BP_VAR_TYPE to = 0;
  };

  /* BUFFERS --------------------------------------------------------------- */
  BP_VAR_TYPE       variables      [BP_VARIABLES];
  uint8_t           memory         [BP_MEM_SIZE];
  char              string         [BP_STRING_MAX_LENGTH];
  char              strings        [BP_STRINGS][BP_STRING_MAX_LENGTH];
  struct cycle_type cycles         [BP_CYCLE_DEPTH];
  struct fun_t      functions      [BP_FUN_DEPTH];
  struct def_t      definitions    [BP_MAX_FUNCTIONS];
  /* STATE ----------------------------------------------------------------- */
  char             *program_start  = NULL;
  uint8_t           cycle_id       = 0;
  uint8_t           fun_cycle_id   = 0;
  int               fun_id         = 0;
  bool              ended          = false;
  uint8_t           return_type    = 0;
  /* CALLBACKS ------------------------------------------------------------- */
  error_type        error_fun;
  BPM_PRINT_TYPE    print_fun;
  BPM_INPUT_TYPE    data_in_fun;
  BPM_SERIAL_TYPE   serial_fun;

  /* FINISHED -------------------------------------------------------------- */
  bool finished() { return ended || decoder_finished(); };

  /* RUN ------------------------------------------------------------------- */
  bool run() { statement(); return !ended;  };

  /* END PROGRAM ----------------------------------------------------------- */
  void end_call() { expect(BP_END); ended = true; };

  /* RESTART PROGRAM CALL -------------------------------------------------- */
  void restart_call() { set_default(); decoder_init(program_start); };

  /* ERROR ----------------------------------------------------------------- */
  void error(char *position, const char *string) {
    error_fun(position, string);
    ended = true;
  };

  /* INDEX LINES ----------------------------------------------------------- */
  void index_function_definitions(char* program) {
    uint16_t param, l = 0;
    while(decoder_get() != BP_ENDOFINPUT) {
      if(ignore(BP_FUN_DEF)) {
        param = 0;
        l = *(decoder_position() - 1) - BP_OFFSET;
        for(uint8_t i = 0; i < BP_PARAMS; i++)
          definitions[l].params[i] = BP_PARAMS;
        while(ignore(BP_L_RPARENT) || ignore(BP_COMMA)) {
          if(ignore(BP_ADDRESS)) {
            definitions[l].params[param++] = *(decoder_position() - 1);
          } if(*decoder_position() == BP_R_RPARENT) break;
        } definitions[l].address = decoder_position() + 1;
      } decoder_next();
    }
  };

  /* PROCESS LABEL STATEMENTS ---------------------------------------------- */
  void process_labels(char* program) {
    decoder_init(program);
    while(decoder_get() != BP_ENDOFINPUT) {
      if(decoder_get() == BP_LABEL) statement();
      else decoder_next();
    }
  };

  /* INITIALIZE INTERPRETER ------------------------------------------------ */

  BIPLAN_Interpreter() { set_default(); };

  void initialize(
    char *program,
    error_type error,
    BPM_PRINT_TYPE print,
    BPM_INPUT_TYPE data_input,
    BPM_SERIAL_TYPE s
  ) {
    program_start = program;
    set_default();
    process_labels(program);
    decoder_init(program);
    index_function_definitions(program);
    decoder_init(program);
    serial_fun = s;
    error_fun = error;
    print_fun = print;
    data_in_fun = data_input;
  };

  void set_default() {
    cycle_id = 0;
    fun_id = 0;
    ended = false;
    for(BP_VAR_TYPE i = 0; i < BP_MEM_SIZE; i++) memory[i] = 0;
    for(BP_VAR_TYPE i = 0; i < BP_VARIABLES; i++) variables[i] = 0;
    for(BP_VAR_TYPE i = 0; i < BP_STRINGS; i++)
      for(BP_VAR_TYPE c = 0; c < BP_STRING_MAX_LENGTH; c++) strings[i][c] = 0;
    for(BP_VAR_TYPE i = 0; i < BP_STRING_MAX_LENGTH; i++) string[i] = 0;
  };

  /* EXPECT A CERTAIN CODE, OTHERWISE THROW ERROR -------------------------- */
  void expect(uint8_t c) {
    if(c != decoder_get()) error(decoder_position(), BP_ERROR_SYMBOL);
    else decoder_next();
  };

  /* IGNORE A CERTAIN CODE ------------------------------------------------- */
  bool ignore(uint8_t c) {
    if((c = (c == decoder_get()))) decoder_next();
    return c;
  };

  /* GET VARIABLE ---------------------------------------------------------- */
  BP_VAR_TYPE get_variable(int n) {
    if(n >= 0 && n <= BP_VARIABLES) return variables[n];
    error(decoder_position(), BP_ERROR_VARIABLE_GET);
    return 0;
  };

  /* SET VARIABLE ---------------------------------------------------------- */
  void set_variable(int n, BP_VAR_TYPE v) {
    if(n >= 0 && n <= BP_VARIABLES) variables[n] = v;
    else error(decoder_position(), BP_ERROR_VARIABLE_SET);
  };

  /* UNARY OPERATOR -------------------------------------------------------- */
  int8_t unary() {
    int8_t u = 0;
    while(decoder_get() == BP_INCREMENT || decoder_get() == BP_DECREMENT) {
      if(decoder_get() == BP_INCREMENT) u++; else u--;
      decoder_next();
    } return u;
  };

  /* NUMERIC VARIABLE: 1234 -------------------------------------------------*/
  BP_VAR_TYPE var_factor() {
    BP_VAR_TYPE v;
    int8_t pre = unary(), post = 0, id = BP_VARIABLES;
    bool index = ignore(BP_INDEX);
    uint8_t type = decoder_get();
    decoder_next();
    id = *(decoder_position() - 1) - BP_OFFSET;
    if(index && ((type == BP_ADDRESS) || (type == BP_S_ADDRESS)))
      return id + pre;
    if(type == BP_ADDRESS) {
      v = get_variable(id);
      if(decoder_get() == BP_INCREMENT || decoder_get() == BP_DECREMENT)
        post = unary();
      if((pre != 0) || (post != 0)) set_variable(id, v + pre + post);
    } else if((type == BP_S_ADDRESS) && (decoder_get() == BP_ACCESS)) {
      v = strings[id][access(BP_ACCESS)];
      return_type = BP_ACCESS;
    } else {
      return_type = BP_S_ADDRESS;
      v = id;
    }
    return v + pre;
  };

  /* ACCESS MEMORY VIA INDEX [ ] ------------------------------------------ */

  BP_VAR_TYPE access(BP_VAR_TYPE v) {
    expect(v);
    v = relation();
    expect(BP_ACCESS_END);
    return v;
  };

  /* FACTOR: (n) ---------------------------------------------------------- */
  BP_VAR_TYPE factor() {
    BP_VAR_TYPE v = 0;
    bool bitwise_not = ignore(BP_BITWISE_NOT), minus = ignore(BP_MINUS);
    switch(decoder_get()) {
      case BP_VAR_ACCESS: v = variables[access(BP_VAR_ACCESS)]; break;
      case BP_STR_ACCESS:
        v = access(BP_STR_ACCESS);
        if(decoder_get() == BP_ACCESS) v = strings[v][access(BP_ACCESS)];
        break;
      case BP_MEM_ACCESS: v = memory[access(BP_MEM_ACCESS)]; break;
      case BP_NUMBER: v = BPM_ATOL(decoder_position()); expect(BP_NUMBER); break;
      case BP_DREAD: decoder_next(); return BPM_IO_READ(expression());
      case BP_MILLIS: decoder_next(); v = (BPM_MILLIS() % BP_VAR_MAX); break;
      case BP_AGET: decoder_next(); v = BPM_AREAD(expression()); break;
      case BP_RND: decoder_next();  v = random_call(); break;
      case BP_SQRT: decoder_next(); v = sqrt(expression()); break;
      case BP_FUNCTION: v = function_call(); decoder_next(); break;
      case BP_SERIAL_RX:
        v = BPM_SERIAL_READ(serial_fun); decoder_next(); break;
      case BP_INPUT: v = BPM_INPUT(data_in_fun); decoder_next(); break;
      case BP_L_RPARENT:
        decoder_next(); v = relation(); expect(BP_R_RPARENT); break;
      case BP_SIZEOF: v = sizeof_call(); break;
      case BP_ATOL: v = atol_call(); break;
      case BP_NUMERIC: decoder_next(); v = relation(); v = (v >= 48) && (v <= 57); break;
      default: v = var_factor();
    } v = (minus) ? -v : v;
    return (bitwise_not) ? ~v : v;
  };

  /* TERM: *, /, % ----------------------------------------------------------*/
  BP_VAR_TYPE term() {
    BP_VAR_TYPE f1 = 0, f2 = 0;
    uint8_t operation;
    f1 = factor();
    operation = decoder_get();
    while(operation == BP_MULT || operation == BP_DIV || operation == BP_MOD) {
      decoder_next();
      f2 = factor();
      switch(operation) {
        case BP_MULT: f1 = f1 * f2; break;
        case BP_DIV:  f1 = f1 / f2; break;
        case BP_MOD:  f1 = f1 % f2; break;
      } operation = decoder_get();
    } return f1;
  };

  /* EXPRESSION +, -, &, | --------------------------------------------------*/
  BP_VAR_TYPE expression() {
    BP_VAR_TYPE t1 = 0, t2 = 0;
    t1 = term();
    uint8_t operation = decoder_get();
    while(
      operation == BP_PLUS || operation == BP_MINUS || operation == BP_AND ||
      operation == BP_OR || operation == BP_XOR || operation == BP_L_SHIFT ||
      operation == BP_R_SHIFT
    ) {
      decoder_next();
      t2 = term();
      switch(operation) {
        case BP_PLUS:    t1 = t1 + t2;  break;
        case BP_MINUS:   t1 = t1 - t2;  break;
        case BP_AND:     t1 = t1 & t2;  break;
        case BP_OR:      t1 = t1 | t2;  break;
        case BP_XOR:     t1 = t1 ^ t2;  break;
        case BP_L_SHIFT: t1 = t1 << t2; break;
        case BP_R_SHIFT: t1 = t1 >> t2; break;
      } operation = decoder_get();
    } return t1;
  };

  /* RELATION <, >, = ------------------------------------------------------ */
  BP_VAR_TYPE relation() {
    BP_VAR_TYPE r1 = expression(), r2 = 0;
    uint8_t operation = decoder_get();
    while(
      operation == BP_EQ || operation == BP_NOT_EQ || operation == BP_LTOEQ ||
      operation == BP_GTOEQ || operation == BP_LT || operation == BP_GT ||
      operation == BP_LOGIC_OR || operation == BP_LOGIC_AND
    ) {
      decoder_next();
      r2 = expression();
      switch(operation) {
        case BP_NOT_EQ:    r1 = r1 != r2; break;
        case BP_EQ:        r1 = r1 == r2; break;
        case BP_GTOEQ:     r1 = r1 >= r2; break;
        case BP_LTOEQ:     r1 = r1 <= r2; break;
        case BP_LOGIC_OR:  r1 = r1 || r2; break;
        case BP_LOGIC_AND: r1 = r1 && r2; break;
        case BP_LT:        r1 = r1 <  r2; break;
        case BP_GT:        r1 = r1 >  r2; break;
      } operation = decoder_get();
    } return r1;
  };

  /* JUMP ------------------------------------------------------------------ */
  void jump_call() {
    decoder_next();
    decoder_goto(program_start + relation());
  }

  /* PRINT ----------------------------------------------------------------- */
  void print_call() {
    do {
      BP_VAR_TYPE v = 0;
      ignore(BP_COMMA);
      bool is_char = ignore(BP_CHAR);
      if(decoder_get() == BP_STR_ACCESS) {
        BPM_PRINT_WRITE(print_fun, strings[access(BP_STR_ACCESS)]);
      } else if(decoder_get() == BP_STRING) {
        decoder_string(string, sizeof(string));
        BPM_PRINT_WRITE(print_fun, string);
        decoder_next();
      } else if(decoder_get() == BP_S_ADDRESS) {
        v = var_factor();
        if(return_type == BP_ACCESS) {
          if(is_char) BPM_PRINT_WRITE(print_fun, (char)v);
          else BPM_PRINT_WRITE(print_fun, v);
        } else BPM_PRINT_WRITE(print_fun, strings[v]);
      } else {
        v = relation();
        if(return_type == BP_S_ADDRESS)
          BPM_PRINT_WRITE(print_fun, strings[v]);
        else if(is_char) BPM_PRINT_WRITE(print_fun, (char)v);
        else BPM_PRINT_WRITE(print_fun, v);
      }
    } while(decoder_get() == BP_COMMA);
  };

  /* BLOCK CALL ------------------------------------------------------------ */
  void skip_block() {
    uint16_t id = 1;
    do {
      if(decoder_get() == BP_IF) id++;
      if(decoder_get() == BP_ENDIF) id--;
      if((decoder_get() == BP_ELSE) && (id == 1)) return;
      if(decoder_get() == BP_ENDOFINPUT)
        error(decoder_position(), BP_ERROR_BLOCK);
      decoder_next();
    } while(id >= 1);
  }

  /* IF -------------------------------------------------------------------- */
  void if_call() {
    decoder_next();
    if((BP_VAR_TYPE)(relation()) > 0) return;
    skip_block();
    ignore(BP_ELSE);
  };

  /* ASSIGN VALUE TO VARIABLE ---------------------------------------------- */
  void variable_assignment_call() {
    if(decoder_get() == BP_VAR_ACCESS) {
      BP_VAR_TYPE v = access(BP_VAR_ACCESS);
      return set_variable(v, relation());
    } else {
      decoder_next();
      int vi = *(decoder_position() - 1) - BP_OFFSET;
      set_variable(vi, relation());
    }
  };

  /* ASSIGN VALUE TO STRING ----------------------------------------------- */
  void string_assignment_call() {
    int ci = BP_STRING_MAX_LENGTH, si;
    bool str_acc = (decoder_get() == BP_STR_ACCESS);
    decoder_next();
    if(str_acc) {
      si = expression();
      expect(BP_ACCESS_END);
    } else si = *(decoder_position() - 1) - BP_OFFSET;
    if(decoder_get() == BP_ACCESS) ci = access(BP_ACCESS);
    if(ci == BP_STRING_MAX_LENGTH) {
      if(decoder_get() == BP_STRING) {
        decoder_string(strings[si], sizeof(strings[si]));
        expect(BP_STRING);
      } else if(ignore(BP_S_ADDRESS)) {
        ci = *(decoder_position() - 1) - BP_OFFSET;
        for(uint16_t i = 0; i < sizeof(strings[ci]); i++)
          strings[si][i] = strings[ci][i];
        decoder_next();
      }
    } else {
      if(ignore(BP_STRING)) {
        strings[si][ci] = (char)(*(decoder_position() - 2));
      } else strings[si][ci] = (uint8_t)expression();
    }
  };

  /* GENERAL PURPOSE MEMORY ASSIGNMENT ------------------------------------ */
  void mem_assignment_call() {
    BP_VAR_TYPE i = access(BP_MEM_ACCESS);
    if((i >= 0) && (i < BP_MEM_SIZE)) memory[i] = expression();
    else error(decoder_position(), BP_ERROR_MEM_SET);
  };

  /* RETURN --------------------------------------------------------------- */
  BP_VAR_TYPE return_call() {
    BP_VAR_TYPE rel = 0;
    decoder_next();
    if(fun_id > 0) {
      if(decoder_get() != BP_SEMICOLON) rel = relation();
      fun_id--;
      for(int i = 0; i < BP_PARAMS; i++)
        if(functions[fun_id].params[i].id != BP_VARIABLES) {
          set_variable( // Set back global variables;
            functions[fun_id].params[i].id,
            functions[fun_id].params[i].value
          );
          functions[fun_id].params[i].id = BP_VARIABLES;
          functions[fun_id].params[i].value = 0;
        }
      decoder_goto(functions[fun_id].address);
      cycle_id = functions[fun_id].cycle_id;
      return rel;
    } else {
      error(decoder_position(), BP_ERROR_RETURN);
      return 0;
    }
  };

  /* FUNCTION -------------------------------------------------------------- */
  BP_VAR_TYPE function_call() {
    functions[fun_id].cycle_id = cycle_id;
    int16_t i = 0;
    expect(BP_FUNCTION);
    uint16_t f = *(decoder_position() - 1) - BP_OFFSET, v = BP_VARIABLES;
    if((*(decoder_position() + 1) == BP_R_RPARENT))
      expect(BP_L_RPARENT); // If call with no params
    else if(ignore(BP_L_RPARENT))
      do {
        v = definitions[f].params[i] - BP_OFFSET;
        functions[fun_id].params[i].id = v;
        if(v != BP_VARIABLES) {
          functions[fun_id].params[i].value = get_variable(v);
          set_variable(v, relation()); // Set the value of local variable
        } else relation(); // ignore unexpected parameter
      } while((++i < BP_PARAMS) && ignore(BP_COMMA));
    if(fun_id < BP_FUN_DEPTH) {
      functions[fun_id++].address = decoder_position();
      decoder_goto(definitions[f].address);
      while(decoder_get() != BP_RETURN) statement();
      return return_call();
    } else {
      error(decoder_position(), BP_ERROR_FUNCTION_CALL);
      return 0;
    }
  };

  /* CONTINUE -------------------------------------------------------------- */
  void continue_call() {
    int16_t id = cycle_id;
    while(cycle_id <= id) {
      if(decoder_get() == BP_NEXT) id--;
      if(decoder_get() == BP_WHILE || decoder_get() == BP_FOR) id++;
      if(cycle_id <= id) decoder_next();
    }
  };

  /* BREAK ----------------------------------------------------------------- */
  void break_call() {
    continue_call();
    decoder_next();
    if(cycles[cycle_id - 1].var_id != BP_VARIABLES)
      set_variable(cycles[cycle_id - 1].var_id, cycles[cycle_id - 1].var);
    cycles[--cycle_id].var_id = BP_VARIABLES;
  };

  /* CYCLE ----------------------------------------------------------------- */
  void for_call() {
    decoder_next();
    expect(BP_ADDRESS);
    uint8_t vi = *(decoder_position() - 1) - BP_OFFSET;
    BP_VAR_TYPE l, v;
    if(cycle_id < BP_CYCLE_DEPTH) {
      v = expression();
      expect(BP_COMMA);
      if((l = expression()) == v) {
        continue_call();
        return decoder_next();
      }
      set_variable(vi, v);
      cycles[++cycle_id - 1].to = l + 1;
      cycles[cycle_id - 1].var = get_variable(vi);
      cycles[cycle_id - 1].var_id = vi;
      if(ignore(BP_COMMA)) cycles[cycle_id - 1].step = relation();
      else cycles[cycle_id - 1].step = (v < l) ? 1 : -1;
      cycles[cycle_id - 1].address = decoder_position();
    } else error_fun(decoder_position(), BP_ERROR_CYCLE_MAX);
  };

  /* LABEL ----------------------------------------------------------------- */
  void label_call() {
    decoder_next();
    decoder_next();
    int id = *(decoder_position() - 1) - BP_OFFSET;
    set_variable(id, decoder_position() - program_start);
  };

  /* NEXT ------------------------------------------------------------------ */
  void next_call() {
    decoder_next();
    if(cycle_id) {
      if(cycles[cycle_id - 1].var_id == BP_VARIABLES) {
        char *end = decoder_position();
        decoder_goto(cycles[cycle_id - 1].address);
        if(relation() <= 0) {
          decoder_goto(end);
          cycle_id--;
        }
      } else {
        uint8_t vi = cycles[cycle_id - 1].var_id;
        variables[vi] += cycles[cycle_id - 1].step;
        if(variables[vi] != cycles[cycle_id - 1].to)
          decoder_goto(cycles[cycle_id - 1].address);
        else { // Set back global variable and reset cycle variable buffer
          if(vi != BP_VARIABLES) set_variable(vi, cycles[cycle_id - 1].var);
          cycles[--cycle_id].var_id = BP_VARIABLES;
        }
      }
    } else error(decoder_position(), BP_ERROR_CYCLE_NEXT);
  };

  /* WHILE ----------------------------------------------------------------- */
  void while_call() {
    char *start = decoder_position();
    if(relation() > 0) {
      if(cycle_id < BP_CYCLE_DEPTH) cycles[cycle_id++].address = start;
      else error(decoder_position(), BP_ERROR_WHILE_MAX);
    } else break_call();
  };

  /* DIGITAL WRITE --------------------------------------------------------- */
  void digitalWrite_call() {
    BP_VAR_TYPE pin = expression();
    expect(BP_COMMA);
    BPM_IO_WRITE(pin, expression());
  };

  /* PINMODE --------------------------------------------------------------- */
  void pinMode_call() {
    BP_VAR_TYPE pin = expression();
    expect(BP_COMMA);
    BPM_IO_MODE(pin, expression());
  }

  /* RANDOM CALL (min optional, max optional) ------------------------------ */
  BP_VAR_TYPE random_call() {
    BP_VAR_TYPE a = expression(), b;
    b = BPM_RANDOM(a);
    return b;
  };

  /* SERIAL TX CALL -------------------------------------------------------- */
  void serial_tx_call() {
    if(decoder_get() == BP_STRING) {
      decoder_string(string, sizeof(string));
      for(uint16_t i = 0; i < BP_STRING_MAX_LENGTH; i++)
        BPM_SERIAL_WRITE(serial_fun, string[i]);
      decoder_next();
    } else if(ignore(BP_S_ADDRESS)) {
      uint8_t id = *(decoder_position() - 1) - BP_OFFSET;
      for(uint16_t i = 0; i < sizeof(strings[id]); i++)
        BPM_SERIAL_WRITE(serial_fun, strings[id][i]);
    } else {
      BP_VAR_TYPE r = relation();
      BPM_SERIAL_WRITE(serial_fun, r);
    }
  };

  /* STRING LENGTH CALL ---------------------------------------------------- */
  BP_VAR_TYPE sizeof_call() {
    decoder_next();
    if(ignore(BP_S_ADDRESS)) {
      BP_VAR_TYPE l =
        strlen(strings[*(decoder_position() - 1) - BP_OFFSET]);
      return l;
    } else if(ignore(BP_ADDRESS)) return sizeof(BP_VAR_TYPE);
    return 0;
  };

  /* ATOL - CONVERTS STRINGS TO NUMBER ------------------------------------ */
  BP_VAR_TYPE atol_call() {
    BP_VAR_TYPE v = 0;
    decoder_next();
    if(ignore(BP_ADDRESS)) {
      uint8_t vi = *(decoder_position() - 1) - BP_OFFSET;
      v = get_variable(vi) - 48;
    } else if(ignore(BP_S_ADDRESS)) {
      v = BPM_ATOL(strings[*(decoder_position() - 1) - BP_OFFSET]);
    } else if(decoder_get() == BP_STRING) {
      decoder_string(string, sizeof(string));
      expect(BP_STRING);
      v = BPM_ATOL(string);
    }
    return v;
  };

  /* STATEMENTS: (print, if, return, for, while...) ------------------------ */
  void statement() {
    return_type = 0;
    switch(decoder_get()) {
      case BP_LABEL:      label_call(); return;
      case BP_SEMICOLON:  ; // Same as BP_ENDIF
      case BP_ENDIF:      decoder_next(); return;
      case BP_FUNCTION:   function_call(); expect(BP_R_RPARENT);
                          return;
      case BP_VAR_ACCESS: ; // assignment by reference
      case BP_ADDRESS:    return variable_assignment_call();
      case BP_STR_ACCESS: ; // assignment by reference
      case BP_S_ADDRESS:  return string_assignment_call();
      case BP_MEM_ACCESS: return mem_assignment_call();
      case BP_INCREMENT:  var_factor();  return;
      case BP_DECREMENT:  var_factor();  return;
      case BP_RETURN:     return_call(); return;
      case BP_IF:         return if_call();
      case BP_ELSE:       decoder_next(); return skip_block();
      case BP_FOR:        return for_call();
      case BP_WHILE:      decoder_next(); return while_call();
      case BP_NEXT:       return next_call();
      case BP_JUMP:       return jump_call();
      case BP_BREAK:      return break_call();
      case BP_CONTINUE:   return continue_call();
      case BP_PRINT:      decoder_next(); return print_call();
      case BP_END:        return end_call();
      case BP_DWRITE:     decoder_next(); return digitalWrite_call();
      case BP_PINMODE:    decoder_next(); return pinMode_call();
      case BP_DELAY:      decoder_next(); BPM_DELAY(expression()); return;
      case BP_RESTART:    return restart_call();
      case BP_SERIAL_TX:  decoder_next(); return serial_tx_call();
      default: error(decoder_position(), BP_ERROR_STATEMENT);
    }
  };
};
