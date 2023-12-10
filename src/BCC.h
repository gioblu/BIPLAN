
/* BIPLAN CR.1 (Byte coded Interpreted Programming Language)

      _____              _________________________
     |   | |            |_________________________|
     |   | |_______________||__________   \___||_________ |
   __|___|_|               ||          |__|   ||     |   ||
  /________|_______________||_________________||__   |   |D
    (O)                 |_________________________|__|___/|
                                           \ /            |
                                           (O)

  Giovanni Blu Mitolo 2017-2022 - gioscarab@gmail.com
  BCC (BIPLAN Compiler Collection) - BIPLAN to BIP compiler  */

#pragma once
#include "BIPLAN_Defines.h"
#include "BCC.h"

/* Checks if the character is an acceptable numeric symbol ----------------- */
#define BCC_IS_NUM(C) (C >= '0' && C <= '9')

/* Checks if the character is an acceptable keyword symbol ----------------- */
#define BCC_IS_KEYWORD(C) \
  ((C >= 'a' && C <= 'z') || (C >= 'A' && C <= 'Z') || (C == '_'))

/* Checks if the character is an acceptable capitalized keyword symbol ------*/
#define BCC_IS_CAP_KEYWORD(C) \
  ((C >= 'A' && C <= 'Z') || (C == '_'))

/* Checks if the character passed is an acceptable address ----------------- */
#define BCC_IS_ADDR(C) ( \
  (C == BP_VAR_ADDR) || (C == BP_STR_ADDR) || (C == BP_FOR_ADDR) || \
  (C == BP_FUNCTION) || (C == BP_FUN_DEF) \
)

/* Sets A to the next available address (avoiding reserved characters) ----- */
#define BCC_NEW_ADDR(A) do { A++; } while(BCC_IS_ADDR(A));

class BCC {
public:
  char var_id = BP_OFFSET, string_id = BP_OFFSET + BP_ARGS, fun_id = BP_OFFSET;

  bip_error_t error_callback = NULL;
  bool fail = false;
  char *stop;

  BCC() { };

  /* Function called in case of compilation error -------------------------- */
  void error(char *position, const char *string) {
    error_callback(position, string);
    fail = true;
  };

  /* Checks consistency of syntax delimiters ------------------------------- */
  bool check_delimeter(char *prog, char a, char b, char c = 0, bool aa = 0) {
    uint16_t ia = 0, ib = 0;
    char *p = prog;
    while(p && *p) {
      if(!in_string(prog, p) && (aa || !BCC_IS_ADDR(*(p - 1)))) {
        if(*p == a) ia++;
        if(*p == b) ib++;
        if(c && (*p == c)) ib++;
      } p++;
    } return (ia == ib);
  };

  /* Finds the end of a program -------------------------------------------- */
  void find_end(char *prog) {
    char *p;
    if(strlen(prog) >= BCC_MAX_PROGRAM_SIZE)
      return error(0, BP_ERROR_PROGRAM_LENGTH);
    for(p = prog; *p != 0; p++);
    stop = p;
  };

  /* Checks if a certain position in the program is within a string -------- */
  bool in_string(char *prog, char *pos) {
    bool in_str = false;
    char *p = prog;
    while((p && *p) && (pos >= p)) {
      if(in_str && *p == BP_BACKSLASH) { p += 2; continue; } // Jump escape + 1
      // Returns false if " is found outside a string
      if((pos == p) && (*p == BP_STRING) && !in_str) return in_str;
      if(*p == BP_STRING) in_str = !in_str;
      p++;
    } return in_str;
  };

  /* Remove a given symbol from the program -------------------------------- */
  void remove(char *s, char v) {
    if(fail) return;
    char *i = s, *j = s;
    bool in_str = false;
    while(j && *j) {
      *i = *j++;
      if(*i == BP_STRING && *(i - 1) != BP_BACKSLASH) in_str = !in_str;
      if(*i != v) i++;
      else if(in_str) i++;
    } *i = 0;
  };

  /* Remove comments from program ------------------------------------------ */
  void remove_comments(char *prog) {
    if(fail) return;
    char *p;
    while((p = strstr(prog, BP_COMMENT)))
      if(!in_string(prog, p) && !BCC_IS_ADDR(*(p - 1)))
        while((p && *p) && (*p != BP_CR) && (*p != BP_LF)) *(p++) = ' ';
  };

  /* Compiles character constants such as '@' into 64 (its decimal value) -- */
  void compile_char_constants(char *prog) {
    char *p = prog, b[3] = {};
    while(p && *p) {
      if(!in_string(prog, p) && (*p == BP_SINGLE_QUOTE)) {
        if(*(p + 2) != BP_SINGLE_QUOTE) {
          error(0, BP_ERROR_SINGLE_QUOTE);
          return;
        }
        BPM_LTOA(*(++p), b, 0);
        p--;
        for(uint8_t i = 0; i < 3; i++)
          *(p++) = (((b + i) == NULL) || !b[i]) ? BP_SPACE : b[i];
      } else p++;
    }
  };

  /* Compiles 3.141 in 3141 (by default BP_FIXED_P = 1000) ----------------- */

  void compile_numbers(char *prog) {
    char *p = prog;
    float v = 0;
    while(p && *p) {
      char n[BP_NUM_MAX + 1] = {0};
      char r[BP_NUM_MAX] = {0};
      if(
        (*p == '.') && !in_string(prog, p) && 
        BCC_IS_NUM(*(p + 1)) && BCC_IS_NUM(*(p - 1)) 
      ) {
        do { p--; } while(BCC_IS_NUM(*p)); 
        v = BP_FIXED_P * BPM_ATOF(p + 1);
        BPM_ROUND(v);
        BPM_LTOA(v, r, 0);
        for(uint8_t i = 0; (*(++p) == '.') || BCC_IS_NUM(*p); i++) 
          if(i <= BP_NUM_MAX) n[i] = *(p);
          else *p = ' ';
        compile(prog, n, r);
      }
      p++;
    }
  }

  /* Compiles BIPLAN keywords into BIP byte-code --------------------------- */
  char *compile_pass(
    char *prog,
    char *pos,
    const char *key,
    const char *code,
    char post = 0,
    bool addr = 0,
    char end = 0
  ) {
    char *p;
    uint8_t kl = strlen(key), cl = strlen(code);
    p = strstr(pos, key);
    if(p && *p) {
      if(in_string(prog, p) || (addr && BCC_IS_ADDR(*(p - 1))) || (p >= stop)) {
        p = strstr(p + kl, key);
        if(p && *p) return p; else return NULL;
      }
      if(end) {
        uint8_t i = kl;
        for(; *(p + i) == BP_SPACE; i++);
        if(*(p + i) != end) {
          p = strstr(p + kl, key);
          if(p && *p) return p; else return NULL;
        }
      }
      if(kl >= cl) {
        for(uint16_t i = 0; i < kl; i++, p++)
          if(i < cl && code[i]) *p = code[i]; else *p = BP_SPACE;
      } else {
        uint8_t ofs = cl - kl;
        if((strlen(prog) + ofs) >= BCC_MAX_PROGRAM_SIZE)
          error(0, BP_ERROR_PROGRAM_LENGTH);
        else {
          memmove(p + ofs, p, strlen(p));
          *(stop + cl) = 0;
          for(uint16_t i = 0; i < cl; i++, p++) *p = code[i];
          find_end(prog);
        }
      }
      if(post) {
        while(*p == BP_SPACE) p++;
        if(*p == post) *p = BP_SPACE;
      }
      return p;
    } else return NULL;
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
    while(p && *p) p = compile_pass(prog, p, key, code, post, addr, end);
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
    while(p && *p) p = compile_pass(prog, p, key, (const char *)c, post, addr);
  };

  /* Compiles user-defined variables in BIP byte-code ---------------------- */
  char *compile_variable(char *prog, char *position, char var_type) {
    char type;
    if((var_type == BP_VAR_ADDR_HUMAN) || (var_type == BP_GLOBAL_HUMAN))
      type = BP_VAR_ADDR;
    else type = var_type;
    char *p, str[BP_KEYWORD_MAX], code[4] = {type, 0, 0, 0};
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
          if((i == (BP_KEYWORD_MAX - 2)) && (BCC_IS_KEYWORD(*(p + 1)))) {
            error(0, BP_ERROR_VARIABLE_NAME);
            return NULL;
          }
        } else break;
      if(n) {
        str[n] = 0;
        code[1] = (type == BP_STR_ADDR) ? string_id : var_id;
        code[2] = 0;
        compile(prog, str, code, 0, 1);
        p = strstr(position, str);
        if((p && *p) && !in_string(prog, p)) return p;
        return (char *)position;
      } return p;
    } return NULL;
  };

  void compile_variables(char *prog, char var_type) {
    if(fail) return;
    char *p = prog;
    while(p && *p) p = compile_variable(prog, p, var_type);
  };

  char *find_longest_var_name(char *prog, char var_type) {
    char *p = prog, *longest = 0;
    uint8_t result = 0;
    while((p && *p) && (p <= stop))
      if(*(p++) == var_type) {
        if(in_string(prog, p - 1) || BCC_IS_ADDR(*(p - 2))) continue;
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

  /* Compiles user-defined functions:

     Funtion parameters are stored at the end of the address space.
     Each function uses the same addresses for its parameters consuming only
     BP_PARAMS addresses for all functions present in the program. --------- */

  bool compile_function_pass(char *prog) {
    char fn_keyword[BP_KEYWORD_MAX], fn_address[3];
    char *p = find_longest_keyword(prog, true), *p2 = p, *p3 = NULL;
    uint8_t keyword_length = 0, f_id;
    if(p && *p) {
      f_id = fun_id;
      BCC_NEW_ADDR(fun_id);
      *(p++) = BP_FUN_DEF;
      *(p++) = fun_id;
      while(*p != BP_SPACE) *(p++) = BP_SPACE;
      while((++p && *p) && (*p != BP_L_RPARENT)) {
        fn_keyword[keyword_length++] = *p;
        *p = BP_SPACE;
      } // Remove commas from definition
      *p = BP_SPACE;
      while((*p != BP_R_RPARENT) || ((*p - 1) == BP_VAR_ADDR)) {
        if((*p == BP_COMMA) && !((*p - 1) == BP_VAR_ADDR)) *p = BP_SPACE;
        p++;
      } // Find the return keyword at the end of the function
      while((p = strstr(p, BP_RETURN_HUMAN)) && *p && in_string(prog, p));
      if(p && *p) { // find the end of the line
        while(*p && p && *p != BP_CR && *p != BP_LF) p++;
        fn_keyword[keyword_length] = 0;
        // Delete the definition if the function is never called
        uint8_t count = 0;
        p3 = prog;
        while(((p3 = strstr(p3 + 1, fn_keyword)) != NULL) && (count <= 1))
          count++;
        if(count <= 1) {
          while(p2 <= p) *(p2++) = ' ';
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
      error(0, BP_ERROR_RETURN);
    } return false;
  };

  void compile_functions(char *prog) {
    if(fail) return;
    while(compile_function_pass(prog));
  };

  /* Finds longest keyword  ------------------------------------------------ */
  char *find_longest_keyword(char *prog, bool t) {
    char *p = prog, *p2, *longest = NULL;
    uint8_t result = 0;
    do {
      uint8_t i = 0;
      p = strstr(p, t ? BP_FUN_DEF_HUMAN : BP_MACRO_DEF_HUMAN);
      if(p && *p) {
        if(in_string(prog, p)) {
          p = strstr(p + 1, t ? BP_FUN_DEF_HUMAN : BP_MACRO_DEF_HUMAN), p2 = p;
          if(!p || !*p) return NULL;
        }
        p2 = p;
        while(BCC_IS_KEYWORD(*p)) p++;
        while(*p == BP_SPACE) p++;
        while((p && *p) && t ? BCC_IS_KEYWORD(*p) : BCC_IS_CAP_KEYWORD(*p)) {
          i++;
          p++;
        }
        if(i > result) {
          longest = p2;
          result = i;
        }
        if(i >= BP_KEYWORD_MAX) {
          error(0, t ? BP_ERROR_FUNCTION_NAME : BP_ERROR_MACRO_NAME);
          return NULL;
        }
      } else return longest;
    } while(*p && p);
    return NULL;
  };

  /* Compile for

   For variables are compiled inefficiently, each for gets a new address. -- */

  void compile_for(char *prog) {
    char *p = prog, *p2 = prog;
    var_id = BP_OFFSET;
    char c[2] = {BP_FOR, 0}; // While you find a for
    while((p = strstr(p, c)) && *p) {
      if(in_string(prog, p)) continue;
      p2 = p;
      int8_t n = 0; // Find the end of the for
      while((++p && *p) && (n >= 0)) {
        if(BCC_IS_ADDR(*(p - 1)) || in_string(prog, p)) continue;
        if(*p == BP_FOR) n++;
        if(*p == BP_NEXT) n--;
      }
      if(n != -1) return error(p, BP_ERROR_NEXT);
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
    char macro_name[BP_KEYWORD_MAX];
    char macro_code[BP_MACRO_MAX];
    char *p = find_longest_keyword(prog, false);
    if(p && *p) {
      while(BCC_IS_KEYWORD(*p)) *(p++) = ' ';
      while(*p == BP_SPACE) p++;
      uint8_t i;
      for(i = 0; BCC_IS_CAP_KEYWORD(*p) && (i < BP_KEYWORD_MAX); i++, p++) {
        macro_name[i] = *p;
        *p = BP_SPACE;
      }
      macro_name[i] = 0;
      while(*p == BP_SPACE) p++;
      for(i = 0; (p && *p) && (*p != BP_CR) && (*p != BP_LF); i++) {
        macro_code[i] = *p;
        *(p++) = BP_SPACE;
      }
      macro_code[i] = 0;
      compile(prog, macro_name, macro_code);
      if(find_longest_keyword(prog, false)) return true;
    }
    return false;
  };

  /* Includes files:

     Files contents are copied at the end of the program. ------------------ */

  void compile_includes(char *prog) {
    if(fail) return;
    char *pos = prog;
    while(pos) pos = compile_include(prog, pos);
  };

  char *compile_include(char *prog, char *pos) {
    char include_path[BP_INCLUDE_PATH_MAX];
    FILE * p_file;
    long p_size;
    size_t result;
    char * p = strstr(pos, BP_INCLUDE_DEF_HUMAN);
    if(p && *p) {
      if(in_string(pos, p)) return compile_include(prog, p + 1);
      while(BCC_IS_KEYWORD(*p)) *(p++) = ' ';
      while(*p == BP_SPACE) p++;
      *(p++) = ' ';
      uint8_t i = 0;
      for(i = 0; (*p != BP_STRING) && (i < BP_INCLUDE_PATH_MAX); i++, p++) {
        include_path[i] = *p;
        *p = ' '; 
      }
      include_path[i] = 0;
      *(p++) = ' ';
      p_file = fopen(include_path, "r");
      if(p_file == NULL) {
        error(0, BP_ERROR_INCLUDE_PATH);
        return NULL;
      }
      fseek(p_file, 0, SEEK_END);
      p_size = ftell(p_file);
      rewind(p_file);
      if(((sizeof(char) * p_size) + strlen(prog))  >= BCC_MAX_PROGRAM_SIZE) 
        error(0, BP_ERROR_PROGRAM_LENGTH);
      else {
        result = fread(stop, 1, p_size, p_file);
        *(stop + p_size) = 0;
        if(result != p_size) {
          error(0, BP_ERROR_INCLUDE_READ);
          return NULL;
        }
      }
      fclose(p_file);
      find_end(prog);
      return p;
    }
    return NULL;
  };

  /* Pre-compilation checks ------------------------------------------------ */
  bool pre_compilation_checks(char *prog) {
    if(!check_delimeter(prog, BP_L_RPARENT, BP_R_RPARENT))
      error(0, BP_ERROR_ROUND_PARENTHESIS);  // Check () parentheses
    if(!check_delimeter(prog, BP_ACCESS, BP_ACCESS_END, 0, 1))
      error(0, BP_ERROR_SQUARE_PARENTHESIS); // Check [] parentheses
    if(!check_delimeter(prog, BP_STRING, BP_STRING))
      error(0, BP_ERROR_STRING_END);         // Check "" string separator
    return !fail;
  };

  /* Post-compilation checks ----------------------------------------------- */
  void post_compilation_checks(char *prog) {
    if(!check_delimeter(prog, BP_IF, BP_ENDIF))
      error(0, BP_ERROR_BLOCK); // Check if-end
    if(!check_delimeter(prog, BP_FUN_DEF, BP_RETURN))
      error(0, BP_ERROR_RETURN); // Check function return
    // Check variables, strings and functions buffer bounds
    if((fun_id - BP_OFFSET) >= BP_FUN_MAX) error(0, BP_ERROR_FUNCTION_MAX);
    if((string_id - BP_OFFSET) >= BP_STRINGS) error(0, BP_ERROR_STRING_MAX);
    if((var_id - BP_OFFSET) >= BP_VARIABLES) error(0, BP_ERROR_VARIABLE_MAX);
  };

  /* Run compilation process ----------------------------------------------- */
  bool run(char *prog) {
    find_end(prog);
    remove_comments(prog);
    compile_includes(prog);
    remove_comments(prog);
    compile_macros(prog);
    compile_numbers(prog);
    compile(prog, "'\\''", "39");
    compile_char_constants(prog);
    if(!pre_compilation_checks(prog)) return false;
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
    compile_char(prog, "=", ' '); // Remove syntactic sugar
    compile_char(prog, BP_INCREMENT_HUMAN, BP_INCREMENT);
    compile_char(prog, BP_DECREMENT_HUMAN, BP_DECREMENT);
    compile_char(prog, BP_BITWISE_NOT_HUMAN, BP_BITWISE_NOT);
    compile_functions(prog);
    var_id = BP_OFFSET;
    find_end(prog);
    compile_variables(prog, BP_GLOBAL_HUMAN);
    compile_variables(prog, BP_STR_ADDR);
    char precision[BP_NUM_MAX];
    BPM_LTOA(BP_FIXED_P, precision, 0);
    compile(prog, BP_PRECISION_HUMAN, precision);
    compile_char(prog, BP_RND_HUMAN, BP_RND);
    compile_char(prog, BP_MILLIS_HUMAN, BP_MILLIS);
    compile_char(prog, BP_DELAY_HUMAN, BP_DELAY);
    compile_char(prog, BP_FIXED_HUMAN, BP_FIXED);
    compile_char(prog, BP_SQRT_HUMAN, BP_SQRT);
    compile_char(prog, BP_SERIAL_HUMAN, BP_SERIAL);
    compile_char(prog, BP_RESULT_HUMAN, BP_RESULT);
    compile_char(prog, BP_CONTINUE_HUMAN, BP_CONTINUE);
    compile_char(prog, BP_RESTART_HUMAN, BP_RESTART);
    compile_char(prog, BP_RETURN_HUMAN, BP_RETURN);
    compile_char(prog, BP_SYSTEM_HUMAN, BP_SYSTEM);
    compile_char(prog, BP_CURSOR_HUMAN, BP_CURSOR);
    compile_char(prog, "locals:", ' ');
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
    compile_char(prog, BP_JUMP_HUMAN, BP_JUMP);
    compile_char(prog, BP_LABEL_HUMAN, BP_LABEL);
    compile_char(prog, BP_END_HUMAN, BP_END);
    compile_char(prog, BP_FOR_HUMAN, BP_FOR);
    compile_char(prog, BP_ADC_HUMAN, BP_ADC);
    compile_char(prog, BP_SIN_HUMAN, BP_SIN);
    compile_char(prog, BP_COS_HUMAN, BP_COS);
    compile_char(prog, BP_TAN_HUMAN, BP_TAN);
    compile(prog, "args[", "S");
    compile_char(prog, "step", BP_COMMA);
    compile(prog, "not", "1-");
    compile_char(prog, BP_IF_HUMAN, BP_IF);
    compile_char(prog, BP_IO_HUMAN, BP_IO);
    compile_char(prog, BP_TO_HUMAN, BP_COMMA);
    compile_for(prog);
    compile(prog, "OUTPUT", "1");
    compile(prog, "INPUT", "0");
    compile(prog, "HIGH", "1");
    compile(prog, "LOW", "0");
    compile(prog, "EOF", "-1");
    compile(prog, "false", "0");
    compile(prog, "true", "1");
    compile(prog, "LF", "10");
    compile(prog, "CR", "13");
    remove(prog, BP_CR);
    remove(prog, BP_LF);
    remove(prog, BP_SPACE);
    remove(prog, BP_TAB);
    var_id = BP_OFFSET, string_id = BP_OFFSET + BP_ARGS, fun_id = BP_OFFSET;
    post_compilation_checks(prog);
    return !fail;
  };
};
