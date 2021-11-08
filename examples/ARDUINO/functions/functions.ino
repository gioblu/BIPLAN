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
"print \"BIPLAN v0.0 test start...\" \n\
print \"\nComputing sum of 1 + 1 = \", sum(1, 1) \n\
print \"\nComputing mul of 2 x 2 = \", mul(2, 2) \n\
print \"\nComputing div of 10 / 2 = \", div(10, 2) \n\
@test = div(100, 2) \n\
print \"\nexpected return value 50: \", @test, \"\nempty_func return value: \", empty_func() \n\
print \"\nBIPLAN test ended.\" \n\
stop # Program end \n\
function sum($a, $b) \n\
  return $a + $b \n\
function mul($a, $b) \n\
  return $a * $b \n\
function div($a, $b) \n\
  return $a / $b \n\
function empty_func() \n\
  return; \n\
\n";

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
