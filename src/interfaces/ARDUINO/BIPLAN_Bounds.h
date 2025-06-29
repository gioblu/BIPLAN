
/* BIPLAN maximum program size --------------------------------------------- */

#ifndef BP_MAX_PROGRAM_SIZE
  #define BCC_MAX_PROGRAM_SIZE 500
#endif

/* Memory size in bytes ---------------------------------------------------- */

#ifndef BP_MEM_SIZE
  #define BP_MEM_SIZE 128
#endif

/* Variable type (supported: int, long) ------------------------------------ */

#ifndef BP_VAR_T
  #define BP_VAR_T long
#endif

#ifndef BP_VAR_MAX
  #define BP_VAR_MAX (BP_VAR_T)((unsigned BP_VAR_T) ~ 0 >> 1)
#endif

/* Maximum length of keywords ---------------------------------------------- */

#ifndef BP_KEYWORD_MAX
  #define BP_KEYWORD_MAX 10
#endif

/* Maximum amount of files ------------------------------------------------- */

#ifndef BP_FILES_MAX
  #define BP_FILES_MAX 1
#endif

/* ASCII addresses offset (avoid the first 34 ASCII characters) ------------ */

#ifndef BP_OFFSET
  #define BP_OFFSET 35
#endif

/* Maximum amount of variables is 91 (87 effectively used). The end of the 
   variable address-space is used by parameters and for variables. Consider
   that the function parameters are stored in the same address space, so the 
   amount of user-defined global variables is: 87 - BP_PARAMS -------------- */

#ifndef BP_VARIABLES
  #define BP_VARIABLES 30
#endif

/* Maximum amount of for variables is 91 (87 effectively used). For now for 
   variables addressess are compiled infecciently, Each gets a new address.  */

#ifndef BP_FOR_VARIABLES
  #define BP_FOR_VARIABLES 25
#endif

/* Maximum amount of program arguments ------------------------------------- */
#ifndef BP_ARGS
  #define BP_ARGS 5
#endif

/* Maximum amount of strings is 91 (87 effectively used). Consider that the 
   program arguments are stored in the same address space, so the 
   amount of user-defined strings is: 87 - BP_ARGS ------------------------- */

#ifndef BP_STRINGS
  #define BP_STRINGS 10 - BP_ARGS
#endif

/* Maximum amount of characters in a macro --------------------------------- */

#ifndef BP_MACRO_MAX
  #define BP_MACRO_MAX 50
#endif

/* Maximum amount of functions is 91 (87 effectively used) ----------------- */

#ifndef BP_FUN_MAX
  #define BP_FUN_MAX 10
#endif

/* Maximum amount of parameters -------------------------------------------- */

#ifndef BP_PARAMS
  #define BP_PARAMS 5
#endif

/* Maximum amount of nested function calls --------------------------------- */

#ifndef BP_FUN_DEPTH
  #define BP_FUN_DEPTH 20
#endif

/* Maximum length of a number (represented as a string) -------------------- */

#ifndef BP_NUM_MAX
  #define BP_NUM_MAX 20 // Handle 64 bits machine limit
#endif

/* Maximum length of a string. --------------------------------------------- */

#ifndef BP_STRING_MAX
  #define BP_STRING_MAX 20
#endif

/* Maximum amount of nested cycles (for, while) ---------------------------- */

#ifndef BP_CYCLE_DEPTH
  #define BP_CYCLE_DEPTH 10
#endif

/* Maximum length of paths passed to include ------------------------------- */

#ifndef BP_INCLUDE_PATH_MAX
  #define BP_INCLUDE_PATH_MAX 50
#endif
