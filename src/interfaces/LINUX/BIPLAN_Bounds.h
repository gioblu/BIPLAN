
/* BIPLAN maximum program size --------------------------------------------- */

#ifndef BP_MAX_PROGRAM_SIZE
  #define BCC_MAX_PROGRAM_SIZE 65536
#endif

/* BIPLAN memory size ------------------------------------------------------ */

#ifndef BP_MEM_SIZE
  #define BP_MEM_SIZE 65536
#endif

/* Variable type, change if required (signed only) ------------------------- */

#ifndef BP_VAR_T
  #define BP_VAR_T long
#endif

#ifndef BP_VAR_MAX
  #define BP_VAR_MAX (BP_VAR_T)((unsigned BP_VAR_T) ~ 0 >> 1)
#endif

/* Keyword maximum length -------------------------------------------------- */

#ifndef BP_KEYWORD_MAX
  #define BP_KEYWORD_MAX 20
#endif

/* Files maximum amount ---------------------------------------------------- */

#ifndef BP_FILES_MAX
  #define BP_FILES_MAX 10
#endif

/* ASCII addresses offset (avoid the first 34 ASCII characters) ------------ */

#ifndef BP_OFFSET
  #define BP_OFFSET 35
#endif

/* Variables amount, max 91 - BP_PARAMS - BP_CYCLE_DEPTH ------------------- */

#ifndef BP_VARIABLES
  #define BP_VARIABLES 91
#endif

/* Strings amount, set higher if required (max 91 - BP_ARGS) --------------- */

#ifndef BP_STRINGS
  #define BP_STRINGS 86
#endif

/* Preprocessor macros maximum length -------------------------------------- */

#ifndef BP_MACRO_MAX
  #define BP_MACRO_MAX 255
#endif

/* Program arguments amount, set higher if required (max 88 - BP_STRINGS) */
/* handle args: https://www.thegeekstuff.com/2013/01/c-argc-argv/ */
#ifndef BP_ARGS
  #define BP_ARGS 5
#endif

/* Functions amount, set higher if required (max 91) ----------------------- */

#ifndef BP_FUN_MAX
  #define BP_FUN_MAX 91
#endif

/* Function parameters amount, set higher if required ---------------------- */

#ifndef BP_PARAMS
  #define BP_PARAMS 10
#endif

/* Function call maximum depth, set higher if required --------------------- */

#ifndef BP_FUN_DEPTH
  #define BP_FUN_DEPTH 100
#endif

/* Maximum length of a number (represented as a string) -------------------- */

#ifndef BP_NUM_MAX
  #define BP_NUM_MAX 20 // Handle 64 bits machine limit
#endif

/* String maximum length, set higher if required --------------------------- */

#ifndef BP_STRING_MAX
  #define BP_STRING_MAX 100
#endif

/* Cycle (for, while) maximum depth, set higher if required ---------------- */

#ifndef BP_CYCLE_DEPTH
  #define BP_CYCLE_DEPTH 10
#endif

/* Maximum length of the path used by include ------------------------------ */

#ifndef BP_INCLUDE_PATH_MAX
  #define BP_INCLUDE_PATH_MAX 256
#endif

/* Number of digit after the comma ----------------------------------------- */

#ifndef BP_FIXED_P
  #define BP_FIXED_P 1000
#endif

