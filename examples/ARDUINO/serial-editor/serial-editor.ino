#include "BCC.h"
#include "BIPLAN.h"

BCC bcc;
BIPLAN_Interpreter interpreter;

#define MAX_PROG_SIZE 2500
#define MAX_LINE_SIZE  100


char program[MAX_PROG_SIZE];
char line[MAX_LINE_SIZE];
String ln = "";
uint16_t line_number = 0;
uint8_t line_offset = 0;
uint8_t char_index = 0;

void shift_left(uint16_t index, uint16_t offset) {
  Serial.print("Index: ");
  Serial.print(index);
  Serial.print(" Offset: ");
  Serial.println(offset);

  for(uint16_t i = 0; (i + index) < MAX_PROG_SIZE; i++) {
    program[(index - offset) + i] = program[index + i];
  }
  //for(uint16_t i = index + offset; i < index + offset + offset; i++)
  //  program[i] = ' ';
};

void empty_line() {
  for(uint8_t i = 0; i < MAX_LINE_SIZE; i++) line[i] = 0;
};

void empty_program() {
  for(uint16_t i = 0; i < MAX_PROG_SIZE; i++) program[i] = ' ';
};

uint16_t find_line_length(uint16_t index) {
  for(uint8_t i = index; i < MAX_LINE_SIZE; i++)
    if(program[i] == '\n') return (i - index);
  return 0;
};

uint16_t find_last_line() {
  for(uint16_t i = MAX_PROG_SIZE - 1; i > 0; i--)
    if(program[i] == '\n') return i;
};

uint16_t find_line(uint16_t line) {
  //Serial.print("Requested line: ");
  //Serial.println(line);
  uint16_t result = 0;
  for(uint16_t i = 0; (i < MAX_PROG_SIZE) && (line - 1); i++)
    if(program[i] == '\n') {
      result = i;
      line--;
    }
  //Serial.println(result);
  return (result) ? ++result : result;
};

void run() {
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
  do {
    interpreter.run();
  } while(!interpreter.finished());
}


void error_callback(char *position, const char *string) {
  Serial.print("error: ");
  Serial.print(string);
  Serial.print(" ");
  Serial.print(*position);
  Serial.print(" at position ");
  Serial.println(position - interpreter.program_start);
};

void setup() {
  Serial.begin(115200);
  empty_program();
  Serial.print("BIPLAN 0.0 Console editor ");
  Serial.print(MAX_PROG_SIZE);
  Serial.println(" bytes free");
  Serial.println("Copyright Giovanni Blu Mitolo 2019");
};

void loop() {
  if(Serial.available()) {
    char c = Serial.read();
    if(!line_number) {
      if((char_index < 4)) {
        if(c == ' ') {
          line_number = (uint16_t)ln.toInt();
          line_offset = char_index;
        }
        else if(c >= 48 && c <= 57) ln += c; else line[char_index++] = c;
      }
    } else if(c >= 0) {
      //program[find_line(line_number) + char_index] = c;
      line[char_index++] = c;
    }
    if(c == '\n') {
      //if(line_number) program[find_line(line_number) + char_index] = c;
      if(line_number) {
        uint8_t l = find_line_length(find_line(line_number));
        //Serial.print("Line length: ");
        //Serial.print(l);
        //Serial.print(" Input length: ");
        //Serial.println(char_index + 1);
        if(l >= char_index) {
          shift_left(find_line(line_number) + (char_index - line_offset), (l - (char_index - line_offset) + 1));
        } else {
          //uint16_t last = find_last_line();
          //for(uint8_t i = last; i; i--)
          //  program[i + (char_index - l)] = program[i];
        }
        memcpy(program + find_line(line_number), line, char_index);
      }
      if(line_number) {
        Serial.print(line_number);
        Serial.print(" ");
      }
      Serial.println(line);
      ln = "";
      char_index = 0;
      line_number = 0;
      if(line[0] == 'R' && line[1] == 'U' && line[2] == 'N') run();
      if(line[0] == 'L' && line[1] == 'I' && line[2] == 'S' && line[3] == 'T')
        Serial.println(program);
      empty_line();
    }
  }
};
