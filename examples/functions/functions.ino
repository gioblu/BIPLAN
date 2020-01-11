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
"print \"BIPLAN v0.0 test start...\" \n\
print \"Computing sum of 1 + 1 = \", sum(1, 1) \n\
print \"Computing mul of 2 x 2 = \", mul(2, 2) \n\
print \"Computing div of 10 / 2 = \", div(10, 2) \n\
$test div(100, 2) \n\
print $test, empty_func() \n\
print \"BIPLAN test ended.\" \n\
end # Program end \n\
function sum($a, $b) \n\
  return $a + $b \n\
function mul($a, $b) \n\
  return $a * $b \n\
function div($a, $b) \n\
  return $a / $b \n\
function empty_func() \n\
  return \n\
\n";

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
}

void loop() {
  do {
    interpreter.run();
  } while(!interpreter.finished());
  while(true);
}
