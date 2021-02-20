
// For printf and file used below
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <BIPLAN.h>

#define BCC_MAX_PROGRAM_SIZE 2000
char program[BCC_MAX_PROGRAM_SIZE];
BIPLAN_Interpreter interpreter;

bool error = false;

void error_callback(char *position, const char *string) {
  printf("\nerror: ");
  printf(" %s ", string);
  if(position) {
    printf(" ");
    printf(" %c ", *position);
    printf(" at position ");
    //printf(" %d \n ", position - interpreter.program_start);
  }
  error = true;
};

int main(int argc, char* argv[]) {
  printf("BIPLAN interpreter - Giovanni Blu Mitolo 2021 \n");
  // Serial initialization
  int s;
  if(argc == 5) {
    s = serialOpen(argv[3], atoi(argv[4]));
    if(int(s) < 0) printf("Serial fail!\n");
    else printf("Serial OK.\n");
  }
  printf("Source: %s", argv[1]);
  fflush(stdout);
  FILE * pFile;
  long lSize;
  size_t result;
  // Open file
  pFile = fopen(argv[1], "r");
  if(pFile == NULL) {
    fputs("\nFile error", stderr);
    exit(1);
  }
  // Obtain file size:
  fseek(pFile, 0, SEEK_END);
  lSize = ftell(pFile);
  rewind(pFile);
  printf("\nSource length: ");
  std::cout << lSize;
  printf("B \n");
  if((sizeof(char) * lSize) >= BCC_MAX_PROGRAM_SIZE) {
    fputs(" Program too big, configure BCC_MAX_PROGRAM_SIZE. ", stderr);
    exit(2);
  }
  // Copy the file into the buffer:
  result = fread(program, 1, lSize, pFile);
  if(result != lSize) {
    fputs("\nReading error ", stderr);
    exit(3);
  }
  // terminate
  fclose(pFile);
  // Initialize interpreter using cout as print and stdin as input
  interpreter.initialize(program, error_callback, s, s, s);
  // Check for compilation errors

  if(error) {
    interpreter.ended = true;
    printf("\nFix your code and retry.");
  }

  uint32_t t = BPM_MICROS();
  printf("\nInterpreter output: \n\n");
  while(interpreter.run());
  t = BPM_MICROS() - t;
  printf("\n\nExecution duration: %u microseconds \n", t);
  return 0;
};
