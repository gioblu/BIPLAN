/*
   ______     ______           ______   _
  |      | | |      | |              | | \    |
  |_____/  | |______| |        ______| |  \   |
  |     \  | |        |       |      | |   \  |
  |______| | |        |______ |______| |    \_|

  Byte coded Interpreted Programming Language
  Giovanni Blu Mitolo 2017 - gioscarab@gmail.com

        _____              _________________________
       |     |            |_________________________|
       |     |_______________||__________    ___||_________ |
     __|_____|               ||          |__|   ||         ||
    /________|_______________||_________________||__       |D
      o                   |_________________________|______/|
                                             \ /            |
                                              O

  BIPLAN Copyright (c) 2017, Giovanni Blu Mitolo All rights reserved.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License. */

const static unsigned char keywords[] PROGMEM = {
  // BIPLAN BASIC COMMANDS ---------------------------------------------------
  'r','e','s','e','t'         | BPBC_SIGN, BPBC_RST,
  'c','l','e','a','r'         | BPBC_SIGN, BPBC_CLR,
  'd','i','e'                 | BPBC_SIGN, BPBC_DIE,
  'r','u','n'                 | BPBC_SIGN, BPBC_RUN,
  'm','e','m'                 | BPBC_SIGN, BPBC_MEM,
  'l','i','s','t'             | BPBC_SIGN, BPBC_LIST
  'l','o','a','d'             | BPBC_SIGN, BPBC_LOAD,
  'p','u','s','h'             | BPBC_SIGN, BPBC_PUSH,
  's','a','v','e'             | BPBC_SIGN, BPBC_SAVE,
  's','t','o','r','e'         | BPBC_SIGN, BPBC_SVMEM,
  'p','i','c','k'             | BPBC_SIGN, BPBC_RDMEM,
  'p','r','i','n','t'         | BPBC_SIGN, BPBC_PRINT,
  // BIPLAN OPERANDS ---------------------------------------------------------
  '/'                         | BPBC_SIGN, BPBC_DIV,
  '*'                         | BPBC_SIGN, BPBC_MUL,
  '-'                         | BPBC_SIGN, BPBC_SUB,
  '+'                         | BPBC_SIGN, BPBC_ADD,
  '%'                         | BPBC_SIGN, BPBC_MOD,
  's','q','r','t'             | BPBC_SIGN, BPBC_SQR,
  'p','o','w'                 | BPBC_SIGN, BPBC_POW,
  'a','b','s'                 | BPBC_SIGN, BPBC_ABS,
  'a','v','g'                 | BPBC_SIGN, BPBC_AVG,
  'w','a','v','g'             | BPBC_SIGN, BPBC_WAVG,
  // BIPLAN OPERATORS --------------------------------------------------------
  '<'                         | BPBC_SIGN, BPBC_LT,
  '<='                        | BPBC_SIGN, BPBC_ELT,
  '>'                         | BPBC_SIGN, BPBC_GT,
  '>='                        | BPBC_SIGN, BPBC_EGT,
  '='                         | BPBC_SIGN, BPBC_EQL,
  '!='                        | BPBC_SIGN, BPBC_NEQ,
  '||'                        | BPBC_SIGN, BPBC_OR,
  '&&'                        | BPBC_SIGN, BPBC_AND,
  '!'                         | BPBC_SIGN, BPBC_NOT,
  // BIPLAN STATEMENTS -------------------------------------------------------
  'v','a','r'                 | BPBC_SIGN, BPBC_VAR,
  'i','f'                     | BPBC_SIGN, BPBC_IF,
  'w','h','i','l','e'         | BPBC_SIGN, BPBC_WHILE,
  'f','o','r'                 | BPBC_SIGN, BPBC_FOR,
  'e','n','d'                 | BPBC_SIGN, BPBC_END,
  'j','u','m','p'             | BPBC_SIGN, BPBC_GOTO,
  'j','u','m','p','f'         | BPBC_SIGN, BPBC_GOTOF,
  'r','e','t','u','r','n'     | BPBC_SIGN, BPBC_RET,
  'b','r','e','a','k'         | BPBC_SIGN, BPBC_BRE,
  'b','o','u','n','c','e'     | BPBC_SIGN, BPBC_BOU,
  '/','/'                     | BPBC_SIGN, BPBC_COMM,
  // RANDOM ------------------------------------------------------------------
  'r','a','n','d'             | BPBC_SIGN, BPBC_RAND,
  's','r','a','n','d'         | BPBC_SIGN, BPBC_RANDS,
  // TIMING ------------------------------------------------------------------
  'd','m','i','l','l','i','s' | BPBC_SIGN, BPBC_DMIL,
  'd','m','i','c','r','o','s' | BPBC_SIGN, BPBC_DMIC,
  'm','i','l','l','i','s'     | BPBC_SIGN, BPBC_MIL,
  'm','i','c','r','o','s'     | BPBC_SIGN, BPBC_MIC,
  // PIN HANDLING ------------------------------------------------------------
  'd','s','e','t'             | BPBC_SIGN, BPBC_DSET,
  'd','g','e','t'             | BPBC_SIGN, BPBC_DGET,
  'd','m','o','d','e'         | BPBC_SIGN, BPBC_DMODE,
  'a','g','e','t'             | BPBC_SIGN, BPBC_AREAD,
  'a','s','e','t'             | BPBC_SIGN, BPBC_ASET,
  // SERIAL PORT HANDLING ----------------------------------------------------
  's','i','n','i','t'         | BPBC_SIGN, BPBC_SERB,
  's','p','r','i','n','t'     | BPBC_SIGN, BPBC_SERP,
  's','g','e','t'             | BPBC_SIGN, BPBC_SERR,
  's','g','o','t'             | BPBC_SIGN, BPBC_SERA,
  's','w','a','i','t'         | BPBC_SIGN, BPBC_SERF,
  // BIPLAN EEPROM HANDLING --------------------------------------------------
  'e','c','l','r'             | BPBC_SIGN, BPBC_ECLR,
  'e','g','e','t'             | BPBC_SIGN, BPBC_EGET,
  'e','s','e','t'             | BPBC_SIGN, BPBC_ESET,
  // BIPLAN BUILT IN AUDIO HANDLING ------------------------------------------
  't','o','n','e'             | BPBC_SIGN, BPBC_TONE,
  't','o','n','e','t'         | BPBC_SIGN, BPBC_TONET,
  't','o','n','e','d'         | BPBC_SIGN, BPBC_TONED,
};
