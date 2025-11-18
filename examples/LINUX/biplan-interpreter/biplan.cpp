#include <BIPLAN.c>

bool   verbose = false;
char   program[BCC_MAX_PROGRAM_SIZE];
bool   error = false;
int    opt = 0;
FILE  *p_file;
long   p_size;
size_t result;

void error_callback(const char *position, const char *string) {
  printf("\n\033[31m⚠️ Error: ");
  printf("%s ", string);
  if(position) {
    printf("%c", *position);
    printf(" at position: ");
    printf("%s \033[m\n\n", position);
  }
  error = true;
  exit(EXIT_FAILURE);
};

void init_program(char *path) {
  if(verbose) printf("Source: %s", path);
  p_file = fopen(path, "r");
  if(p_file == NULL) {
    printf("\n\033[31m⚠️ Error: File error\033[m");
    exit(-3);
  } // Obtain file size:
  fseek(p_file, 0, SEEK_END);
  p_size = ftell(p_file);
  rewind(p_file);
  if(verbose) {
    printf("\nSource length: ");
    std::cout << p_size;
    printf("B \n");
  }
  if((sizeof(char) * p_size) >= BCC_MAX_PROGRAM_SIZE) {
    printf("\n\033[31m⚠️ Error: Program too long, configure BCC_MAX_PROGRAM_SIZE\033[m");
    exit(-2);
  } // Copy the file into the buffer:
  result = fread(program, 1, p_size, p_file);
  if(result != p_size) {
    printf("\nReading error ");
    exit(EXIT_FAILURE);
  }
  fclose(p_file);
};


int main(int argc, char *argv[]) {
  while((opt = getopt(argc, argv, "d::i:a:h::")) != -1) {
    switch(opt) {
      case 'd': verbose = true; break;
      case 'i': init_program(optarg); break;
      case 'a': bip_process_argument(optarg); break;
      case 'h':
        printf("\n-a: Passes argument to program, see args documentation");
        printf("\n-d: Prints debug information");
        printf("\n-h: Prints this help message");
        printf("\n-i: Path to the program to be interpreted (example: biplan -i fib.bip) \n\n");
        exit(1);
        break;
      case '?': printf("\n\033[31m⚠️ Invalid argument received\033[m");
      break;
    }
  }
  if(verbose) printf("\nBIPLAN (Byte-coded Interpreted Programming Language) interpreter\nGiovanni Blu Mitolo 2025\n\n");
  bip_init(program, error_callback, 0, 0, 0);
  // Initialize interpreter using cout as print and stdin as input
  if(verbose) printf("Interpreter output: \n\n");
  uint32_t t = BPM_MICROS();
  while(bip_run());
  t = BPM_MICROS() - t;
  if(verbose) printf("\n\n\033[32m✅ Terminated without errors\033[m\nExecution duration: %u microseconds \n\n", t);
  else printf("\n");
  exit(EXIT_SUCCESS);
}
