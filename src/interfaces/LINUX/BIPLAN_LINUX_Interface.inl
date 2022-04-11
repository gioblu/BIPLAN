#ifndef LINUX
    #define LINUX
#endif
#ifndef PJON_LINUX_SEPARATE_DEFINITION
    #define PJON_LINUX_SEPARATE_DEFINITION
#endif

#include "BIPLAN_LINUX_Interface.h"
#include <asm-generic/termbits.h>
#include <asm-generic/ioctls.h>

auto start_ts = std::chrono::high_resolution_clock::now();
auto start_ts_ms = std::chrono::high_resolution_clock::now();

uint32_t micros() {
  auto elapsed_usec =
  std::chrono::duration_cast<std::chrono::microseconds>(
    std::chrono::high_resolution_clock::now() - start_ts
  ).count();

  if(elapsed_usec >= UINT32_MAX) {
    start_ts = std::chrono::high_resolution_clock::now();
    return 0;
  } else return elapsed_usec;
};

uint32_t millis() {
  return (uint32_t)
  std::chrono::duration_cast<std::chrono::milliseconds>(
    std::chrono::high_resolution_clock::now() - start_ts_ms
  ).count();
};

void delayMicroseconds(uint32_t delay_value) {
  struct timeval tv;
  if (delay_value < 1000000){
    tv.tv_sec = 0;
    tv.tv_usec = delay_value;
  }
  else{
    tv.tv_sec = floor(delay_value / 1000000);
    tv.tv_usec = delay_value - tv.tv_sec * 1000000;
  }

  select(0, NULL, NULL, NULL, &tv);
};

void delay(uint32_t delay_value_ms) {
  std::this_thread::sleep_for(std::chrono::milliseconds(delay_value_ms));
};

/* Open serial port -------------------------------------------------------- */

int serialOpen(const char *device, const int baud) {
  speed_t bd;
  int fd;

  if((fd = open(device, O_NDELAY | O_NOCTTY | O_NONBLOCK | O_RDWR)) == -1)
  return -1;

  fcntl(fd, F_SETFL, O_RDWR);

  struct termios2 config;
  int state;
  int r = ioctl(fd, TCGETS2, &config);
  if(r) return -1;

  // Sets terminal to something like "raw" mode of Version 7 terminal driver
  config.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
                   | INLCR | IGNCR | ICRNL | IXON);
  config.c_cflag &= ~(CSTOPB | CSIZE | PARENB);
  config.c_cflag |= CS8;
  config.c_lflag &= ~(ECHO | ECHOE | ECHONL | ICANON | ISIG | IEXTEN);
  config.c_oflag &= ~OPOST;

  // sets the baudrate
  config.c_ispeed = config.c_ospeed = baud;
  config.c_cflag &= ~CBAUD;
  config.c_cflag |= BOTHER;

  config.c_cflag |= (CLOCAL | CREAD);
  config.c_cc [VMIN] = 0;
  config.c_cc [VTIME] = 50; // 5 seconds reception timeout

  r = ioctl(fd, TCSETS2, &config);
  if(r) return -1;

  r = ioctl(fd, TIOCMGET, &state);
  if(r) return -1;

  state |= (TIOCM_DTR | TIOCM_RTS);
  r = ioctl(fd, TIOCMSET, &state);
  if(r) return -1;

  delayMicroseconds(10000);	// Sleep for 10 milliseconds
  return fd;
};

/* Returns the number of bytes of data available to be read in the buffer -- */

int serialDataAvailable(const int fd) {
  int result = 0;
  ioctl(fd, FIONREAD, &result);
  return result;
};

/* Reads a character from the serial buffer -------------------------------- */

int serialGetCharacter(const int fd) {
  uint8_t result;
  if(read(fd, &result, 1) != 1) return -1;
  return ((int)result) & 0xFF;
};

/* ltoa atol --------------------------------------------------------------- */

int fast_ltoa(unsigned long value, char* string, uint16_t shift = 0) {
  unsigned char index = BP_NUM_MAX;
  char buffer[BP_NUM_MAX];
  string = string + shift;
  do {
    buffer[--index] = '0' + (value % 10);
  } while (value /= 10);
  do {
    *string++ = buffer[index++];
  } while(index < BP_NUM_MAX);
  *string = 0;

  return index;
};

long fast_atol(const char *p) {
  int c = *(p++), x = 0;
  for(; c > 47 && c < 58; c = *(p++)) x = (x << 1) + (x << 3) + c - 48;
  return x;
};
