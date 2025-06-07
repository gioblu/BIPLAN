
// For printf and file used below
#include <inttypes.h>
//#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <BCC.h>

#define MAX_ERROR_SOURCE 25

char program[BCC_MAX_PROGRAM_SIZE];
BCC compiler;

void error_callback(char *position, const char *string) {
  printf("\nCompilation error: %s", string);
  printf("\nSee: %.*s ... \nLength: %ld", (int)((strlen(position) > MAX_ERROR_SOURCE) ? MAX_ERROR_SOURCE : strlen(position)), position, strlen(position));
  exit(-4);
};

int main(int argc, char* argv[]) {
  printf("BCC (BIP Compiler Collection) Giovanni Blu Mitolo 2025 \n");
  printf("Source: %s \n", argv[1]);
  printf("Target: %s \n", argv[2]);
  FILE * p_file;
  long p_size;
  size_t result;
  // Open file
  p_file = fopen(argv[1], "r");
  if(p_file == NULL) {
    printf("Unable to open the source file.\n");
    exit(-3);
  }
  // Obtain file size:
  fseek(p_file, 0, SEEK_END);
  p_size = ftell(p_file);
  rewind(p_file);
  printf("Source length: ");
  std::cout << p_size;
  printf("B");
  if((sizeof(char) * p_size) >= BCC_MAX_PROGRAM_SIZE) {
    printf("\nProgram too big, configure BCC_MAX_PROGRAM_SIZE.");
    exit(-2);
  }
  // Copy the file into the buffer:
  result = fread(program, 1, p_size, p_file);
  if(result != p_size) {
    printf("\nUnable to read source file.");
    exit(-1);
  }
  // Close source file
  fclose(p_file);
  // Compile program
  compiler.error_callback = error_callback;
  uint32_t t = BPM_MICROS();
  if(!compiler.run(program)) {
    printf("\nCompilation failed: check your code and retry\n");
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
  printf(", BIP length: ");
  std::cout << o_size;
  printf("B, reduction: %f", (100 - (100 / ((float)p_size / (float)o_size))));
  fclose(o_file);
  printf("%% \nCompilation time: %d microseconds \n", (int)(t));
  exit(1);
};
