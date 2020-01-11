#include "BCC.h"
#include "BIPLAN.h"

BCC    bcc;
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
"# Condition test \n\
print \"BIPLAN v0.0 conditions test start...\" \n\
block(false) \n\
block(true) \n\
end\n\
function block($condition) \n\
  if $condition  \n\
    print \"Block if fail\n\" \n\
  endif \n\
  if not $condition  \n\
    print \"Block if ok\n\" \n\
  endif \n\
  if $condition \n\
    print \"Block if fail\n\" \n\
  else  \n\
    print \"Block else ok\n\" \n\
  endif \n\
return\n";

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
