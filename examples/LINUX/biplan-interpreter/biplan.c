#include <iostream>
#include <BIPLAN.c>

bool   verbose = false;
char   program[BCC_MAX_PROGRAM_SIZE];
char  *serial_name = NULL;
int    serial_bd = 0, s;
bool   error = false;
int    opt = 0;
FILE  *p_file;
long   p_size;
size_t result;

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

void init_program(char *path) {
  if(verbose) printf("Source: %s", path);
  p_file = fopen(path, "r");
  if(p_file == NULL) {
    printf("\nFile error\n");
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
    printf(" Program too big, configure BCC_MAX_PROGRAM_SIZE. ");
    exit(-2);
  } // Copy the file into the buffer:
  result = fread(program, 1, p_size, p_file);
  if(result != p_size) {
    printf("\nReading error ");
    exit(-1);
  }
  fclose(p_file);
};


int main(int argc, char *argv[]) {
  while((opt = getopt(argc, argv, "i:a:s:b:h::")) != -1) {
    switch(opt) {
      case 'v': verbose = true;
      case 'i': init_program(optarg); break;
      case 'a': bip_process_argument(optarg); break;
      case 's':
        serial_name = optarg;
        if(verbose) printf("Serial name: %s \n", serial_name);
        break;
      case 'b':
        serial_bd = atoi(optarg);
        if(verbose) printf("Baudrate: %d \n", serial_bd);
        break;
      case 'h':
        printf("\n-a: Passes argument to program (-a hi -> args[0] = \"hi\")");
        printf("\n-b: Sets serial bardrate (-b 9600)");
        printf("\n-s: Sets serial port (-s COM1)");
        printf("\n-h: Prints this help message\n");
        exit(1);
        break;
      case '?': printf("\nInvalid argument received");
      break;
    }
  }
  if(serial_name && serial_bd) {
    s = serialOpen(serial_name, serial_bd);
    if(int(s) < 0) {
      printf("Serial fail!\n");
      exit(-4);
    }
  }
  if(verbose) printf("BIPLAN interpreter - Giovanni Blu Mitolo 2021 \n");
  bip_init(program, error_callback, s, s, s);
  // Initialize interpreter using cout as print and stdin as input
  if(verbose) printf("\nInterpreter output: \n\n");
  uint32_t t = BPM_MICROS();
  while(bip_run());
  t = BPM_MICROS() - t;
  if(verbose) printf("\n\nExecution duration: %u microseconds \n", t);
  else printf("\n");
  exit(1);
}
