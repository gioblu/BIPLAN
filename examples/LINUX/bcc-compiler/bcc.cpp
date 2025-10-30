#include <BCC.h>

char program[BCC_MAX_PROGRAM_SIZE];
bcc_error_t bcc_error_callback = NULL; 

void error_handler(uint16_t line, const char *position, const char *string) {
  printf("| State    | \033[31mError: %s Line: %d", string, line);
  if(position != NULL) {
    printf("\nCode: ");
    for(uint16_t i = 0; *position != 0 && *position != BP_LF; position++)
      printf("%c", *position);
  }
  printf("\033[m\n\n");
  exit(EXIT_FAILURE);
};

int main(int argc, char* argv[]) {
  printf("\n| BCC      | BIP Compiler Collection by Giovanni Blu Mitolo\n");
  FILE * p_file;
  long p_size;
  size_t result;
  // Open file
  p_file = fopen(argv[1], "r");
  if(p_file == NULL) {
    printf("| State    | \033[31mError: Unable to open source file.\033[m\n\n");
    exit(2);
  }
  // Obtain file size:
  fseek(p_file, 0, SEEK_END);
  p_size = ftell(p_file);
  rewind(p_file);
  
  if((sizeof(char) * p_size) >= BCC_MAX_PROGRAM_SIZE) {
    printf("| State    | \033[31mError: ");
    printf(
      "Source too big, BCC_MAX_PROGRAM_SIZE is set to %dB.\033[m\n\n",
      BCC_MAX_PROGRAM_SIZE
    );
    exit(3);
  }
  // Copy the file into the buffer:
  result = fread(program, 1, p_size, p_file);
  if(result != p_size) {
    printf("| State    | \033[31mError: Unable to read source file.\033[m\n\n");
    exit(4);
  }

  fclose(p_file);

  printf("| Source   | %s (%ldB)\n", argv[1], p_size);

  // Compile program
  bcc_error_callback = error_handler;
  uint32_t t = BPM_MICROS();
  if(!bcc_run(program)) {
    printf("| State    | \033[31mError: Compilation failed.\033[m\n\n");
    exit(EXIT_FAILURE);
  }
  t = BPM_MICROS() - t;
  int o_size = 0;
  if(strlen(program) > 0) {
    FILE *o_file = fopen(argv[2], "w");
    if(o_file == NULL) {
      printf("| State    | \033[31mError: Unable to open the target file.\033[m\n\n");
      exit(5);
    }
    fwrite(program, sizeof(char), strlen(program), o_file);
    fseek(o_file, 0, SEEK_END);
    o_size = ftell(o_file);
    rewind(o_file);
    fclose(o_file);
  }
  
  printf("| Target   | %s (%dB)\n", argv[2], o_size);
  printf("| Duration | %.2f milliseconds \n", (float)(t) / 1000);
  printf("| State    | \033[32mSuccess\033[m\n\n");
  exit(EXIT_SUCCESS);
};
