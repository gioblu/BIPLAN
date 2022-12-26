
// For printf and file used below
#include <inttypes.h>
//#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <BCC.h>

char program[BCC_MAX_PROGRAM_SIZE];
BCC compiler;

void error_callback(char *position, const char *string) {
  printf("\033[0;31m\nCompilation error: ");
  printf("%s", string);
};

int main(int argc, char* argv[]) {
  printf("\033[0;36m\nBCC (BIP Compiler Collection) compiler \nGiovanni Blu Mitolo 2022 \n\n");
  printf("Source:\033[0;32m %s \033[0;36m", argv[1]);
  printf("Target:\033[0;32m %s \033[0;36m \n", argv[2]);
  FILE * p_file;
  long p_size;
  size_t result;
  // Open file
  p_file = fopen(argv[1], "r");
  if(p_file == NULL) {
    printf("\033[0;31m\nUnable to open the source file.\n");
    exit(-3);
  }
  // Obtain file size:
  fseek(p_file, 0, SEEK_END);
  p_size = ftell(p_file);
  rewind(p_file);
  printf("BIPLAN size: \033[0;32m");
  std::cout << p_size;
  printf("B\033[0;36m");
  if((sizeof(char) * p_size) >= BCC_MAX_PROGRAM_SIZE) {
    printf("\033[0;31m\nProgram too big, configure BCC_MAX_PROGRAM_SIZE.");
    exit(-2);
  }
  // Copy the file into the buffer:
  result = fread(program, 1, p_size, p_file);
  if(result != p_size) {
    printf("\033[0;31m\nUnable to read source file.");
    exit(-1);
  }
  // Close source file
  fclose(p_file);
  // Compile program
  compiler.error_callback = error_callback;
  uint32_t t = BPM_MICROS();
  if(!compiler.run(program)) {
    printf("\033[0;31m\nCompilation failed: check your code and retry\n\n");
    exit(0);
  }
  t = BPM_MICROS() - t;
  // Save program in target file
  FILE *o_file = fopen(argv[2], "w");
  fwrite(program, sizeof(char), strlen(program), o_file);
  // Obtain file size:
  fseek(o_file, 0, SEEK_END);
  int o_size = ftell(o_file);
  rewind(o_file);
  printf(", BIP size: \033[0;32m");
  std::cout << o_size;
  printf("B\033[0;36m, reduction: \033[0;32m%f", (100 - (100 / ((float)p_size / (float)o_size))));
  fclose(o_file);
  printf("%% \033[0;36m \nCompilation time:\033[0;32m %d microseconds \n \n\033[0m", (int)(t));
  exit(1);
};
