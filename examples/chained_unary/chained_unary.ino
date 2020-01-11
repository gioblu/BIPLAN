#include "BCC.h"
#include "BIPLAN.h"

BCC bcc;
BIPLAN_Interpreter interpreter;

void error_callback(char *position, const char *string) {
  Serial.print("error: ");
  Serial.print(string);
  Serial.print(" ");
  Serial.print(*position);
  Serial.print(" at position ");
  Serial.println(position - interpreter.program_start);
};

char program[] =
"# Unary test \n\
print \"Chained unary test:\n\" \n\
$unary = 0 \n\
print \"Expected: 2 - 0\n\" \n\
print ++++$unary----, $unary, \"\n\" \n\
print \"Expected: 2 - 1\n\" \n\
print ++++$unary--, $unary, \"\n\" \n\
print \"Expected: 2 - 5\n\" \n\
print --++++$unary++++++, $unary, \"\n\" \n\
end\n";

void setup() {
  Serial.begin(115200);
  Serial.print(program);
  uint16_t length;
  for(length = 0; program[length] != 0; length++);
  Serial.println("--------------------------");
  Serial.print("Program length: ");
  Serial.print(length);
  Serial.println(" bytes");
  Serial.println();
  uint32_t time = millis();

  bcc.compile(program);
  interpreter.initialize(program, error_callback, &Serial, &Serial, &Serial);

  Serial.print(program);
  uint16_t new_length;
  for(new_length = 0; program[new_length] != 0; new_length++);
  Serial.println("--------------------------");
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
};

void loop() {
  do {
    interpreter.run();
  } while(!interpreter.finished());
  while(true);
};
