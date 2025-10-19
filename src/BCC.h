
/* BIPLAN CR.1 (Byte coded Interpreted Programming Language)

      _____              _________________________
     |   | |            |_________________________|
     |   | |_______________||__________   \___||_________ |
   __|___|_|               ||          |__|   ||     |   ||
  /________|_______________||_________________||__   |   |D
    (O)                 |_________________________|__|___/|
                                           \ /            |
                                           (O)

  Giovanni Blu Mitolo 2017-2025 - gioscarab@gmail.com
  BCC (BIPLAN Compiler Collection) - BIPLAN to BIP compiler  */

#pragma once
#include "BIPLAN_Defines.h"

typedef void (*bcc_error_t)(uint16_t line, const char *p, const char *s);

/* Checks if the character is an acceptable numeric symbol ----------------- */
#define BCC_IS_NUM(C) (C >= '0' && C <= '9')

/* Checks if the character is an acceptable keyword symbol ----------------- */
#define BCC_IS_KEYWORD(C) ( \
  (C >= 'a' && C <= 'z') || (C >= 'A' && C <= 'Z') || \
  (C == '_') || (C >= '0' && C <= '9') )

/* Checks if the character is an acceptable capitalized keyword symbol ------*/
#define BCC_IS_CAP_KEYWORD(C) \
  ((C >= 'A' && C <= 'Z') || (C == '_') || (C >= '0' && C <= '9'))

/* Checks if the character passed is an acceptable address ----------------- */
#define BCC_IS_ADDR(C) ( \
  (C == BP_VAR_ADDR) || (C == BP_STR_ADDR) || (C == BP_FOR_ADDR) || \
  (C == BP_FOR) || (C == BP_FUNCTION) || (C == BP_FUN_DEF) )

/* Sets A to the next available address (avoiding reserved characters) ----- */
#define BCC_NEW_ADDR(A) do { A++; } while(BCC_IS_ADDR(A));

#define BCC_SUGAR(P) \
  (*P == BP_SPACE) || (*P == BP_CR) || (*P == BP_LF) || (*P == BP_TAB)

/* Ignores Space, tab, carriage return ------------------------------------- */
#define BCC_IGNORE_SUGAR(P) while(BCC_SUGAR(P)) P++;

class BCC {
private:
  bool fail = false;
  char var_id = BP_OFFSET, string_id = BP_OFFSET + BP_ARGS, fun_id = BP_OFFSET;
  char *stop;

  /* Function called in case of compilation error -------------------------- */
  void error(uint16_t line, const char *position, const char *string) {
    if(error_callback) error_callback(line, position, string);
    fail = true;
  };

  /* Determines the program line at a certain position --------------------- */
  uint16_t line(const char *prog, const char *pos) {
    if(!prog || !pos) error(0, NULL, BP_ERROR_PROGRAM_GET);
    if(fail) return 0;
    uint16_t i = 1;
    const char *p = prog;
    while((p && *p) && (p <= pos)) {
      if(!in_string(prog, p) && (*p == BP_LF)) i++;
      p++;
    } return i;
  }

  /* Checks consistency of syntax delimiters ------------------------------- */
  bool check_delimeter(const char *prog, char a, char b, bool ignore = 0) {
    if(!prog) error(0, NULL, BP_ERROR_PROGRAM_GET);
    if(fail) return false;
    uint16_t ia = 0, ib = 0;
    const char *p = prog;
    while(p && *p) {
      if(
        !in_string(prog, p) && 
        (ignore || p == prog || (p > prog && !BCC_IS_ADDR(*(p - 1))))
      ) {
        if((a == b) && (*p == a)) ia = !ia;
        else {
          if(*p == a) ia++;
          if(*p == b) ib++;
        }
      } p++;
    } return (ia == ib);
  };

  /* Finds the end of a program -------------------------------------------- */
  void find_end(char *prog) {
    if(!prog) error(0, NULL, BP_ERROR_PROGRAM_GET);
    if(fail) return;
    if(strlen(prog) >= BCC_MAX_PROGRAM_SIZE)
      return error(0, NULL, BP_ERROR_PROGRAM_LENGTH);
    for(stop = prog; *stop != 0; stop++);
  };

  /* Checks if a certain position in the program is within a string -------- */
  bool in_string(const char *prog, const char *pos) {
    if(!prog || !pos) error(0, NULL, BP_ERROR_PROGRAM_GET);
    if(fail) return false;
    bool in_str = false;
    const char *p = prog;
    while((p && *p) && (pos >= p)) {
      if(in_str && *p == BP_BACKSLASH) p += 2; // Jump escape + 1
      else { // Returns false if " is found outside of a string
        if((pos == p) && (*p == BP_STRING) && !in_str) return in_str;
        if(*p == BP_STRING) in_str = !in_str;
        p++;
      }
    } return in_str;
  };

  /* Remove a given symbol from the program -------------------------------- */
  void remove(char *prog, char v1, char v2 = 0, char v3 = 0, char v4 = 0) {
    if(!prog) error(0, NULL, BP_ERROR_PROGRAM_GET);
    if(fail) return;
    char *p = prog, *p2 = prog;
    bool in_str = false;
    while(p2 && *p2) {
      *p = *p2++;
      if(*p == BP_STRING) {
        if(!in_str || (in_str && p > prog && (*(p - 1) != BP_BACKSLASH))) 
          in_str = !in_str;
      }
      if((*p != v1) && (*p != v2) && (*p != v3) && (*p != v4)) p++;
      else if(in_str) p++;
    } *p = 0;
  };

  /* Remove comments from program ------------------------------------------ */
  void remove_comments(char *prog) {
    if(!prog) error(0, NULL, BP_ERROR_PROGRAM_GET);
    if(fail) return;
    char *p;
    while((p = strstr(prog, BP_COMMENT)))
      if(!in_string(prog, p)) 
        while((p && *p) && (*p != BP_CR) && (*p != BP_LF)) *(p++) = BP_SPACE;
  };

  /* Compiles character constants such as '@' into 64 (its decimal value) -- */
  void compile_char_constants(char *prog) {
    if(!prog) error(0, NULL, BP_ERROR_PROGRAM_GET);
    if(fail) return;
    char *p = prog, b[3] = {};
    while(p && *p) {
      if(!in_string(prog, p) && (*p == BP_SINGLE_QUOTE)) {
        if(*(p + 2) != BP_SINGLE_QUOTE) {
          error(line(prog, p), p, BP_ERROR_SINGLE_QUOTE);
          return;
        }
        BPM_LTOA(*(++p), b, 0);
        p--;
        for(uint8_t i = 0; i < 3; i++)
          *(p++) = (((b + i) == NULL) || !b[i]) ? BP_SPACE : b[i];
      } else p++;
    }
  };

  /* Compiles a single occurrence of a keyword into bytecode --------------- */
  char *compile_step(
    char *prog,
    char *pos,
    const char *key,
    const char *code,
    char post = 0,
    bool addr = 0,
    char end = 0
  ) {
    if(!prog || !pos || !key || !code) error(0, NULL, BP_ERROR_PROGRAM_GET);
    if(fail) return NULL;
    char *p;
    uint8_t kl = strlen(key), cl = strlen(code);
    p = strstr(pos, key);
    if(p && *p && (p < stop)) {
      if(in_string(prog, p) || (addr && p > prog && BCC_IS_ADDR(*(p - 1)))) {
        if(p = strstr(p + kl, key)) return p;
        return NULL;
      }
      if(end) {
        uint8_t i = kl;
        BCC_IGNORE_SUGAR(p);
        if(*(p + i) != end) {
          if(p = strstr(p + kl, key)) return p;
          return NULL;
        }
      }
      if(kl >= cl) {
        for(uint16_t i = 0; i < kl; i++, p++)
          if(i < cl && code[i]) *p = code[i]; else *p = BP_SPACE;
      } else {
        uint8_t ofs = cl - kl;
        if((strlen(prog) + ofs + 1) >= BCC_MAX_PROGRAM_SIZE) {
          error(line(prog, p), p, BP_ERROR_PROGRAM_LENGTH);
          return NULL;
        }
        memmove(p + ofs, p, strlen(p));
        for(uint16_t i = 0; i < cl; i++, p++) *p = code[i];
        *(stop + cl) = 0;
        stop = stop + cl;
      }
      if(post) {
        BCC_IGNORE_SUGAR(p);
        if(*p == post) *p = BP_SPACE;
      }
      return p;
    } return NULL;
  };

  void compile(
    char *prog,
    const char *key,
    const char *code,
    char post = 0,
    bool addr = 0,
    char end = 0
  ) {
    if(fail) return;
    char *p = prog;
    while(p && *p) p = compile_step(prog, p, key, code, post, addr, end);
  };

  void compile_char(
    char *prog,
    const char *key,
    const char code,
    char post = 0,
    bool addr = 0
  ) {
    if(fail) return;
    char *p = prog;
    const char c[2] = {code, 0};
    while(p && *p) p = compile_step(prog, p, key, c, post, addr);
  };

  /* Compiles user-defined variables in BIP bytecode ---------------------- */
  char *compile_variable(char *prog, char *position, char var_type) {
    if(!prog || !position) error(0, NULL, BP_ERROR_PROGRAM_GET);
    if(fail) return NULL;
    char type;
    if((var_type == BP_VAR_ADDR_HUMAN) || (var_type == BP_GLOBAL_HUMAN))
      type = BP_VAR_ADDR;
    else type = var_type;
    char *p, str[BP_KEYWORD_MAX] = {0}, code[4] = {type, 0, 0, 0};
    uint8_t n = 0;
    if((p = find_longest_var_name(prog, var_type)) != NULL) {
      str[n++] = var_type;
      *p = type;
      str[n++] = *(++p);
      if(type == BP_STR_ADDR) {
        BCC_NEW_ADDR(string_id);
      } else BCC_NEW_ADDR(var_id);
      *(p++) = (type == BP_STR_ADDR) ? string_id : var_id;
      for(uint16_t i = 0; i < BP_KEYWORD_MAX - 1; i++, p++)
        if(BCC_IS_KEYWORD(*p)) {
          str[n++] = *p;
          *p = BP_SPACE;
        } else break;
      if(n) {
        str[n] = 0;
        code[1] = (type == BP_STR_ADDR) ? string_id : var_id;
        code[2] = 0;
        compile(prog, str, code, 0, 1);
        p = strstr(position, str);
        if((p && *p) && !in_string(prog, p)) return p;
        return position;
      } return p;
    } return NULL;
  };

  void compile_variables(char *prog, char var_type) {
    if(fail) return;
    char *p = prog;
    while(p && *p) p = compile_variable(prog, p, var_type);
  };

  char *find_longest_var_name(char *prog, char var_type) {
    if(!prog) error(0, NULL, BP_ERROR_PROGRAM_GET);
    if(fail) return NULL;
    char *p = prog, *longest = 0;
    uint8_t result = 0;
    while((p && *p) && (p < stop))
      if(*(p++) == var_type) {
        if(in_string(prog, p - 1)) continue;
        if(BCC_IS_NUM(*p)) {
          error(line(prog, p), p, BP_ERROR_KEYWORD);
          return NULL;
        }
        uint8_t i = 0;
        while((p && *p) && BCC_IS_KEYWORD(*p++)) i++;
        if(i >= BP_KEYWORD_MAX) {
          error(line(prog, p), p, BP_ERROR_VARIABLE_NAME);
          return NULL;
        }
        if(i <= result) continue;
        longest = p - (i + 1);
        result = i;
      }
    if(result) return longest;
    return NULL;
  };

  /* Compiles a single user-defined function (longest name first):

     Funtion parameters are stored at the end of the address space.
     Each function uses the same addresses for its parameters consuming only
     BP_PARAMS addresses for all parameters present in the program. -------- */

  bool compile_function_step(char *prog) {
    if(!prog) error(0, NULL, BP_ERROR_PROGRAM_GET);
    if(fail) return false;
    char fn_keyword[BP_KEYWORD_MAX] = {0}, fn_address[3];
    char *p = find_longest_keyword(prog, true), *p2 = p, *p3 = NULL;
    uint8_t keyword_length = 0, f_id;
    if(p && *p) {
      f_id = fun_id;
      BCC_NEW_ADDR(fun_id);
      *(p++) = BP_FUN_DEF;
      *(p++) = fun_id;
      while(!BCC_SUGAR(p)) *(p++) = BP_SPACE;
      while(
        (++p && *p) && 
        (*p != BP_L_RPARENT) && 
        (keyword_length < (BP_KEYWORD_MAX - 1))
      ) {
        // Ignore sugar postfix
        if(!BCC_SUGAR(p)) {
          fn_keyword[keyword_length++] = *p;
          *p = BP_SPACE;
        }
      } // Remove commas from definition
      *p = BP_SPACE;
      while(p && *p && (*p != BP_R_RPARENT) || ((*p - 1) == BP_VAR_ADDR)) {
        if((*p == BP_COMMA) && !((*p - 1) == BP_VAR_ADDR)) *p = BP_SPACE;
        p++;
      } // Find the return keyword at the end of the function
      while((p = strstr(p, BP_RETURN_HUMAN)) && in_string(prog, p));
      if(p && *p) { // find the end of the line
        while(*p && p && *p != BP_CR && *p != BP_LF) p++;
        fn_keyword[keyword_length] = 0;
        // Delete the definition if the function is never called
        uint8_t count = 0;
        p3 = prog;
        while(((p3 = strstr(p3 + 1, fn_keyword)) != NULL) && (count <= 1))
          if(!in_string(prog, p3)) count++;
        if(count <= 0) {
          while(p2 <= p) *(p2++) = BP_SPACE;
          fun_id = f_id;
          return true;
        }
        stop = p; // Compile parameters
        var_id = BP_OFFSET + (BP_VARIABLES - BP_PARAMS) - 1;
        compile_variables(p2, BP_VAR_ADDR_HUMAN);
        find_end(prog);
        fn_address[0] = BP_FUNCTION;
        fn_address[1] = fun_id;
        fn_address[2] = 0; // Compile function calls
        compile(prog, fn_keyword, fn_address, BP_L_RPARENT, true, '(');
        return true;
      }
      error(0, NULL, BP_ERROR_RETURN);
    } return false;
  };

  void compile_functions(char *prog) {
    if(fail) return;
    while(compile_function_step(prog));
  };

  /* Finds longest keyword  ------------------------------------------------ */
  char *find_longest_keyword(char *prog, bool t) {
    if(!prog) error(0, NULL, BP_ERROR_PROGRAM_GET);
    if(fail) return NULL;
    char *p = prog, *p2, *longest = NULL;
    uint8_t result = 0;
    do {
      uint8_t i = 0;
      p = strstr(p, t ? BP_FUN_DEF_HUMAN : BP_MACRO_DEF_HUMAN);
      if(p && *p) {
        if(in_string(prog, p)) {
          ++p;
          continue;
        }
        p2 = p;
        if(BCC_IS_NUM(*p)) {
          error(line(prog, p), p, BP_ERROR_KEYWORD);
          return NULL;
        } 
        while(BCC_IS_KEYWORD(*p)) p++;
        BCC_IGNORE_SUGAR(p);
        while((p && *p) && t ? BCC_IS_KEYWORD(*p) : BCC_IS_CAP_KEYWORD(*p)) {
          i++;
          p++;
        }
        if(i > result) {
          longest = p2;
          result = i;
        }
        if(i >= BP_KEYWORD_MAX) {
          error(
            line(prog, p), p, t ? BP_ERROR_FUNCTION_NAME : BP_ERROR_MACRO_NAME
          );
          return NULL;
        }
      } else return longest;
    } while(*p && p);
    return NULL;
  };

  /* Compile for

   For variables are compiled inefficiently, each for gets a new address. -- */

  void compile_for(char *prog) {
    if(!prog) error(0, NULL, BP_ERROR_PROGRAM_GET);
    if(fail) return;
    char *p = prog, *p2 = prog;
    var_id = BP_OFFSET; // Reset variable address
    char c[2] = {BP_FOR, 0}; // While you find a for
    while(p = strstr(p, c)) {
      if(in_string(prog, p)) continue;
      p2 = p;
      int8_t n = 0; // Find the end of the for
      while((++p && *p) && (n >= 0)) {
        if(BCC_IS_ADDR(*(p - 1)) || in_string(prog, p)) continue;
        if(*p == BP_FOR) n++;
        if(*p == BP_NEXT) n--;
      }
      if(n != -1) return error(line(prog, p), p, BP_ERROR_NEXT);
      stop = p; // compile for variables within this for
      compile_variable(p2, p2, BP_FOR_ADDR);
      p = ++p2;
    }
    find_end(prog); // remove variable type from for variable declaration
    compile(prog, c, c, BP_FOR_ADDR, 1);
  };

  /* Pre-processor macros -------------------------------------------------- */
  void compile_macros(char *prog) {
    if(fail) return;
    while(compile_macro(prog));
  };

  bool compile_macro(char *prog) {
    if(!prog) error(0, NULL, BP_ERROR_PROGRAM_GET);
    if(fail) return false;
    char macro_name[BP_KEYWORD_MAX];
    char macro_code[BP_MACRO_MAX];
    char *p = find_longest_keyword(prog, false);
    if(p && *p) {
      while(BCC_IS_KEYWORD(*p)) *(p++) = BP_SPACE;
      BCC_IGNORE_SUGAR(p);
      uint8_t i;
      for(i = 0; BCC_IS_CAP_KEYWORD(*p) && (i < (BP_KEYWORD_MAX - 1)); i++) {
        macro_name[i] = *p;
        *(p++) = BP_SPACE;
      }
      macro_name[i] = 0;
      BCC_IGNORE_SUGAR(p);
      for(i = 0; p && *p && (i < (BP_MACRO_MAX - 1)); i++) {
        macro_code[i] = *p;
        *(p++) = BP_SPACE;
        if(!in_string(prog, p) && ((*p == BP_CR) || (*p == BP_LF))) break;
      }
      macro_code[++i] = 0;
      compile(prog, macro_name, macro_code);
      if(find_longest_keyword(prog, false)) return true;
    } return false;
  };

  /* Includes files:

     The content of each included file is copied at the end of the program.  */

  void compile_includes(char *prog) {
    if(fail) return;
    char *pos = prog;
    while(pos) pos = compile_include(prog, pos);
  };

  char *compile_include(char *prog, char *pos) {
    if(!prog || !pos) error(0, NULL, BP_ERROR_PROGRAM_GET);
    if(fail) return NULL;
    char include_path[BP_INCLUDE_PATH_MAX];
    FILE * p_file;
    long p_size;
    size_t result;
    char * p = strstr(pos, BP_INCLUDE_DEF_HUMAN);
    if(p && *p) {
      if(in_string(pos, p)) return compile_include(prog, p + 1);
      while(BCC_IS_KEYWORD(*p)) *(p++) = BP_SPACE;
      BCC_IGNORE_SUGAR(p);
      *(p++) = BP_SPACE;
      uint8_t i = 0;
      for(i = 0; (*p != BP_STRING) && (i < BP_INCLUDE_PATH_MAX); i++, p++) {
        include_path[i] = *p;
        *p = BP_SPACE;
      }
      include_path[i] = 0;
      *(p++) = BP_SPACE;
      p_file = fopen(include_path, "r");
      if(p_file == NULL) {
        error(line(prog, p), p, BP_ERROR_INCLUDE_PATH);
        return NULL;
      }
      fseek(p_file, 0, SEEK_END);
      p_size = ftell(p_file);
      rewind(p_file);
      if(p_size + strlen(prog) + 1 >= BCC_MAX_PROGRAM_SIZE)
        error(0, NULL, BP_ERROR_PROGRAM_LENGTH);
      else {
        result = fread(stop, 1, p_size, p_file);
        *(stop + p_size) = 0;
        if(result != p_size) {
          error(0, NULL, BP_ERROR_INCLUDE_READ);
          return NULL;
        }
      }
      fclose(p_file);
      find_end(prog);
      return p;
    } return NULL;
  };

  /* Pre-compilation checks ------------------------------------------------ */
  bool pre_compilation_checks(const char *prog) {
    if(fail) return fail;
    if(!check_delimeter(prog, BP_L_RPARENT, BP_R_RPARENT, true))
      error(0, NULL, BP_ERROR_ROUND_PARENTHESIS); // Check () parentheses
    if(!check_delimeter(prog, BP_ACCESS, BP_ACCESS_END, true))
      error(0, NULL, BP_ERROR_SQUARE_PARENTHESIS); // Check [] parentheses
    if(!check_delimeter(prog, BP_STRING, BP_STRING, true))
      error(0, NULL, BP_ERROR_STRING_END); // Check "" string separator
    return !fail;
  };

  /* Post-compilation checks ----------------------------------------------- */
  void post_compilation_checks(const char *prog) {
    if(fail) return;
    if(!check_delimeter(prog, BP_IF, BP_ENDIF))
      error(0, NULL, BP_ERROR_BLOCK); // Check if-end
    if(!check_delimeter(prog, BP_FUN_DEF, BP_RETURN))
      error(0, NULL, BP_ERROR_RETURN); // Check function return
    // Check variables, strings and functions buffer bounds
    if((fun_id - BP_OFFSET) >= BP_FUN_MAX) 
      error(0, NULL, BP_ERROR_FUNCTION_MAX);
    if((string_id - BP_OFFSET) >= BP_STRINGS) 
      error(0, NULL, BP_ERROR_STRING_MAX);
    if((var_id - BP_OFFSET) >= BP_VARIABLES) 
      error(0, NULL, BP_ERROR_VARIABLE_MAX);
  };

public:

  BCC() { };
  
  bcc_error_t error_callback = NULL;

  /* Run compilation process ----------------------------------------------- */
  bool run(char *prog) {
    find_end(prog);
    // Remove comments to be able to compile the includes
    remove_comments(prog);
    // Copy in includes, remove comments and process macros
    compile_includes(prog);
    remove_comments(prog);
    compile_macros(prog);
    // Compile character constants
    compile(prog, "'\\''", "39");
    compile_char_constants(prog);
    // Execute pre-compilation checks
    if(!pre_compilation_checks(prog)) return false;
    // Compile operators (longest first)
    compile_char(prog, BP_STR_ACC_HUMAN, BP_STR_ACC);
    compile_char(prog, BP_VAR_ACC_HUMAN, BP_VAR_ACC);
    compile_char(prog, BP_MEM_ACC_HUMAN, BP_MEM_ACC);
    compile_char(prog, BP_EQ_HUMAN, BP_EQ);
    compile_char(prog, BP_NOT_EQ_HUMAN, BP_NOT_EQ);
    compile_char(prog, BP_GTOEQ_HUMAN, BP_GTOEQ);
    compile_char(prog, BP_LTOEQ_HUMAN, BP_LTOEQ);
    compile_char(prog, BP_LOGIC_OR_HUMAN, BP_LOGIC_OR);
    compile_char(prog, BP_LOGIC_AND_HUMAN, BP_LOGIC_AND);
    compile_char(prog, BP_R_SHIFT_HUMAN, BP_R_SHIFT);
    compile_char(prog, BP_L_SHIFT_HUMAN, BP_L_SHIFT);
    // A single = is just syntactic sugar in BIPLAN so it is removed
    compile_char(prog, "=", BP_SPACE); 
    compile_char(prog, BP_INCREMENT_HUMAN, BP_INCREMENT);
    compile_char(prog, BP_DECREMENT_HUMAN, BP_DECREMENT);
    compile_char(prog, BP_BITWISE_NOT_HUMAN, BP_BITWISE_NOT);
    // Compile functions and variables
    compile_functions(prog);
    var_id = BP_OFFSET;
    find_end(prog);
    compile_variables(prog, BP_GLOBAL_HUMAN);
    compile_variables(prog, BP_STR_ADDR);
    // Compile syntax and system functions (longest first)
    compile_char(prog, BP_RND_HUMAN, BP_RND);
    compile_char(prog, BP_MILLIS_HUMAN, BP_MILLIS);
    compile_char(prog, BP_DELAY_HUMAN, BP_DELAY);
    compile_char(prog, BP_SERIAL_HUMAN, BP_SERIAL);
    compile_char(prog, BP_CONTINUE_HUMAN, BP_CONTINUE);
    compile_char(prog, BP_RESTART_HUMAN, BP_RESTART);
    compile_char(prog, BP_RETURN_HUMAN, BP_RETURN);
    compile_char(prog, BP_SYSTEM_HUMAN, BP_SYSTEM);
    compile_char(prog, BP_CURSOR_HUMAN, BP_CURSOR);
    compile_char(prog, "locals:", BP_SPACE);
    compile_char(prog, BP_LTOA_HUMAN, BP_LTOA);
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
    compile_char(prog, BP_END_HUMAN, BP_END);
    compile_char(prog, BP_FOR_HUMAN, BP_FOR);
    compile_char(prog, BP_ADC_HUMAN, BP_ADC);
    compile(prog, "args[", "S");
    compile_char(prog, "step", BP_COMMA);
    compile(prog, "not", "1-");
    compile_char(prog, BP_IF_HUMAN, BP_IF);
    compile_char(prog, BP_IO_HUMAN, BP_IO);
    compile_char(prog, BP_TO_HUMAN, BP_COMMA);
    // Compile for loops
    compile_for(prog);
    // Compile constants (longest first)
    compile(prog, "OUTPUT", "1");
    compile(prog, "INPUT", "0");
    compile(prog, "HIGH", "1");
    compile(prog, "LOW", "0");
    compile(prog, "EOF", "-1");
    compile(prog, "false", "0");
    compile(prog, "true", "1");
    compile(prog, "LF", "10");
    compile(prog, "CR", "13");
    // Remove sugar
    remove(prog, BP_CR, BP_LF, BP_SPACE, BP_TAB);
    var_id = BP_OFFSET, string_id = BP_OFFSET + BP_ARGS, fun_id = BP_OFFSET;
    // Execute post-compilation checks
    post_compilation_checks(prog);
    return !fail;
  };
};
