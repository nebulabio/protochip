#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <errno.h>
#include <unistd.h> 

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
  const char *port;
  int   baud;
  int   fd;
  int   daemon;
  int   verbose;
} driver_t; 

/********************************** 
  initialize state
**********************************/

static driver_t driver;

/********************************** 
  helper functions 
**********************************/

static void exithandler()    { printf("Closing the connection.\n"); serialClose(driver.fd); }
static void error(char *msg) { fprintf(stderr, "Error: %s\n", msg); exit(1); }

static void take_ownership(const char *port) {
  int  user = getuid();
  int group = getgid();

#ifdef DEBUG
  printf("\nUID:\t%d\nGID:\t%d\n\n", user, group);
#endif

  printf("Port is: %s\n\n", port);

  // int chown(const char *path, uid_t owner, gid_t group);
  if (chown(port, user, group) == -1) { 
    printf("Error (can't `chown`): %s\n", strerror(errno)); 
    exit(EXIT_FAILURE); 
  }
}



/********************************** 
  stateful functions 

  i.e., functions that modify the
  `driver_t driver` struct.
**********************************/

void cheapstat_reader(driver_t *driver) {
  while (driver->fd != -1) {
    if (serialHasChar(driver->fd)) {
      uint8_t b;
      read(driver->fd, &b, 1);
      printf("%02x", b);
    }
  }
}

// FIXME: write a daemonize function
//static void daemonize() {}

/********************************** 
  driver processes

  i.e., top-level commands for 
  the cli
**********************************/

/*
 * stops the driver and gracefully shuts down all things
 * 
 * FIXME: this segfaults
 */
//static void stop(driver_t *driver) {
//  free(&driver);
//}


/*
 * starts the driver
 */ 
static void start(driver_t *driver) {

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


  cheapstat_reader(driver);
}


/*
 * lists available ports
 */
void list(driver_t *driver) {
  char **ports = getSerialPorts();
  char **tmp = ports;
  printf("Available serial ports:\n");

  while (*tmp != NULL) { printf(" %s\n", *(tmp++)); }
  free(ports);
}


//@@ add ability to run as background thread.
void daemonize(void)
{}

// Prints correct usage.
int usage(void)
{
  fprintf(stderr, "-i --pidfile <path>  specify the pidfile location\n");
  fprintf(stderr, "-g --logfile <path>  specify the logfile location\n");
  fprintf(stderr, "-b --baud <num>      specify the baud rate, defaults to 9600\n");
  fprintf(stderr, "-p --port <path>     specify the port. If empty, tries to guess based on your platform\n");
  fprintf(stderr, "-v --verbose         enable verbose output\n");
  fprintf(stderr, "-d --daemon          run as a daemon in the background\n");
  return 0;
}

// entrypoint
int main(int argc, char **argv) {
  int c = 0, d = 0;

  // default states.
  driver.pidfile = ""; //FIXME
  driver.logfile = ""; //FIXME
  driver.port    = "/dev/USB0";
  driver.baud    = 9600;
  driver.fd      = -1;
  driver.daemon  = 0;
  driver.verbose = 0;



  printf("CheapStat Driver v0.0.2\n");

  // parse command line arguments.
  while((c = getopt(argc, argv, "i:g:b:p:vd")) != EOF)
  {
    switch(c)
    {
      case 'b':
        driver.baud = atoi(optarg);
        break;
      case 'p':
        driver.port = optarg;
        break;
      case 'i':
        driver.pidfile = optarg;
        break;
      case 'g':
        driver.logfile = optarg;
        break;
      case 'd':
        d = 1;
        break;
      case 'v':
        driver.verbose = 1;
        printf("verbose\n");
        break;
      default:
        fprintf(stderr, "unknown arg %c\n", optopt);
        return usage();
        break;
    }
  }

  printf("port = %s\n", driver.port);
  printf("baud rate = %i\n", driver.baud);


  if (d == 1)
    daemonize();


  printf("exit\n");
  return 0;
}

