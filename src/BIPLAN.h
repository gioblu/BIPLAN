
/* BIPLAN CR.1 (Byte coded Interpreted Programming Language)

      _____              _________________________
     |   | |            |_________________________|
     |   | |_______________||__________   \___||_________ |
   __|___|_|               ||          |__|   ||     |   ||
  /________|_______________||_________________||__   |   |D
    (O)                 |_________________________|__|___/|
                                           \ /            |
                                           (O)

  Giovanni Blu Mitolo 2017-2026 - gioscarab@gmail.com
  BIP bytecode interpreter */

#pragma once
#include "BIPLAN_Defines.h"
#include "BIPLAN_Decoder.h"

/* DEFINITIONS ------------------------------------------------------------- */

BP_FUN_T bool bip_run();

void bip_restart_call();

void bip_error(char *position, const char *string);

void bip_end_call();

void bip_index_definitions(char* program);

void bip_process_labels(char* program);

void bip_process_argument(char *a);

BP_VAR_T bip_get_file_id();

void bip_init(char *, bip_error_t, BPM_PRINT_T, BPM_INPUT_T, BPM_SERIAL_T);

void bip_set_default();

#ifdef BIP_JUMP_TABLE
static void bip_statement_jump_table();
#endif

BP_FUN_T bool bip_ignore(char c);

BP_FUN_T BP_VAR_T bip_get_variable(int n);

BP_FUN_T char bip_string_char(int s, int c);

BP_FUN_T BP_VAR_T bip_var_factor();

BP_FUN_T BP_VAR_T bip_access(BP_VAR_T v);

BP_FUN_T BP_VAR_T bip_factor();

BP_FUN_T BP_VAR_T bip_term();

BP_FUN_T BP_VAR_T bip_expression();

BP_FUN_T BP_VAR_T bip_relation();

BP_FUN_T void bip_read_string(char *s);

void bip_print_call();

BP_FUN_T void bip_skip_block();

BP_FUN_T void bip_if_call();

void bip_string_assignment_call();

void bip_mem_assignment_call();

BP_FUN_T BP_VAR_T bip_return_call();

BP_FUN_T BP_VAR_T bip_function_call();

BP_FUN_T void bip_next_call();

BP_FUN_T void bip_var_addr_call();

void bip_continue_call();

void bip_break_call();

void bip_for_call();

void bip_while_call();

char input_call();

BP_VAR_T bip_io_get_call();

void bip_io_set_call();

BP_VAR_T bip_adc_call();

void bip_pinMode_call();

BP_VAR_T bip_random_call();

BP_VAR_T bip_result_get_call();

void bip_result_set_call();

BP_VAR_T bip_serial_call();

BP_VAR_T bip_file_get_call();

void bip_file_set_call();

BP_VAR_T bip_sizeof_call();

BP_VAR_T bip_pipe_call(BP_VAR_T v);

BP_VAR_T bip_atol_call(BP_VAR_T v);

void bip_ltoa_call();

void bip_statement();
