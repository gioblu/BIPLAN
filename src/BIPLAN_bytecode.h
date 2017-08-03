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

// BIPLAN symbol sign
#define BPBC_SIGN   0B10000000

/* BIPLAN byte code ----------------------------------------------------------
   BPBC = BIPLAN BYTE CODE --------------------------------------------------
   --------------------------------------------------------------------------*/
#define BPBC_RST    0 | BPBC_SIGN // Reset
#define BPBC_CLR    1 | BPBC_SIGN // Clears the current program
#define BPBC_DIE    2 | BPBC_SIGN // Stops program execution
#define BPBC_RUN    3 | BPBC_SIGN // Starts program execution
#define BPBC_MEM    4 | BPBC_SIGN // Memory stats
#define BPBC_LIST   5 | BPBC_SIGN // List files in memory
#define BPBC_LOAD   6 | BPBC_SIGN // Load file from memory
#define BPBC_PUSH   7 | BPBC_SIGN // Load and run program from memory
#define BPBC_SAVE   8 | BPBC_SIGN // Save file on memory
#define BPBC_SVMEM  9 | BPBC_SIGN // Save value in memory
#define BPBC_RDMEM 10 | BPBC_SIGN // Read value from memory
#define BPBC_PRINT 11 | BPBC_SIGN // Print
/* BIPLAN Operands -----------------------------------------------------------
   --------------------------------------------------------------------------
   --------------------------------------------------------------------------*/
#define BPBC_DIV   12 | BPBC_SIGN // /
#define BPBC_MUL   13 | BPBC_SIGN // *
#define BPBC_SUB   14 | BPBC_SIGN // -
#define BPBC_ADD   15 | BPBC_SIGN // +
#define BPBC_MOD   16 | BPBC_SIGN // %
#define BPBC_SQR   17 | BPBC_SIGN // sqrt
#define BPBC_POW   18 | BPBC_SIGN // pow
#define BPBC_ABS   19 | BPBC_SIGN // abs
#define BPBC_AVG   20 | BPBC_SIGN // Average
#define BPBC_WAVG  21 | BPBC_SIGN // Weighted average
/* BIPLAN Operators ----------------------------------------------------------
   --------------------------------------------------------------------------
   --------------------------------------------------------------------------*/
#define BPBC_LT    22 | BPBC_SIGN // <
#define BPBC_ELT   23 | BPBC_SIGN // <=
#define BPBC_GT    24 | BPBC_SIGN // >
#define BPBC_EGT   25 | BPBC_SIGN // >=
#define BPBC_EQL   26 | BPBC_SIGN // =
#define BPBC_NEQ   27 | BPBC_SIGN // !=
#define BPBC_OR    28 | BPBC_SIGN // ||
#define BPBC_AND   29 | BPBC_SIGN // &&
#define BPBC_NOT   30 | BPBC_SIGN // !
/* BIPLAN Statements ---------------------------------------------------------
   --------------------------------------------------------------------------
   --------------------------------------------------------------------------*/
#define BPBC_VAR   31 | BPBC_SIGN // var
#define BPBC_IF    32 | BPBC_SIGN // if
#define BPBC_WHILE 33 | BPBC_SIGN // while
#define BPBC_FOR   34 | BPBC_SIGN // for
#define BPBC_END   35 | BPBC_SIGN // block end
#define BPBC_GOTO  36 | BPBC_SIGN // goto
#define BPBC_GOTOF 37 | BPBC_SIGN // goto function
#define BPBC_RET   38 | BPBC_SIGN // return
#define BPBC_BRE   39 | BPBC_SIGN // break
#define BPBC_BOU   40 | BPBC_SIGN // bounce or continue
#define BPBC_COMM  41 | BPBC_SIGN // // comment
/* BIPLAN Constants ----------------------------------------------------------
   --------------------------------------------------------------------------
   --------------------------------------------------------------------------*/
#define BPBC_HI    42 | BPBC_SIGN // HIGH
#define BPBC_LO    43 | BPBC_SIGN // LOW
#define BPBC_IN    44 | BPBC_SIGN // INPUT
#define BPBC_INPU  45 | BPBC_SIGN // INPUT PULL UP
#define BPBC_INPD  46 | BPBC_SIGN // INPUT PULL DOWN
#define BPBC_OU    47 | BPBC_SIGN // OUTPUT
#define BPBC_TRUE  48 | BPBC_SIGN // true
#define BPBC_FALSE 49 | BPBC_SIGN // false
#define BPBC_PI    50 | BPBC_SIGN // Pi
/* BIPLAN Methods ------------------------------------------------------------
   ------------------------------------------------------------------------- */
// Random -------------------------------------------------------------------
#define BPBC_RAND  51 | BPBC_SIGN // Random
#define BPBC_RANDS 52 | BPBC_SIGN // Random seed
// Timing --------------------------------------------------------------------
#define BPBC_DMIL  53 | BPBC_SIGN // Delay milliseconds
#define BPBC_DMIC  54 | BPBC_SIGN // Delay microseconds
#define BPBC_MIL   55 | BPBC_SIGN // returns milliseconds from startup
#define BPBC_MIC   56 | BPBC_SIGN // returns microseconds from startup
// IO pin handling -----------------------------------------------------------
#define BPBC_DSET  57 | BPBC_SIGN // digitalWrite
#define BPBC_DGET  58 | BPBC_SIGN // digitalRead
#define BPBC_DMODE 59 | BPBC_SIGN // pinMode
#define BPBC_AREAD 60 | BPBC_SIGN // analogRead
#define BPBC_ASET  61 | BPBC_SIGN // analogWrite
// Serial --------------------------------------------------------------------
#define BPBC_SERB  62 | BPBC_SIGN // Serial begin
#define BPBC_SERP  63 | BPBC_SIGN // Serial print
#define BPBC_SERR  64 | BPBC_SIGN // Serial read
#define BPBC_SERA  65 | BPBC_SIGN // Serial available
#define BPBC_SERF  66 | BPBC_SIGN // Serial flush
// EEPROM --------------------------------------------------------------------
#define BPBC_ECLR  67 | BPBC_SIGN // Clear EEPROM
#define BPBC_EGET  68 | BPBC_SIGN // Read EEPROM
#define BPBC_ESET  69 | BPBC_SIGN // Write EEPROM
// Ethernet ------------------------------------------------------------------
#define BPBC_ETIP  70 | BPBC_SIGN // Ethernet IP
#define BPBC_ETMA  71 | BPBC_SIGN // Ethernet maintain
#define BPBC_ETSV  72 | BPBC_SIGN // Ethernet server instantiation
#define BPBC_ETSB  73 | BPBC_SIGN // Ethernet server begin
#define BPBC_ETSA  74 | BPBC_SIGN // Ethernet server available
#define BPBC_ETSP  75 | BPBC_SIGN // Ethernet server print
#define BPBC_ETCL  76 | BPBC_SIGN // Ethernet client instantiation
#define BPBC_ETCB  77 | BPBC_SIGN // Ethernet client begin
#define BPBC_ETCA  78 | BPBC_SIGN // Ethernet client available
#define BPBC_ETCP  79 | BPBC_SIGN // Ethernet client print
#define BPBC_ETCR  80 | BPBC_SIGN // Ethernet client read
#define BPBC_ETCC  81 | BPBC_SIGN // Ethernet client connect
#define BPBC_ETCCD 82 | BPBC_SIGN // Ethernet client connected
#define BPBC_ETCF  83 | BPBC_SIGN // Ethernet client flush
#define BPBC_ETCS  84 | BPBC_SIGN // Ethernet client stop
// Tones ---------------------------------------------------------------------
#define BPBC_TONE  85 | BPBC_SIGN // Sound tone
#define BPBC_TONET 86 | BPBC_SIGN // Sound tone with duration
#define BPBC_TONED 87 | BPBC_SIGN // Kill all tones
