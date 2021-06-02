
// For printf and file used below
#include <inttypes.h>
//#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <BIPLAN.c>

#define BCC_MAX_PROGRAM_SIZE 2000
char program[BCC_MAX_PROGRAM_SIZE];

bool error = false;

void error_callback(char *position, const char *string) {
  printf("\nerror: ");
  printf("%s ", string);
  if(position) {
    printf("%c", *position);
    printf(" at position ");
    printf("%d \n ", (int)(position - bip_program_start));
  }
  error = true;
  exit(0);
};

int main(int argc, char* argv[]) {
  printf("BIPLAN interpreter - Giovanni Blu Mitolo 2021 \n");
  // Serial initialization
  int s;
  if(argc == 5) {
    s = serialOpen(argv[2], atoi(argv[3]));
    if(int(s) < 0) printf("Serial fail!\n");
    else printf("Serial OK.\n");
  }
  printf("Source: %s", argv[1]);
  FILE * p_file;
  long p_size;
  size_t result;
  // Open file
  p_file = fopen(argv[1], "r");
  if(p_file == NULL) {
    printf("\nFile error");
    exit(-3);
  }
  // Obtain file size:
  fseek(p_file, 0, SEEK_END);
  p_size = ftell(p_file);
  rewind(p_file);
  printf("\nSource length: ");
  std::cout << p_size;
  printf("B \n");
  if((sizeof(char) * p_size) >= BCC_MAX_PROGRAM_SIZE) {
    printf(" Program too big, configure BCC_MAX_PROGRAM_SIZE. ");
    exit(-2);
  }
  // Copy the file into the buffer:
  result = fread(program, 1, p_size, p_file);
  if(result != p_size) {
    printf("\nReading error ");
    exit(-1);
  }
  // Terminate
  fclose(p_file);
  // Initialize interpreter using cout as print and stdin as input
  bip_init(program, error_callback, s, s, s);
  printf("\nInterpreter output: \n\n");
  uint32_t t = BPM_MICROS();
  while(bip_run());
  t = BPM_MICROS() - t;
  printf("\n\nExecution duration: %u microseconds \n", t);
  exit(1);
};
