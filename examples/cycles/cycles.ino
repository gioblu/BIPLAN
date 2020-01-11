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
"# Test inc speed \n\
print \"BIPLAN v0.0 cycles test start...\n\" \n\
$inc = 0 \n\
$time millis \n\
for $i = 0 to 10000 \n\
 ++$inc \n\
next \n\
print \"for: 10000 increments duration in milliseconds: \", millis - $time, \"\n\" \n\
delay 1000 \n\
$inc = 0\n\
$time = millis\n\
while $inc < 10000 \n\
  ++$inc \n\
redo \n\
print \"while redo: 10000 increments duration in milliseconds: \", millis - $time, \"\n\" \n\
print \"BIPLAN cycles test ended.\n\" \n\
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
  interpreter.initialize(
    program,
    error_callback,
    &Serial,
    &Serial,
    &Serial
  );

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
