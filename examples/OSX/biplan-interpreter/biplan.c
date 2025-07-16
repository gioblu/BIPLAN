#include <iostream>
#include <../../../src/BIPLAN.c>

char   program[BCC_MAX_PROGRAM_SIZE];
bool   error = false;
int    opt = 0;
FILE  *p_file;
long   p_size;
size_t result;
uint32_t t = 0;

void end(bool e) {
  printf("\033[0;36m\n\nExecution duration: %u microseconds \033[0m\n\n", BPM_MICROS() - t);
  exit(e);
}

void error_callback(char *position, const char *string) {
  printf("\033[0;31m\nerror: ");
  printf("%s ", string);
  if(position) {
    printf("%c", *position);
    printf(" at position ");
    printf("%d \n", (int)(position - bip_program_start));
  }
  error = true;
  end(0);
};

void init_program(char *path) {
  printf("Source: \033[0;32m%s", path);
  p_file = fopen(path, "r");
  if(p_file == NULL) {
    printf("\nFile error\n");
    exit(-3);
  } // Obtain file size:
  fseek(p_file, 0, SEEK_END);
  p_size = ftell(p_file);
  rewind(p_file);
  printf("\033[0;36m Size: \033[0;32m");
  std::cout << p_size;
  printf("B \033[0;36m\n");
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
  printf("\n\033[0;36mBIPLAN (Bytecoded Interpreted Programming LANguage) interpreter \nGiovanni Blu Mitolo 2024 \n\n");
  while((opt = getopt(argc, argv, "i:a:s:b:h")) != -1) {
    switch(opt) {
      case 'i': init_program(optarg); break;
      case 'a': bip_process_argument(optarg); break;
      case 's':
        serial_name = optarg; printf("Serial name: %s \n", serial_name); break;
      case 'b':
        serial_bd = atoi(optarg); printf("Baudrate: %d \n", serial_bd); break;
      case 'h':
        printf("\n-a: Passes argument to program (-a hi -> args[0] = \"hi\")");
        printf("\n-h: Prints this help message\n");
        exit(1);
        break;
      case '?': printf("\nInvalid argument received");
      break;
    }
  }
  bip_init(program, error_callback, NULL, NULL, NULL);
  // Initialize interpreter using cout as print and stdin as input
  printf("Interpreter output: \033[0m\n\n");
  t = BPM_MICROS();
  while(bip_run());
  end(1);
}
