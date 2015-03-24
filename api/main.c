#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <termios.h>
#include <errno.h>
#include <unistd.h> 

#include "deps/serial/serial.h"
#include "lib/profile.h"
// refs:
//   - http://www.cprogramming.com/tutorial/cfileio.html
//   - http://www.codingunit.com/c-tutorial-binary-file-io <- this is really good


#define CHEAPSTAT "/dev/ttyUSB0" // FIXME: how to scan for the correct port? How to account for Windows?
#define BAUDRATE  "B9600"        // baud is 9600, c_cflag = B9600

int fd = -1;

void exithandler() {
  serialClose(fd);
}

/**
 * `conn_cheapstat()` - Opens a port to the Cheapstat
 * 
 * Returns the file descriptor on success or -1 on error.
 *
int conn_cheapstat(void) {
  int fd; // File descriptor for the port

  fd = open(CHEAPSTAT, O_RDWR | O_NOCTTY | ONDELAY);

  if (fd == -1 ) {
    perror("conn_cheapstat: Unable to open CHEAPSTAT -");
  } else {
    fcntl(fd, F_SETFL, 0);
  }

  return(fd);    
}
*/

int main(int argc, char **argv) {
  if ((argc == 2) && (strcmp(argv[1], "-l") == 0)) {
    char **ports = getSerialPorts();
    char **tmp = ports;
    printf("Available serial ports:\n");
    while (*tmp != NULL)
      printf(" %s\n", *(tmp++));
    free(ports);
  } else if (argc == 3) {
    fd = serialOpen(argv[1], atoi(argv[2]));
    if (fd == -1) {
      printf("Could not open %s with %d!\n", argv[1], atoi(argv[2]));
      return 1;
    }
    atexit(exithandler);
    printf("Connected! Datareceived will be printed...\n");
    printf("Use CTRL+C to quit.\n");
    for (;;) {
      if (serialHasChar(fd)) {
        char c;
        serialReadChar(fd, &c);
        printf("%c", c);
      }
    }
  } else {
    printf("Usage:\n");
    printf("  %s -l        --> list available ports\n", argv[0]);
    printf("  %s PORT BAUD --> monitor port\n", argv[0]);
  }

  return 0;
}
