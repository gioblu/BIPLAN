
#include "BCC.h"
#include "BIPLAN.h"

BCC compiler;


bool error = false;

void error_callback(char *position, const char *string) {
  Serial.print("error: ");
  Serial.print(string);
  if(position) {
    Serial.print(" ");
    Serial.print(*position);
    Serial.print(" at position ");
    Serial.print(position - bip_program_start);
  }
  Serial.println();
  error = true;
};

char program[] =
"# Memory update \n\
mem[0] = 10\n\
mem[1] = 22\n\
mem[2] = 14\n\
mem[3] = 9\n\
print \"Variables initial state \n\" \n\
# Print memory \n\
for $i = 0 to 3 \n\
  print mem[$i], \"\n\" \n\
next \n\
# Update memory \n\
for $i = 0 to 3 \n\
  mem[$i] = $i \n\
next \n\
print \"Memory state changed by reference \n\" \n\
# Print memory \n\
for $i = 0 to 3 \n\
  print mem[$i], \"\n\" \n\
next \n\
stop\n";

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(115200);
  // Show human readable input program
  Serial.print("\nBIPLAN human-readable source:\n\n");
  Serial.print(program);
  uint16_t length = strlen(program);
  // Print stats
  Serial.println("\n--------------------------");
  Serial.print("Program length: ");
  Serial.print(length);
  Serial.println(" bytes");
  uint32_t time = millis();
  // Compile
  Serial.print("\nBCC compilation result:\n\n");
  compiler.error_callback = error_callback;
  compiler.run(program);
  // Print compiled source
  Serial.print("\nBIPLAN machine language:\n\n");
  Serial.print(program);
  uint16_t new_length = strlen(program);
  // Print Stats
  Serial.println("\n\n--------------------------");
  Serial.print("Compilation duration: ");
  Serial.print(millis() - time);
  Serial.println(" milliseconds");
  Serial.print("BIPLAN program length: ");
  Serial.print(length);
  Serial.println(" bytes");
  Serial.print("BIPLAN compiled program length: ");
  Serial.print(new_length);
  Serial.println(" bytes");
  Serial.print("Reduction: ");
  Serial.print(100 - (new_length * 100.0) / length);
  Serial.println("%");
  Serial.println("Program output:");
  Serial.println();
  // Initialize interpreter
  bip_init(
    program,
    error_callback,
    &Serial,
    &Serial,
    &Serial
  );
  // Check for compilation errors
  if(error) {
    bip_ended = true;
    Serial.println("Fix your code and retry.");
  }
}

void loop() {
  while(bip_run());
  while(true);
}
