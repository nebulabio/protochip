#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <termios.h>
#include <errno.h>
#include <unistd.h> 

#include "deps/commander/commander.h"
#include "deps/serial/serial.h"
// refs:
//   - http://www.cprogramming.com/tutorial/cfileio.html
//   - http://www.codingunit.com/c-tutorial-binary-file-io <- this is really good


/** 
 * FIXME: how to scan for the correct port? How to work with windows?
 *
 * When I switch to cmake, I can do something like this:
 *
 *    #ifdef linux
 *      // do linux stuff
 *    #endif
 *
 *    #ifdef windows
 *     // do windows stuff
 *    #endif 
 *
 * In those blocks, define platform-specific vars. Also, read this article
 * and adopt the advice: http://lucumr.pocoo.org/2013/8/18/beautiful-native-libraries/
 * A good program to take inspiration from is mon:
 * https://github.com/tj/mon/blob/master/src/mon.c
 */ 
#define CHEAPSTAT "/dev/ttyUSB0" 
#define BAUDRATE  "B9600"        // baud is 9600, c_cflag = B9600

typedef struct { // legacy struct from the mcu, don't change
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

typedef struct { // legacy struct from the mcu, don't change
  char    name[15];
  int16_t freq;
  int16_t start;
  int16_t stop;
  int16_t height;
  int16_t increment;
  uint8_t curr_range;
} swv;

// Struct for the driver state
typedef struct {
  const char *pidfile;
  const char *logfile;
  char *port;
  int   baud;
  int   fd;
  int   daemon;
  int   verbose;
} driver_t; 

// Initiate state with default values
static driver_t driver;
int verbose = 0;
//driver.verbose->0;
//driver.baud   ->9600; 
//driver.fd     ->-1;


// Function signatures
static void exithandler(driver_t *driver);
static void print_profile(profile data, int fd);
static void print_swv(swv data, int fd);
static void take_ownership(char *port);


// Public api - FIXME: flesh this out
//               also: http://lucumr.pocoo.org/2013/8/18/beautiful-native-libraries/
void list_ports();
void runn(const char *cmd, driver_t *driver);


// entrypoint helpers
static void set_verbose(command_t *self) { verbose = 1; };
static void error(char *msg)             { fprintf(stderr, "Error: %s\n", msg); exit(1); }
static void tbd(command_t *self)         { printf("to be developed!"); exit(1); } 

// entrypoint
int main(int argc, char **argv) {
  command_t cli;
  
  command_init(&cli, argv[0], "0.0.1");
  command_option(&cli, "-v", "--verbose", "enable verbose output", set_verbose);
  command_option(&cli, "-l", "--list", "list all available ports", list_ports);
  command_option(&cli, "-d", "--daemon", "run as a daemon in the background", tbd);
  command_option(&cli, "-p", "--port", "specify the port. If not specified, tries to guess based on your platform.", tbd);
  command_option(&cli, "-b", "--baud", "specify the baud rate, defaults to 9600", tbd);
  command_parse(&cli, argc, argv);

  printf("additional args:\n");
  for (int i = 0; i < cli.argc; ++i) {
    printf("  - '%s'\n", cli.argv[i]);
  }

  // command required
  if (!cli.argc) error("<cmd> required");
  const char *cmd = cli.argv[0];

  runn(cmd, &driver);

  // don't think I need this?
  //command_free(&driver); 
  return 0;
}


// actual functionality

static void exithandler(driver_t *driver) { printf("Closing the connection.\n"); serialClose(driver->fd); }

static void print_profile(profile data, int fd) {
  printf("\n"); // Begin
  printf("File descriptor is %i\n", fd);

  printf("  Description  \t Data\tAddress\t\tSize\n");
  printf("---------------------------------------------------\n");
  printf("         Name:\t%s\t%p\t%lu\n", data.name,       &data.name,       sizeof(data.name));
  printf("         Type:\t%u\t%p\t%lu\n", data.type,       &data.type,       sizeof(data.type));
  printf("  Operation 1:\t%d\t%p\t%lu\n", data.op1,        &data.op1,        sizeof(data.op1));
  printf("  Operation 2:\t%d\t%p\t%lu\n", data.op2,        &data.op2,        sizeof(data.op2));
  printf("  Operation 3:\t%d\t%p\t%lu\n", data.op3,        &data.op3,        sizeof(data.op3));
  printf("  Operation 4:\t%d\t%p\t%lu\n", data.op4,        &data.op4,        sizeof(data.op4));
  printf("  Operation 5:\t%d\t%p\t%lu\n", data.op5,        &data.op5,        sizeof(data.op5));
  printf("  Operation 6:\t%d\t%p\t%lu\n", data.op6,        &data.op6,        sizeof(data.op6));
  printf("Current Range:\t%d\t%p\t%lu\n", data.curr_range, &data.curr_range, sizeof(data.curr_range));
  printf("---------------------------------------------------\n");
  printf("  Total Bytes: \t %lu\n\n", sizeof(data));

  for (int p = 0; p < sizeof(data.name); p++) {
    printf("\tname[%i]:\t%x\n", p, data.name[p]);
  }

  printf("\n"); // End of printer
}

static void print_swv(swv data, int fd) {
  printf("\nFile descriptor is %i\n", fd);

  printf("  Description  \t Data\tAddress\t\tSize\n");
  printf("---------------------------------------------------\n");
  printf("         Name:\t%s\t%p\t%lu\n", data.name,       &data.name,       sizeof(data.name));
  printf("    Frequency:\t%u\t%p\t%lu\n", data.freq,       &data.freq,       sizeof(data.freq));
  printf("        Start:\t%i\t%p\t%lu\n", data.start,      &data.start,      sizeof(data.start));
  printf("         Stop:\t%d\t%p\t%lu\n", data.stop,       &data.stop,       sizeof(data.stop));
  printf("       Height:\t%d\t%p\t%lu\n", data.height,     &data.height,     sizeof(data.height));
  printf("    Increment:\t%d\t%p\t%lu\n", data.increment,  &data.increment,  sizeof(data.increment));
  printf("Current Range:\t%d\t%p\t%lu\n", data.curr_range, &data.curr_range, sizeof(data.curr_range));
  printf("---------------------------------------------------\n");
  printf("  Total Bytes: \t %lu\n\n", sizeof(data));

  for (int p = 0; p < sizeof(data.name); p++) {
    printf("\tname[%i]:\t%x\n", p, data.name[p]);
  }

  printf("\n"); // End of printer
}


static void take_ownership(char *port) {
  int  user = getuid();
  int group = getgid();

#ifdef DEBUG
  printf("\nUID:\t%d\nGID:\t%d\n", user, group);
  printf("Port is: %s", port);
#endif

  // int chown(const char *path, uid_t owner, gid_t group);
  if (chown(port, user, group) == -1) { 
    printf("Error (can't `chown`): %s\n", strerror(errno)); 
    exit(EXIT_FAILURE); 
  }
}


void list_ports() {
  char **ports = getSerialPorts();
  char **tmp = ports;
  printf("Available serial ports:\n");

  while (*tmp != NULL) { printf(" %s\n", *(tmp++)); }
  free(ports);
}

// FIXME: refactor this to dispatch on cmd
// for inspiration: https://github.com/tj/mon/blob/master/src/mon.c#L326
void runn(const char *cmd, driver_t *driver) {

#ifdef DEBUG
  printf("running %s", cmd); // yeah, this cmd doesn't do anything, there's only one command
#endif

  take_ownership(driver->port);

  driver->fd = serialOpen(driver->port, driver->baud);
    
  if (driver->fd == -1) {
    printf("Could not open %s with %d!\n", driver->port, driver->baud);
    exit(1);
  }

  atexit(exithandler);

#ifdef DEBUG  
  printf("Connected! Datareceived will be printed...\n");
  printf("Use CTRL+C to quit.\n");
#endif

  while (driver->fd != -1) {
    if (serialHasChar(driver->fd)) {

      swv d;
      read(driver->fd, &d, 29);
      print_swv(d, driver->fd);

      //short int type;
        

      //printf("Getting results for: %s", type);
        
      /*profile p; int *ptr = &p; 

        while (ptr < 29) {

        if ( ptr < 16 ) { p.name = serialReadRaw(fd, ptr, 1); ptr += 14; } 
        if ( ptr < 32 ) { p.type = serialReadRaw(fd, ptr, 8); ptr  = 29; }

        }*/
    }
  }
}


