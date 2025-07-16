#ifndef LINUX
    #define LINUX
#endif

#ifndef BPM_LINUX_SEPARATE_DEFINITION
    #define BPM_LINUX_SEPARATE_DEFINITION
#endif

#include "BIPLAN_LINUX_Interface.h"
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
  int fd;
 
  // Open the file descriptor in non-blocking mode
  fd = open(device, O_RDWR | O_NOCTTY | O_NONBLOCK);

  // Set up the control structure
  struct termios toptions;

  // Get currently set options for the tty
  tcgetattr(fd, &toptions);

  // Configure bad rate according to baud parameter
  speed_t bd = 0;

  switch(baud) {
    case     50: bd = B50; break;
    case     75: bd = B75; break;
    case    110: bd = B110; break;
    case    150: bd = B150; break;
    case    200: bd = B200; break;
    case    300: bd = B300; break;
    case    600: bd = B600; break;
    case   1200: bd = B1200; break;
    case   1800: bd = B1800; break;
    case   2400: bd = B2400; break;
    case   4800: bd = B4800; break;
    case   9600: bd = B9600; break;
    case  19200: bd = B19200; break;
    case  38400: bd = B38400; break;    
    case  57600: bd = B57600; break;
    case 115200: bd = B115200; break;
    case 230400: bd = B230400; break;
    default: bd = B0;  // Invalid baud rate
  }

  cfsetispeed(&toptions, bd);
  cfsetospeed(&toptions, bd);
  // 8 bits, no parity, no stop bits
  toptions.c_cflag &= ~PARENB;
  toptions.c_cflag &= ~CSTOPB;
  toptions.c_cflag &= ~CSIZE;
  toptions.c_cflag |= CS8;
  // No hardware flow control 
  toptions.c_cflag &= ~CRTSCTS;
  // Enable receiver, ignore status lines 
  toptions.c_cflag |= CREAD | CLOCAL;
  // Disable input/output flow control, disable restart chars
  toptions.c_iflag &= ~(IXON | IXOFF | IXANY);
  /* disable canonical input, disable echo, disable visually erase chars,
  disable terminal-generated signals */
  toptions.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
  // disable output processing
  toptions.c_oflag &= ~OPOST;

  // wait for 1 character to come in before read returns 
  toptions.c_cc[VMIN] = 1;
  // 1 second reception timeout
  toptions.c_cc[VTIME] = 10;  

  // commit the options 
  tcsetattr(fd, TCSANOW, &toptions);
  tcflush(fd, TCIFLUSH);
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

/* Reads a single key-press (unbuffered) ----------------------------------- */

unsigned char keypress() {
  struct termios old_tio, new_tio;
	unsigned char c;

	// get the terminal settings for stdin 
	tcgetattr(STDIN_FILENO,&old_tio);

	// we want to keep the old setting to restore them a the end 
	new_tio = old_tio;
	// disable canonical mode (buffered i/o) and local echo 
	new_tio.c_lflag &=(~ICANON & ~ECHO);

	// set the new settings immediately 
	tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
	c = getchar();
	// restore the former settings 
	tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);

	return c;
}

/* ltoa atol --------------------------------------------------------------- */

void fast_ltoa(unsigned long value, char* string, uint16_t shift) {
  unsigned char index = BP_NUM_MAX;
  char buffer[BP_NUM_MAX];
  string = string + shift;
  do {
    buffer[--index] = '0' + (value % 10);
  } while (value /= 10);
  do {
    *string++ = buffer[index];
  } while(++index < BP_NUM_MAX);
  *string = 0;
};

long fast_atol(const char *p) {
  int c = *(p++), x = 0;
  for(; c > 47 && c < 58; c = *(p++)) x = (x << 1) + (x << 3) + c - 48;
  return x;
};
