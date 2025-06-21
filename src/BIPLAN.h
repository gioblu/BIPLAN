
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
  BIP bytecode interpreter */

#pragma once
#include "BIPLAN_Defines.h"
#include "BIPLAN_Decoder.h"

/* DEFINITIONS ------------------------------------------------------------- */

static bool bip_run();

void bip_restart_call();

void bip_error(char *position, const char *string);

void bip_end_call();

void bip_index_definitions(char* program);

void bip_process_labels(char* program);

void bip_process_argument(char *a);

BP_VAR_T bip_get_file_id();

void bip_init(char *, bip_error_t, BPM_PRINT_T, BPM_INPUT_T, BPM_SERIAL_T);

void bip_set_default();

static bool bip_ignore(char c);

static BP_VAR_T bip_get_variable(int n);

static char bip_string_char(int s, int c);

static BP_VAR_T bip_var_factor();

static BP_VAR_T bip_access(BP_VAR_T v);

static BP_VAR_T bip_factor();

static BP_VAR_T bip_term();

static BP_VAR_T bip_expression();

static BP_VAR_T bip_relation();

void bip_read_string(char *s, uint16_t o);

void bip_print_call();

void bip_skip_block();

void bip_if_call();

void bip_string_assignment_call();

void bip_mem_assignment_call();

static BP_VAR_T bip_return_call();

static BP_VAR_T bip_function_call();

static void bip_next_call(); 

static void bip_var_addr_call();

void bip_continue_call();

void bip_break_call();

void bip_for_call();

void bip_while_call();

char input_call();

BP_VAR_T bip_io_get_call();

BP_VAR_T bip_adc_call();

void bip_pinMode_call();

BP_VAR_T bip_random_call();

BP_VAR_T bip_result_get_call();

void bip_result_set_call();

BP_VAR_T bip_serial_call();

BP_VAR_T bip_file_get_call();

BP_VAR_T bip_sizeof_call();

BP_VAR_T bip_system_call(BP_VAR_T v);

BP_VAR_T bip_atol_call(BP_VAR_T v);

void bip_ltoa_call();

void bip_statement();
