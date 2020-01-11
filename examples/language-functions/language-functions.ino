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
"# BIPLAN language functions test \n\
print \"\nBIPLAN v0.0 language functions test start...\" \n\
print \"\nmillis: \", millis \n\
print \"\ndigitalRead 13: \", digitalRead 13 \n\
print \"\nanalogRead 0: \", analogRead 0 \n\
print \"\nrandom 100: \", random 100 \n\
print \"\nrandom 0, 10: \", random 0, 10 \n\
print \"\nsqrt 81: \", sqrt 81 \n\
print \"\npinMode 13, OUTPUT \" \n\
pinMode 13, OUTPUT \n\
print \"\nNow blink 5 times: \" \n\
for $i = 0 to 4 \n\
  print \"\nBLINK\" \n\
  digitalWrite 13, HIGH \n\
  delay 1000 \n\
  digitalWrite 13, LOW \n\
  delay 1000 \n\
next \n\
print \"\n\BIPLAN language functions test finished.\" \n\
end\n";

void setup() {
  pinMode(13, OUTPUT);
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
