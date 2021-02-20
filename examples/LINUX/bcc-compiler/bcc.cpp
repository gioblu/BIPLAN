
// For printf and file used below
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <BCC.h>

#define BCC_MAX_PROGRAM_SIZE 2000
char program[BCC_MAX_PROGRAM_SIZE];
BCC compiler;

void error_callback(char *position, const char *string) {
  printf("Compilation error: ");
  printf("%s", string);
  printf("\n");
  fflush(stdout);
};

int main(int argc, char* argv[]) {
  printf("BCC (BIP Compiler Collection) Giovanni Blu Mitolo 2021 \n");
  printf("Source: %s \n", argv[1]);
  printf("Target: %s \n", argv[2]);
  fflush(stdout);
  FILE * pFile;
  long lSize;
  size_t result;
  // Open file
  pFile = fopen(argv[1], "r");
  if(pFile == NULL) {
    fputs("Unable to open the source file.\n", stderr);
    exit(1);
  }
  // Obtain file size:
  fseek(pFile, 0, SEEK_END);
  lSize = ftell(pFile);
  rewind(pFile);
  printf("Source length: ");
  std::cout << lSize;
  printf("B \n");
  if((sizeof(char) * lSize) >= BCC_MAX_PROGRAM_SIZE) {
    fputs("Program too big, configure BCC_MAX_PROGRAM_SIZE.\n", stderr);
    exit(2);
  }
  // Copy the file into the buffer:
  result = fread(program, 1, lSize, pFile);
  if(result != lSize) {
    fputs("Unable to read source file.\n", stderr);
    exit(3);
  }
  // Close source file
  fclose(pFile);
  // Compile program
  compiler.error_callback = error_callback;
  uint32_t t = BPM_MICROS();
  compiler.run(program);
  t = BPM_MICROS() - t;
  printf("Compilation time: %u microseconds \n", t);
  // Save program in target file
  FILE *f = fopen(argv[2], "w");
  fwrite(program, sizeof(char), strlen(program), f);
  fclose(f);
  return 0;
};
