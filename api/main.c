#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <termios.h>
#include <errno.h>
#include <unistd.h> 

#include "deps/serial/serial.h"
// refs:
//   - http://www.cprogramming.com/tutorial/cfileio.html
//   - http://www.codingunit.com/c-tutorial-binary-file-io <- this is really good


#define CHEAPSTAT "/dev/ttyUSB0" // FIXME: how to scan for the correct port? How to account for Windows?
#define BAUDRATE  "B9600"        // baud is 9600, c_cflag = B9600


typedef struct {
	char name[15];
	uint8_t type;
	int16_t op1;
	int16_t op2;
	int16_t op3;
	int16_t op4;
	int16_t op5;
	int16_t op6;
	uint8_t curr_range;
} profile;


int fd = -1;

void exithandler() {
  printf("Closing the connection.\n");
  serialClose(fd);
}


void printProfile(profile data) {
  printf("  Description  \t Data\tAddress\t\tSize\n");
  printf("---------------------------------------------------\n");
  printf("         Name:\t%s\t%p\t%lu\n", data.name,       &data.name,       sizeof(data.name));
  printf("         Type:\t%d\t%p\t%lu\n", data.type,       &data.type,       sizeof(data.type));
  printf("  Operation 1:\t%d\t%p\t%lu\n", data.op1,        &data.op1,        sizeof(data.op1));
  printf("  Operation 2:\t%d\t%p\t%lu\n", data.op2,        &data.op2,        sizeof(data.op2));
  printf("  Operation 3:\t%d\t%p\t%lu\n", data.op3,        &data.op3,        sizeof(data.op3));
  printf("  Operation 4:\t%d\t%p\t%lu\n", data.op4,        &data.op4,        sizeof(data.op4));
  printf("  Operation 5:\t%d\t%p\t%lu\n", data.op5,        &data.op5,        sizeof(data.op5));
  printf("  Operation 6:\t%d\t%p\t%lu\n", data.op6,        &data.op6,        sizeof(data.op6));
  printf("Current Range:\t%d\t%p\t%lu\n", data.curr_range, &data.curr_range, sizeof(data.curr_range));
  printf("---------------------------------------------------\n");
  printf("  Total Bytes: \t %lu \n", sizeof(data));

}

/**
 * `conn_cheapstat()` - Opens a port to the Cheapstat
 * 
 * Returns the file descriptor on success or -1 on error.
 *
*/

// FIXME: I should check permissions on the port to make sure it is openable

int main(int argc, char **argv) {
  if ((argc == 2) && (strcmp(argv[1], "-l") == 0)) {
    char **ports = getSerialPorts();
    char **tmp = ports;
    printf("Available serial ports:\n");

    while (*tmp != NULL) { printf(" %s\n", *(tmp++)); }
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
    

    while (fd != -1) {
      if (serialHasChar(fd)) {
        // need to use pointer arithmetic - track my location in the stream
        // with a pointer and de-reference the pointer to print the value of the input

        printf("\n"); // Begin

        printf("File descriptor is %i\n", fd);
        
        profile p;
        read(fd, &p, 29);

        printProfile(p);
        
        printf("\n"); // End of main program
        return 0;

        /*profile p; int *ptr = &p; 

        while (ptr < 29) {

          if ( ptr < 16 ) { p.name = serialReadRaw(fd, ptr, 1); ptr += 14; } 
          if ( ptr < 32 ) { p.type = serialReadRaw(fd, ptr, 8); ptr  = 29; }

          }*/
      }
    }
  } else {
    printf("Usage:\n");
    printf("  %s -l        --> list available ports\n", argv[0]);
    printf("  %s PORT BAUD --> monitor port\n", argv[0]);
  }

  return 0;
}
