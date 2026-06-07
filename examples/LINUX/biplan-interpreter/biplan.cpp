
/* This program implements the biplan command line interface.

   if the input is .biplan it compiles it and then interprets it.
   If the input is .bip it interprets it immediately

   Giovanni Blu Mitolo 2026 */

#include <string.h>

/* Although it is considered an anti-pattern to include BIPLAN.c inside
   a .c or .cpp file this is an intentional performance optimization.
   This approach operates with a single compilation units and
   enables aggressive inlining and IPO (IntraProcedural Optimization)
   for interpreter performance.  */

#include "../../../src/BIPLAN.c"
#include "../../../src/BCC.c"

char        program[BCC_MAX_PROGRAM_SIZE];
FILE       *p_file;
long        p_size;
size_t      result;
bool        error = false;
bool        verbose = false;
bcc_error_t bcc_error_callback = NULL;

static bool is_biplan_file(const char *path) {
  const char *ext = strrchr(path, '.');
  return ext && strcmp(ext, ".biplan") == 0;
}

void bcc_error_handler(uint16_t line, const char *position, const char *string) {
  if(position)
    printf(
      "\n\033[31m⚠️ Error: %s Line: %u Code: %s\033[m\n\n",
      string,
      line,
      position
    );
  else printf("\n\033[31m⚠️ Error: %s Line: %u\033[m\n\n", string, line);
  exit(EXIT_FAILURE);
}

void biplan_error_callback(const char *position, const char *string) {
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
    printf("\n\033[31m⚠️ Error: File error opening: %s\033[m\n", path);
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

void print_help() {
  printf("\nUsage: biplan [options] <script.bip|script.biplan> [arguments...]\n");
  printf("\nOptions:");
  printf("\n  -d, --debug   Prints internal interpreter performance & debugging metrics");
  printf("\n  -c, --compile Compiles .biplan source to .bip, requires source and target paths\n");
  printf("\n  -h, --help    Prints this clean help instruction layout\n");
  printf("\nExamples:");
  printf("\n  biplan script.bip");
  printf("\n  biplan script.biplan");
  printf("\n  biplan calc.biplan 12 + 12");
  printf("\n  biplan --debug prime.biplan");
  printf("\n  biplan --compile prime.biplan prime.bip\n\n");
  exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]) {
  if(argc < 2) print_help();

  char *script_path = NULL;
  int arg_index = 1;

  bool mode_compile_only = false;
  char *compile_src = NULL;
  char *compile_dst = NULL;

  // Process upfront global operational configuration flags cleanly
  while (arg_index < argc) {
    if(
      strcmp(argv[arg_index], "-d") == 0 ||
      strcmp(argv[arg_index], "--debug") == 0
    ) {
      verbose = true;
      arg_index++;
    } else if(
      strcmp(argv[arg_index], "-h") == 0 ||
      strcmp(argv[arg_index], "--help") == 0
    ) {
      print_help();
    } else if(
      strcmp(argv[arg_index], "-c") == 0 ||
      strcmp(argv[arg_index], "--compile") == 0
    ) {
      if (arg_index + 2 >= argc) {
        printf("\n\033[31m⚠️ Error: -c requires both source file and target destination.\033[m\n");
        print_help();
      }
      mode_compile_only = true;
      compile_src = argv[arg_index + 1];
      compile_dst = argv[arg_index + 2];
      arg_index += 3;
      break; // Exit argument processing immediately for compilation mode
    } else {
      // First non-flag argument encountered is designated as the target file path
      script_path = argv[arg_index];
      arg_index++;
      break;
    }
  }

  // Handle compile-only mode (biplan -c fib.biplan fib.bip)
  if(mode_compile_only) {
    printf("\nBCC (BIP Compiler Collection) - Embedded Engine\nGiovanni Blu Mitolo 2026\n\n");
    init_program(compile_src);
    printf("| Source   | %s (%ldB)\n", compile_src, p_size);

    bcc_error_callback = bcc_error_handler;
    uint32_t t = BPM_MICROS();
    if(!bcc_run(program)) {
      printf("| State    |\033[31m ⚠️ Error: Compilation failed.\033[m\n\n");
      exit(EXIT_FAILURE);
    }
    t = BPM_MICROS() - t;

    size_t out_len = strlen(program);
    if(out_len > 0) {
      FILE *o_file = fopen(compile_dst, "w");
      if(o_file == NULL) {
        printf("| State    |\033[31m ⚠️ Error: Unable to open target destination file.\033[m\n\n");
        exit(5);
      }
      fwrite(program, sizeof(char), out_len, o_file);
      fclose(o_file);
    }

    printf("| Target   | %s (%zuB)\n", compile_dst, out_len);
    printf("| Duration | %.2f milliseconds \n", (float)(t) / 1000);
    printf("| State    |\033[32m ✅ Success\033[m\n\n");
    exit(EXIT_SUCCESS);
  }

  // If no script path was isolated after checking options, drop out safely

  if(!script_path) {
    printf("\n\033[31m⚠️ Error: No target file provided.\033[m\n");
    print_help();
  }

  // Initialize the file reading tracker
  init_program(script_path);

  if(is_biplan_file(script_path)) {
    bcc_error_callback = bcc_error_handler;
    if(!bcc_run(program)) {
      printf("\n\033[31m⚠️ Error: Compilation failed.\033[m\n");
      exit(EXIT_FAILURE);
    }
  }

  // Process remaining trailing positional parameters as program arguments
  while (arg_index < argc) {
    bip_process_argument(argv[arg_index]);
    arg_index++;
  }

  if(verbose) printf("\nBIPLAN (Byte-coded Interpreted Programming Language) interpreter\nGiovanni Blu Mitolo 2026\n\n");

  bip_init(program, biplan_error_callback, 0, 0, 0);

  if(verbose) printf("Interpreter output: \n\n");
  uint32_t t = BPM_MICROS();
  while(bip_run());
  t = BPM_MICROS() - t;

  if(verbose) printf("\n\n\033[32m✅ Terminated without errors\033[m\nExecution duration: %u microseconds \n\n", t);
  else printf("\n");

  exit(EXIT_SUCCESS);
}
