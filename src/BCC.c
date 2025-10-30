
/* BCC (BIPLAN Compiler Collection) - BIPLAN to BIP compiler

      _____              _________________________
     |   | |            |_________________________|
     |   | |_______________||__________   \___||_________ |
   __|___|_|               ||          |__|   ||     |   ||
  /________|_______________||_________________||__   |   |D
    (O)                 |_________________________|__|___/|
                                           \ /            |
                                           (O)

  Giovanni Blu Mitolo 2017-2025 - gioscarab@gmail.com */

#include "BCC.h"

typedef void (*bcc_error_t)(uint16_t line, const char *p, const char *s);

int bcc_fail = 0;
char bcc_var_id = BP_OFFSET;
char bcc_string_id = BP_OFFSET + BP_ARGS;
char bcc_fun_id = BP_OFFSET;
char *bcc_stop = NULL;

/* Checks if the character is an acceptable numeric symbol ----------------- */
#define BCC_IS_NUM(C) ((C) >= '0' && (C) <= '9')

/* Checks if the character is an acceptable keyword symbol ----------------- */
#define BCC_IS_KEYWORD(C) ( \
  ((C) >= 'a' && (C) <= 'z') || ((C) >= 'A' && (C) <= 'Z') || \
  ((C) == '_') || ((C) >= '0' && (C) <= '9') )

/* Checks if the character is an acceptable capitalized keyword symbol ------*/
#define BCC_IS_CAP_KEYWORD(C) ( \
  ((C) >= 'A' && (C) <= 'Z') || ((C) == '_') || ((C) >= '0' && (C) <= '9') )

/* Checks if the character passed is an acceptable address ----------------- */
#define BCC_IS_ADDR(C) ( \
  ((C) == BP_VAR_ADDR) || ((C) == BP_STR_ADDR) || ((C) == BP_FOR_ADDR) || \
  ((C) == BP_FOR) || ((C) == BP_FUNCTION) || ((C) == BP_FUN_DEF) )

/* Sets A to the next available address (avoiding reserved characters) ----- */
#define BCC_NEW_ADDR(A) do { (A)++; } while(BCC_IS_ADDR(A))

/*  Checks if the character passed is syntactic sugar ---------------------- */
#define BCC_SUGAR(P) \
  (*(P) == BP_SPACE) || (*(P) == BP_CR) || (*(P) == BP_LF) || (*(P) == BP_TAB)

/* Ignores syntactic sugar ------------------------------------------------- */
#define bcc_IGNORE_SUGAR(P) while(BCC_SUGAR(P)) (P)++

/* Function called in case of compilation error ---------------------------- */
void bcc_error(uint16_t line, const char *position, const char *string) {
  if(bcc_error_callback) bcc_error_callback(line, position, string);
  bcc_fail = 1;
}

/* Determines the program line at a certain position ----------------------- */
uint16_t bcc_line(const char *prog, const char *pos) {
  if(!prog || !pos || bcc_fail) {
    if(!bcc_fail) bcc_error(0, NULL, BP_ERROR_PROGRAM_GET);
    return 0;
  }
  uint16_t i = 1;
  const char *p = prog;
  while((p && *p) && (p <= pos)) {
    if(!bcc_in_string(prog, p) && (*p == BP_LF)) i++;
    p++;
  } 
  return i;
}

/* Checks consistency of syntax delimiters --------------------------------- */
int bcc_check_delimeter(const char *prog, char a, char b, int ignore) {
  if(!prog || bcc_fail) {
    if(!bcc_fail) bcc_error(0, NULL, BP_ERROR_PROGRAM_GET);
    return 0;
  }
  uint16_t ia = 0, ib = 0;
  const char *p = prog;
  while(p && *p) {
    if(
      !bcc_in_string(prog, p) && 
      (ignore || p == prog || (p > prog && !BCC_IS_ADDR(*(p - 1))))
    ) {
      if((a == b) && (*p == a)) ia = !ia;
      else {
        if(*p == a) ia++;
        if(*p == b) ib++;
      }
    } 
    p++;
  } 
  return (ia == ib);
}

/* Finds the end of a program ---------------------------------------------- */
void bcc_find_end(char *prog) {
  if(!prog || bcc_fail) {
    if(!bcc_fail) bcc_error(0, NULL, BP_ERROR_PROGRAM_GET);
    return;
  }
  if(strlen(prog) >= BCC_MAX_PROGRAM_SIZE)
    bcc_error(0, NULL, BP_ERROR_PROGRAM_LENGTH);
  for(bcc_stop = prog; *bcc_stop != 0; bcc_stop++);
}

/* Checks if a certain position in the program is within a string ---------- */
int bcc_in_string(const char *prog, const char *pos) {
  if(!prog || !pos || bcc_fail) {
    if(!bcc_fail) bcc_error(0, NULL, BP_ERROR_PROGRAM_GET);
    return 0;
  }
  int in_str = 0;
  const char *p = prog;
  while((p && *p) && (pos >= p)) {
    if(in_str && *p == BP_BACKSLASH) p += 2;
    else {
      if((pos == p) && (*p == BP_STRING) && !in_str) return 0;
      if(*p == BP_STRING) in_str = !in_str;
      p++;
    }
  } 
  return in_str;
}

/* Remove a given symbol from the program ---------------------------------- */
void bcc_remove(char *prog, char v1, char v2, char v3, char v4) {
  if(!prog || bcc_fail) {
    if(!bcc_fail) bcc_error(0, NULL, BP_ERROR_PROGRAM_GET);
    return;
  }
  char *p = prog, *p2 = prog;
  int in_str = 0;
  while(p2 && *p2) {
    *p = *p2++;
    if(*p == BP_STRING) {
      if(!in_str || (in_str && p > prog && (*(p - 1) != BP_BACKSLASH)))
        in_str = !in_str;
    }
    if((*p != v1) && (*p != v2) && (*p != v3) && (*p != v4)) p++;
    else if(in_str) p++;
  } 
  *p = 0;
}

/* Remove comments from program -------------------------------------------- */
void bcc_remove_comments(char *prog) {
  if(!prog || bcc_fail) {
    if(!bcc_fail) bcc_error(0, NULL, BP_ERROR_PROGRAM_GET);
    return;
  }
  char *p;
  while((p = strstr(prog, BP_COMMENT)))
    if(!bcc_in_string(prog, p)) {
      while((p && *p) && (*p != BP_CR) && (*p != BP_LF)) *(p++) = BP_SPACE;
    } else p++;
}

/* Compiles character constants such as '@' into 64 (its decimal value) ---- */
void bcc_compile_char_constants(char *prog) {
  if(!prog || bcc_fail) {
    if(!bcc_fail) bcc_error(0, NULL, BP_ERROR_PROGRAM_GET);
    return;
  }
  char *p = prog, b[3] = {0};
  while(p && *p) {
    if(!bcc_in_string(prog, p) && (*p == BP_SINGLE_QUOTE)) {
      if(*(p + 2) != BP_SINGLE_QUOTE) {
        bcc_error(bcc_line(prog, p), p, BP_ERROR_SINGLE_QUOTE);
        return;
      }
      BPM_LTOA(*(++p), b, 0);
      p--;
      for(unsigned char i = 0; i < 3; i++)
        *(p++) = (((b + i) == NULL) || !b[i]) ? BP_SPACE : b[i];
    } else p++;
  }
}

/* Compiles a single occurrence of a keyword into bytecode ----------------- */
char *bcc_compile_step(
  char *prog, 
  char *pos, 
  const char *key, 
  const char *code, 
  char post, 
  int addr, 
  char end
) {
  if(!prog || !pos || !key || !code || bcc_fail) {
    if(!bcc_fail) bcc_error(0, NULL, BP_ERROR_PROGRAM_GET);
    return NULL;
  }
  char *p;
  unsigned char kl = strlen(key), cl = strlen(code);
  p = strstr(pos, key);
  if(p && *p && (p < bcc_stop)) {
    if(bcc_in_string(prog, p) || (addr && p > prog && BCC_IS_ADDR(*(p - 1)))) {
      if((p = strstr(p + kl, key))) return p;
      return NULL;
    }
    if(end) {
      unsigned char i = kl;
      bcc_IGNORE_SUGAR(p);
      if(*(p + i) != end) {
        if((p = strstr(p + kl, key))) return p;
        return NULL;
      }
    }
    if(kl >= cl) {
      for(unsigned int i = 0; i < kl; i++, p++)
        if(i < cl && code[i]) *p = code[i];
        else *p = BP_SPACE;
    } else {
      unsigned char ofs = cl - kl;
      if((strlen(prog) + ofs + 1) >= BCC_MAX_PROGRAM_SIZE) {
        bcc_error(bcc_line(prog, p), p, BP_ERROR_PROGRAM_LENGTH);
        return NULL;
      }
      memmove(p + ofs, p, strlen(p) + 1);
      for(unsigned int i = 0; i < cl; i++, p++) *p = code[i];
      bcc_stop = bcc_stop + cl;
    }
    if(post) {
      bcc_IGNORE_SUGAR(p);
      if(*p == post) *p = BP_SPACE;
    }
    return p;
  } 
  return NULL;
}

void bcc_compile(
  char *prog, 
  const char *key, 
  const char *code, 
  char post, 
  int addr, 
  char end
) {
  if(bcc_fail) return;
  char *p = prog;
  while(p && *p) p = bcc_compile_step(prog, p, key, code, post, addr, end);
}

void bcc_compile_char(
  char *prog, 
  const char *key, 
  char code, 
  char post, 
  int addr
) {
  if(bcc_fail) return;
  char *p = prog;
  char c[2] = {code, 0};
  while(p && *p) p = bcc_compile_step(prog, p, key, c, post, addr, 0);
}

/* Finds longest variable name  -------------------------------------------- */
char *bcc_find_longest_var_name(char *prog, char var_type) {
  if(!prog || bcc_fail) {
    if(!bcc_fail) bcc_error(0, NULL, BP_ERROR_PROGRAM_GET);
    return NULL;
  }
  char *p = prog, *longest = NULL;
  unsigned char result = 0;
  while(p && *p && (p < bcc_stop)) {
    if(*(p++) == var_type) {
      if(bcc_in_string(prog, p - 1)) continue;
      if(BCC_IS_NUM(*p)) {
        bcc_error(bcc_line(prog, p), p, BP_ERROR_KEYWORD);
        return NULL;
      }
      unsigned char i = 0;
      while(BCC_IS_KEYWORD(*p) && (p && *(p++))) i++;
      if(i >= BP_KEYWORD_MAX) {
        bcc_error(bcc_line(prog, p), p, BP_ERROR_VARIABLE_NAME);
        return NULL;
      }
      if(i <= result) continue;
      longest = p - (i + 1);
      result = i;
    }
  } 
  return (result) ? longest : NULL;
}

/* Compiles user-defined variables in BIP bytecode ------------------------- */
char *bcc_compile_variable(char *prog, char *position, char var_type) {
  if(!prog || !position || bcc_fail) {
    if(!bcc_fail) bcc_error(0, NULL, BP_ERROR_PROGRAM_GET);
    return NULL;
  }
  char type = var_type;
  if((var_type == BP_VAR_ADDR_HUMAN) || (var_type == BP_GLOBAL_HUMAN)) 
    type = BP_VAR_ADDR;
  char *p, str[BP_KEYWORD_MAX] = {0}, code[4] = {type, 0, 0, 0};
  unsigned char n = 0;
  if((p = bcc_find_longest_var_name(prog, var_type)) != NULL) {
    str[n++] = var_type;
    *p = type;
    str[n++] = *(++p);
    if(type == BP_STR_ADDR) BCC_NEW_ADDR(bcc_string_id);
    else BCC_NEW_ADDR(bcc_var_id);
    *(p++) = (type == BP_STR_ADDR) ? bcc_string_id : bcc_var_id;
    for(unsigned int i = 0; i < BP_KEYWORD_MAX - 1; i++, p++) {
      if(BCC_IS_KEYWORD(*p)) {
        str[n++] = *p;
        *p = BP_SPACE;
      } else break;
    }
    if(n) {
      str[n] = 0;
      code[1] = (type == BP_STR_ADDR) ? bcc_string_id : bcc_var_id;
      code[2] = 0;
      bcc_compile(prog, str, code, 0, 1, 0);
      p = strstr(position, str);
      if((p && *p) && !bcc_in_string(prog, p)) return p;
      return position;
    } 
    return p;
  } 
  return NULL;
}

void bcc_compile_variables(char *prog, char var_type) {
  if(bcc_fail) return;
  char *p = prog;
  while(p && *p) p = bcc_compile_variable(prog, p, var_type);
}

/* Finds longest keyword  -------------------------------------------------- */
char *bcc_find_longest_keyword(char *prog, int t) {
  if(!prog || bcc_fail) {
    if(!bcc_fail) bcc_error(0, NULL, BP_ERROR_PROGRAM_GET);
    return NULL;
  }
  char *p = prog, *p2, *longest = NULL;
  unsigned char result = 0;
  do {
    unsigned char i = 0;
    p = strstr(p, t ? BP_FUN_DEF_HUMAN : BP_MACRO_DEF_HUMAN);
    if(!p || !*p) return longest;
    if(bcc_in_string(prog, p)) {
      ++p;
      continue;
    }
    p2 = p;
    if(BCC_IS_NUM(*p)) {
      bcc_error(
        bcc_line(prog, p), p, t ? BP_ERROR_FUNCTION_NAME : BP_ERROR_MACRO_NAME
      );
      return NULL;
    }
    while(BCC_IS_KEYWORD(*p)) p++;
    bcc_IGNORE_SUGAR(p);
    while((p && *p) && (t ? BCC_IS_KEYWORD(*p) : BCC_IS_CAP_KEYWORD(*p))) {
      i++;
      p++;
    }
    if(i > result) {
      longest = p2;
      result = i;
    }
    if(i >= BP_KEYWORD_MAX) {
      bcc_error(
        bcc_line(prog, p), p, t ? BP_ERROR_FUNCTION_NAME : BP_ERROR_MACRO_NAME
      );
      return NULL;
    }
  } while(*p && p);
  return longest;
}

/* Compiles a single user-defined function (longest name first):

Funtion parameters are stored at the end of the address space.
Each function uses the same addresses for its parameters consuming only
BP_PARAMS addresses for all parameters present in the program. ------------- */

int bcc_compile_function_step(char *prog) {
  if(!prog || bcc_fail) {
    if(!bcc_fail) bcc_error(0, NULL, BP_ERROR_PROGRAM_GET);
    return 0;
  }
  char fn_keyword[BP_KEYWORD_MAX] = {0}, fn_address[3];
  char *p = bcc_find_longest_keyword(prog, 1), *p2 = p, *p3 = NULL;
  unsigned char keyword_length = 0, f_id;
  if(p && *p) {
    f_id = bcc_fun_id;
    BCC_NEW_ADDR(bcc_fun_id);
    *(p++) = BP_FUN_DEF;
    *(p++) = bcc_fun_id;
    while(!BCC_SUGAR(p)) *(p++) = BP_SPACE;
    while(
      (++p && *p) && 
      (*p != BP_L_RPARENT) && 
      (keyword_length < (BP_KEYWORD_MAX - 1))
    ) {
      if(!BCC_SUGAR(p)) { // Ignore sugar postfix
        fn_keyword[keyword_length++] = *p;
        *p = BP_SPACE;
      }
    } // Remove commas from definition
    *p = BP_SPACE;
    while(p && *p && (*p != BP_R_RPARENT) || (*(p - 1) == BP_VAR_ADDR)) {
      if((*p == BP_COMMA) && !((*(p - 1)) == BP_VAR_ADDR)) *p = BP_SPACE;
      p++;
    } // Find the return keyword at the end of the function
    while((p = strstr(p, BP_RETURN_HUMAN)) && bcc_in_string(prog, p));
    if(p && *p) {
      while(*p && p && *p != BP_CR && *p != BP_LF) p++;
      fn_keyword[keyword_length] = 0;
      unsigned char count = 0;
      p3 = prog; // Delete the definition if the function is never called
      while(((p3 = strstr(p3 + 1, fn_keyword)) != NULL) && (count <= 1))
        if(!bcc_in_string(prog, p3)) count++;
      if(count <= 0) {
        while(p2 <= p) *(p2++) = BP_SPACE;
        bcc_fun_id = f_id;
        return 1;
      }
      bcc_stop = p; // Compile parameters
      bcc_var_id = BP_OFFSET + (BP_VARIABLES - BP_PARAMS) - 1;
      bcc_compile_variables(p2, BP_VAR_ADDR_HUMAN);
      bcc_find_end(prog);
      fn_address[0] = BP_FUNCTION;
      fn_address[1] = bcc_fun_id;
      fn_address[2] = 0; // Compile function calls
      bcc_compile(prog, fn_keyword, fn_address, BP_L_RPARENT, 1, '(');
      return 1;
    } bcc_error(0, NULL, BP_ERROR_RETURN);
  } 
  return 0;
}

void bcc_compile_functions(char *prog) {
  if(bcc_fail) return;
  while(bcc_compile_function_step(prog));
}

/* Compile for (inefficient compilation, each for gets a new address) ------ */
void bcc_compile_for(char *prog) {
  if(!prog || bcc_fail) {
    if(!bcc_fail) bcc_error(0, NULL, BP_ERROR_PROGRAM_GET);
    return;
  }
  char *p = prog, *p2 = prog;
  bcc_var_id = BP_OFFSET; // Reset variable address
  char c[2] = {BP_FOR, 0}; // While you find a for
  while((p = strstr(p, c))) {
    if(bcc_in_string(prog, p++)) continue;
    p2 = p;
    int8_t n = 0; // Find the end of the for
    while((++p && *p) && (n >= 0)) {
      if(BCC_IS_ADDR(*(p-1)) || bcc_in_string(prog, p)) continue;
      if(*p == BP_FOR) n++;
      if(*p == BP_NEXT) n--;
    }
    if(n != -1) {
      bcc_error(bcc_line(prog, p), p, BP_ERROR_NEXT);
      return;
    }
    bcc_stop = p; // compile for variables within this for
    bcc_compile_variable(p2, p2, BP_FOR_ADDR);
    p = p2;
  }
  bcc_find_end(prog); // remove variable type from for variable declaration
  bcc_compile(prog, c, c, BP_FOR_ADDR, 1, 0);
}

/* Pre-processor macros ---------------------------------------------------- */
int bcc_compile_macro(char *prog) {
  if(!prog || bcc_fail) {
    if(!bcc_fail) bcc_error(0, NULL, BP_ERROR_PROGRAM_GET);
    return 0;
  }
  char macro_name[BP_KEYWORD_MAX];
  char macro_code[BP_MACRO_MAX];
  char *p = bcc_find_longest_keyword(prog, 0);
  if(!p || !*p) return 0;
  while(BCC_IS_KEYWORD(*p)) *(p++) = BP_SPACE;
  bcc_IGNORE_SUGAR(p);
  unsigned int i;
  for(i = 0; BCC_IS_CAP_KEYWORD(*p) && (i < (BP_KEYWORD_MAX - 1)); i++) {
    macro_name[i] = *p;
    *(p++) = BP_SPACE;
  }
  macro_name[i] = 0;
  bcc_IGNORE_SUGAR(p);
  for(i = 0; p && *p && (i < (BP_MACRO_MAX - 1)); i++) {
    macro_code[i] = *p;
    *(p++) = BP_SPACE;
    if(!bcc_in_string(prog, p) && ((*p == BP_CR) || (*p == BP_LF))) break;
  }
  macro_code[++i] = 0;
  bcc_compile(prog, macro_name, macro_code, 0, 0, 0);
  if(bcc_find_longest_keyword(prog, 0)) return 1;
  return 0;
}

void bcc_compile_macros(char *prog) {
  if(bcc_fail) return;
  while(bcc_compile_macro(prog));
}

/* File inclusion (included files are copied at the end of the program. ---  */
char *bcc_compile_include(char *prog, char *pos) {
  if(!prog || !pos || bcc_fail) {
    if(!bcc_fail) bcc_error(0, NULL, BP_ERROR_PROGRAM_GET);
    return NULL;
  }
  char include_path[BP_INCLUDE_PATH_MAX];
  FILE *p_file;
  long p_size;
  uint32_t result;
  char *p = strstr(pos, BP_INCLUDE_DEF_HUMAN);
  if(!p || !*p) return NULL;
  if(bcc_in_string(pos, p)) return bcc_compile_include(prog, p + 1);
  while(BCC_IS_KEYWORD(*p)) *(p++) = BP_SPACE;
  bcc_IGNORE_SUGAR(p);
  *(p++) = BP_SPACE;
  unsigned int i;
  for(i = 0; (*p != BP_STRING) && (i < BP_INCLUDE_PATH_MAX); i++, p++) {
    include_path[i] = *p;
    *p = BP_SPACE;
  }
  include_path[i] = 0;
  *(p++) = BP_SPACE;
  p_file = fopen(include_path, "r");
  if(p_file == NULL) {
    bcc_error(bcc_line(prog, p), p, BP_ERROR_INCLUDE_PATH);
    return NULL;
  }
  fseek(p_file, 0, SEEK_END);
  p_size = ftell(p_file);
  rewind(p_file);
  if(p_size + strlen(prog) + 1 >= BCC_MAX_PROGRAM_SIZE) {
    bcc_error(0, NULL, BP_ERROR_PROGRAM_LENGTH);
  } else {
    result = fread(bcc_stop, 1, p_size, p_file);
    *(bcc_stop + p_size) = 0;
    if(result != p_size) {
      bcc_error(0, NULL, BP_ERROR_INCLUDE_READ);
      fclose(p_file);
      return NULL;
    }
  }
  fclose(p_file);
  bcc_find_end(prog);
  return p;
}

void bcc_compile_includes(char *prog) {
  if(bcc_fail) return;
  char *pos = prog;
  while(pos) pos = bcc_compile_include(prog, pos);
}

/* Pre-compilation checks -------------------------------------------------- */
int bcc_pre_compilation_checks(const char *prog) {
  if(bcc_fail) return bcc_fail;
  if(!bcc_check_delimeter(prog, BP_L_RPARENT, BP_R_RPARENT, 1))
    bcc_error(0, NULL, BP_ERROR_ROUND_PARENTHESIS);
  if(!bcc_check_delimeter(prog, BP_ACCESS, BP_ACCESS_END, 1))
    bcc_error(0, NULL, BP_ERROR_SQUARE_PARENTHESIS);
  if(!bcc_check_delimeter(prog, BP_STRING, BP_STRING, 1))
    bcc_error(0, NULL, BP_ERROR_STRING_END);
  return !bcc_fail;
}

/* Post-compilation checks ------------------------------------------------- */
void bcc_post_compilation_checks(const char *prog) {
  if(bcc_fail) return;
  if(!bcc_check_delimeter(prog, BP_IF, BP_ENDIF, 0))
    bcc_error(0, NULL, BP_ERROR_BLOCK);
  if(!bcc_check_delimeter(prog, BP_FUN_DEF, BP_RETURN, 0))
    bcc_error(0, NULL, BP_ERROR_RETURN);
  if((bcc_fun_id - BP_OFFSET) >= BP_FUN_MAX)
    bcc_error(0, NULL, BP_ERROR_FUNCTION_MAX);
  if((bcc_string_id - BP_OFFSET) >= BP_STRINGS)
    bcc_error(0, NULL, BP_ERROR_STRING_MAX);
  if((bcc_var_id - BP_OFFSET) >= BP_VARIABLES)
    bcc_error(0, NULL, BP_ERROR_VARIABLE_MAX);
}

/* Run compilation process ------------------------------------------------- */
int bcc_run(char *prog) {
  bcc_find_end(prog);
  bcc_remove_comments(prog);
  bcc_compile_includes(prog);
  bcc_remove_comments(prog);
  bcc_compile_macros(prog);
  bcc_compile(prog, "'\\''", "39", 0, 0, 0);
  bcc_compile_char_constants(prog);
  if(!bcc_pre_compilation_checks(prog)) return 0;
  bcc_compile_char(prog, BP_STR_ACC_HUMAN, BP_STR_ACC, 0, 0);
  bcc_compile_char(prog, BP_VAR_ACC_HUMAN, BP_VAR_ACC, 0, 0);
  bcc_compile_char(prog, BP_MEM_ACC_HUMAN, BP_MEM_ACC, 0, 0);
  bcc_compile_char(prog, BP_EQ_HUMAN, BP_EQ, 0, 0);
  bcc_compile_char(prog, BP_NOT_EQ_HUMAN, BP_NOT_EQ, 0, 0);
  bcc_compile_char(prog, BP_GTOEQ_HUMAN, BP_GTOEQ, 0, 0);
  bcc_compile_char(prog, BP_LTOEQ_HUMAN, BP_LTOEQ, 0, 0);
  bcc_compile_char(prog, BP_LOGIC_OR_HUMAN, BP_LOGIC_OR, 0, 0);
  bcc_compile_char(prog, BP_LOGIC_AND_HUMAN, BP_LOGIC_AND, 0, 0);
  bcc_compile_char(prog, BP_R_SHIFT_HUMAN, BP_R_SHIFT, 0, 0);
  bcc_compile_char(prog, BP_L_SHIFT_HUMAN, BP_L_SHIFT, 0, 0);
  bcc_compile_char(prog, "=", BP_SPACE, 0, 0);
  bcc_compile_char(prog, BP_INCREMENT_HUMAN, BP_INCREMENT, 0, 0);
  bcc_compile_char(prog, BP_DECREMENT_HUMAN, BP_DECREMENT, 0, 0);
  bcc_compile_char(prog, BP_BITWISE_NOT_HUMAN, BP_BITWISE_NOT, 0, 0);
  bcc_compile_functions(prog);
  bcc_var_id = BP_OFFSET;
  bcc_find_end(prog);
  bcc_compile_variables(prog, BP_GLOBAL_HUMAN);
  bcc_compile_variables(prog, BP_STR_ADDR);
  bcc_compile_char(prog, BP_RND_HUMAN, BP_RND, 0, 0);
  bcc_compile_char(prog, BP_MILLIS_HUMAN, BP_MILLIS, 0, 0);
  bcc_compile_char(prog, BP_DELAY_HUMAN, BP_DELAY, 0, 0);
  bcc_compile_char(prog, BP_SERIAL_HUMAN, BP_SERIAL, 0, 0);
  bcc_compile_char(prog, BP_CONTINUE_HUMAN, BP_CONTINUE, 0, 0);
  bcc_compile_char(prog, BP_RESTART_HUMAN, BP_RESTART, 0, 0);
  bcc_compile_char(prog, BP_RETURN_HUMAN, BP_RETURN, 0, 0);
  bcc_compile_char(prog, BP_SYSTEM_HUMAN, BP_SYSTEM, 0, 0);
  bcc_compile_char(prog, BP_CURSOR_HUMAN, BP_CURSOR, 0, 0);
  bcc_compile_char(prog, "locals:", BP_SPACE, 0, 0);
  bcc_compile_char(prog, BP_LTOA_HUMAN, BP_LTOA, 0, 0);
  bcc_compile_char(prog, BP_ATOL_HUMAN, BP_ATOL, 0, 0);
  bcc_compile_char(prog, BP_INPUT_HUMAN, BP_INPUT, 0, 0);
  bcc_compile_char(prog, BP_BREAK_HUMAN, BP_BREAK, 0, 0);
  bcc_compile_char(prog, BP_PRINT_HUMAN, BP_PRINT, 0, 0);
  bcc_compile_char(prog, BP_WHILE_HUMAN, BP_WHILE, 0, 0);
  bcc_compile_char(prog, BP_ENDIF_HUMAN, BP_ENDIF, 0, 0);
  bcc_compile_char(prog, BP_SIZEOF_HUMAN, BP_SIZEOF, 0, 0);
  bcc_compile_char(prog, BP_WRITE_HUMAN, BP_WRITE, 0, 0);
  bcc_compile_char(prog, BP_INDEX_HUMAN, BP_INDEX, 0, 0);
  bcc_compile_char(prog, BP_CLOSE_HUMAN, BP_CLOSE, 0, 0);
  bcc_compile_char(prog, BP_READ_HUMAN, BP_READ, 0, 0);
  bcc_compile_char(prog, BP_OPEN_HUMAN, BP_OPEN, 0, 0);
  bcc_compile_char(prog, BP_NEXT_HUMAN, BP_NEXT, 0, 0);
  bcc_compile_char(prog, BP_FILE_HUMAN, BP_FILE, 0, 0);
  bcc_compile_char(prog, BP_CHAR_HUMAN, BP_CHAR, 0, 0);
  bcc_compile_char(prog, BP_ELSE_HUMAN, BP_ELSE, 0, 0);
  bcc_compile_char(prog, BP_END_HUMAN, BP_END, 0, 0);
  bcc_compile_char(prog, BP_FOR_HUMAN, BP_FOR, 0, 0);
  bcc_compile_char(prog, BP_ADC_HUMAN, BP_ADC, 0, 0);
  bcc_compile(prog, "args[", "S", 0, 0, 0);
  bcc_compile_char(prog, "step", BP_COMMA, 0, 0);
  bcc_compile(prog, "not", "1-", 0, 0, 0);
  bcc_compile_char(prog, BP_IF_HUMAN, BP_IF, 0, 0);
  bcc_compile_char(prog, BP_IO_HUMAN, BP_IO, 0, 0);
  bcc_compile_char(prog, BP_TO_HUMAN, BP_COMMA, 0, 0);
  bcc_compile_for(prog);
  bcc_compile(prog, "OUTPUT", "1", 0, 0, 0);
  bcc_compile(prog, "INPUT", "0", 0, 0, 0);
  bcc_compile(prog, "HIGH", "1", 0, 0, 0);
  bcc_compile(prog, "LOW", "0", 0, 0, 0);
  bcc_compile(prog, "EOF", "-1", 0, 0, 0);
  bcc_compile(prog, "false", "0", 0, 0, 0);
  bcc_compile(prog, "true", "1", 0, 0, 0);
  bcc_compile(prog, "LF", "10", 0, 0, 0);
  bcc_compile(prog, "CR", "13", 0, 0, 0);
  bcc_remove(prog, BP_CR, BP_LF, BP_SPACE, BP_TAB);
  bcc_post_compilation_checks(prog);
  bcc_var_id = BP_OFFSET, bcc_string_id = BP_OFFSET + BP_ARGS, bcc_fun_id = BP_OFFSET;
  return !bcc_fail;
};