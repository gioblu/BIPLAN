
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
  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License. */

#pragma once
#include "BIPLAN_Defines.h"
#include "BIPLAN_Decoder.h"

/* DEFINITIONS ------------------------------------------------------------- */

bool bip_finished();

bool bip_run();

void bip_restart_call();

void bip_error(char *position, const char *string);

void bip_end_call();

void bip_index_definitions(char* program);

void bip_process_labels(char* program);

BP_VAR_T bip_get_file_id();

void bip_init(char *, bip_error_t, BPM_PRINT_T, BPM_INPUT_T, BPM_SERIAL_T);

void bip_set_default();

bool bip_ignore(char c);

BP_VAR_T bip_get_variable(int n);

char bip_string_char(int s, int c);

BP_VAR_T bip_var_factor();

BP_VAR_T bip_access(BP_VAR_T v);

BP_VAR_T bip_factor();

BP_VAR_T bip_term();

BP_VAR_T bip_expression();

BP_VAR_T bip_relation();

void bip_jump_call();

void bip_read_string(char *s);

void bip_print_call();

void bip_skip_block();

void bip_if_call();

void bip_variable_assignment_call();

void bip_string_assignment_call();

void bip_mem_assignment_call();

BP_VAR_T bip_return_call();

BP_VAR_T bip_function_call();

void bip_continue_call();

void bip_break_call();

void bip_for_call();

void bip_label_call();

void bip_next_call();

void bip_while_call();

BP_VAR_T bip_io_call();

BP_VAR_T bip_adc_call();

void bip_pinMode_call();

BP_VAR_T bip_random_call();

BP_VAR_T bip_result_get_call();

void bip_result_set_call();

BP_VAR_T bip_serial_call();

BP_VAR_T bip_system_call();

BP_VAR_T bip_file_get_call();

BP_VAR_T bip_sizeof_call();

BP_VAR_T bip_atol_call();

void bip_statement();
