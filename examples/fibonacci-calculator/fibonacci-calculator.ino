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
"print \"BIPLAN v0.0 prime calculator \n Digit the test range: \" \n\
$index = 0 \n\
$range = 0 \n\
while true \n\
  $value = serialRead \n\
  if $value < 1 continue endif \n\
  if $value == 13 break endif \n\
  if ($value < 48) || ($value > 57) \n\
    print \"Only numbers are accepted \n\" \n\
    restart \n\
  endif \n\
  :str[$index++] = $value \n\
redo \n\
print :str, \"\n\" \n\
$range = number :str \n\
for $i = 0 to $range \n\
  print($i, \" prime: \", prime($i), \"\n\"); \n\
next \n\
$time = millis \n\
for $i = 0 to $range \n\
  prime($i) \n\
next \n\
print(\"Elapsed time: \", millis - $time, \" milliseconds \n\") \n\
restart \n\
function prime($n) \n\
  if $n <= 1 return 0 endif \n\
  if $n <= 3 return 1 endif \n\
  if ($n % 2 == 0) || ($n % 3 == 0) return 0 endif \n\
  for $u = 2 to sqrt($n) + 1 \n\
    if($n % $u == 0) return 0 endif \n\
    if $n == $u return 1 endif \n\
  next \n\
return 1 \n\
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
