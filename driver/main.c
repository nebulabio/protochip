#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>

#include <getopt.h>
#include <sys/time.h>

#include <unistd.h> 
#include <termios.h>

#include "deps/serial/serial.h"

#include "cheapstat-types.h"
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



// SWV 0
// CV 1
// ACV 2
// LSV 3
// CONSTVOLT 4
// CA 5

// SWV test //// total length = 29 + i * 4 bytes
// u8 SWV ID (0)
// u8*16 name
// u16 freq
// u16 start
// u16 stop
// u16 height
// u16 increment
// u8 curr_range
// u16 i (number of measurements)
// - u16 forwardCurrent * i
// - u16 reverseCurrent * i
// u8 SWV ID (0)

// CV test //// total length = 27 + i * 2 bytes
// u8 CV ID (1)
// u8*16 name
// u16 slope
// u16 start
// u16 stop
// u16 scans
// u16 sample_rate
// u8 curr_range
// u16 i (number of measurements)
// - u16 current * i
// u8 CV ID (1)

// ACV test //// total length = 33 + k * 4 bytes
// u8 ACV ID (2)
// u8*16 name
// u16 freq
// u16 height
// u16 cycles
// u16 start
// u16 stop
// u16 increment
// u8 curr_rante 
// u16 k (number of samples)
// - u16 magnitude * k
// - u16 phase * k
// u8 ACV ID (2)

// LSV test //// total length = 29 + i * 2 bytes
// u8 LSV ID (3)
// u8*16 name
// u16 settle
// u16 start
// u16 slope
// u16 sample_rate
// u8 curr_rage
// u16 i (number of samples)
// - u16 current * i
// u8 LSV ID (3)

// CONSTVOLT test -- no output

// CA test //// total length = 30 + i * 2 bytes
// u8 CA ID (5)
// u8*16 name
// u16 wait_time
// u16 step_voltage
// u16 step_width
// u16 quiet_time
// u16 sample_rate
// u8 steps
// u8 curr_range
// u16 length (number of samples)
// - u16 results * length
// u8 CA ID (5)

typedef struct CheapStatProfile{ // legacy struct from the mcu, don't change
	char name[15];
} Profile;

// All the different types of readings you can have //


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

// All raw input is read into this buffer. It is sized to fit the maximum possible transfer.
uint8_t  gRawBytes[15 + kSize_MaxSamplesLSV * 2];

SWV  gSVWInput;
CV   gCVInput;
ACV  gACVInput;
LSV  gLSVInput;
CA   gCAInput;

/********************************** 
  helper functions 
**********************************/

// enables and disables canonical mode for terminal input.
void ttyCanonicalMode(int state)
{
  struct termios ttystate;

  tcgetattr(STDIN_FILENO, &ttystate);

  switch(state)
  {
    case 1:
      ttystate.c_lflag &= ~ICANON;
      ttystate.c_cc[VMIN] = 1;
      break;
    default:
      ttystate.c_lflag |= ICANON;
      break;
  }

  tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}

static void exithandler()
{ 
  printf("Closing the connection.\n"); 
  serialClose(driver.fd); 
  ttyCanonicalMode(0);
}
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
    printf("Error (can't `chown`): %s\n Please run as admin\n", strerror(errno)); 
    exit(EXIT_FAILURE); 
  }
}

int userInputAvailable(void)  
{
  struct timeval tv;
  fd_set fds;
  tv.tv_sec = 0;
  tv.tv_usec = 0;
  FD_ZERO(&fds);
  FD_SET(STDIN_FILENO, &fds);
  return select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
  //return (FD_ISSET(STDIN_FILENO, &fds));
}

/********************************** 
  stateful functions 

  i.e., functions that modify the
  `driver_t driver` struct.
**********************************/

uint16_t swapEndianLong(uint16_t l)
{
  return(((l & 0xFF) << 8) | (l >> 8));
}

void printSWV(SWV *swv)
{
  printf("SWV Reading\n");
  printf("freq: %3d  0x%04x\n", swv->freq, swv->freq);
  printf("start: %3d  0x%04x\n", swv->start, swv->start);
  printf("stop: %4d  0x%04x\n", swv->stop, swv->stop);
  printf("height: %4d  0x%04x\n", swv->height, swv->height);
  printf("increment: %4d  0x%04x\n", swv->increment, swv->increment);
  printf("currRange: %d  0x%02x\n", swv->currRange, swv->currRange);
  printf("numSamples: %d  0x%04x\n", swv->numSamples, swv->numSamples);
}

// parser function pointer 
int (*parse)(uint8_t);

uint16_t pSWVIndex = 0;

int parseSWV(uint8_t b)
{
  gRawBytes[pSWVIndex++] = b;
  printf("%d %02x\n", (pSWVIndex-1), gRawBytes[pSWVIndex-1]);

  if(pSWVIndex < 13)
    return(0);

  if(pSWVIndex == 13)
  {
    printf("Raw bytes:\n");
    for(uint8_t i = 0; i < 13; i++)
      printf("0x%02x ", gRawBytes[i]);

    printf("\n");

    // atmel = big endian - Intel = little endian
    gSVWInput.freq        = gRawBytes[0] << 8 | gRawBytes[1];
    gSVWInput.start       = gRawBytes[2] << 8 | gRawBytes[3];
    gSVWInput.stop        = gRawBytes[4] << 8 | gRawBytes[5];
    gSVWInput.height      = gRawBytes[6] << 8 | gRawBytes[7];
    gSVWInput.increment   = gRawBytes[8] << 8 | gRawBytes[9];
    gSVWInput.currRange   = gRawBytes[10];
    gSVWInput.numSamples  = gRawBytes[11] << 8 | gRawBytes[12];
    printSWV(&gSVWInput);

    return(0);
  }

  // pSWVIndex should always be greater than 14
  uint16_t index = pSWVIndex - 14;
  
  if((index % 4) < 2)
    gSVWInput.forwardCurrentSamples[index / 4] |= gRawBytes[pSWVIndex-1] << (8 * (1 - index % 2));
  else
    gSVWInput.reverseCurrentSamples[index / 4] |= gRawBytes[pSWVIndex-1] << (8 * (1 - index % 2));


  printf("shift - %04x\n", gRawBytes[pSWVIndex-1] << (8 * (index % 2)));
    
  if((index % 4) == 3)
    printf("%d) reverse: %d  forward: %d\n", index / 4
          , gSVWInput.reverseCurrentSamples[index / 4], gSVWInput.forwardCurrentSamples[index / 4]);
    
  
  if((index) == (gSVWInput.numSamples * 4) - 1)
    return(1);
  else
    return(0);
}

uint8_t   gParseState = 0;

uint8_t   gNameIndex = 0;
uint8_t   gName[15] = {0x00};

// Parse CheapStat 
void    CSParse(uint8_t b)
{
  switch(gParseState)
  {
    case 0: // State one choses the parser function based on reading type.
    {
      switch(b)
      {
        case 0:
        {
          printf("Recieving SWV\n");
          // set function pointer ot SWV function.
          pSWVIndex = 0;
          parse = parseSWV;
          gParseState++;
          break;
        }
//        case 1:
//          printf("Recieving CV\n");
//          break;
//        case 2:
//          printf("Recieving ACV\n");
//          break;
//        case 3:
//          printf("Recieving LSV\n");
//          break;
//        case 4:
//          printf("Recieving CONSTVOLT\n");
//          break;
//        case 5:
//          printf("Recieving CA\n");
//          break;
//        case 'z':
//          printf("Recieving Profiles\n");
//          break;
        default:
          printf("Unrecognized Type: %c\n", b);
          break;
      }
      break;
    }
    case 1: // reads in name.
    {
      gName[gNameIndex++] = b;
      if(gNameIndex == 15)
      {
        printf("Name: ");
        for(int i = 0; i < gNameIndex; i++)
          printf("%c", gName[i]);

        printf("\n");
        gParseState++; // increment state
        gNameIndex = 0; // reset state variable
      }
      break;
    }
    case 2: // Passes all data until function returns 0
    {
      if(parse(b))
        gParseState++;

      break;
    }
    case 3: // Waits for closing character based on reading type. Clears state back to 0.
      gParseState = 0;
      printf("Finished parsing type %i\n", b);
      break;
    default:
      // driver crash.
      gParseState = 0;
      break;
  }
}

// loop checks for input on terminal and serial port & passes data to parsers.
void cheapstat_reader(driver_t *driver) 
{
  int8_t c;

  // remove terminal canonical mode for parsing ease.
  ttyCanonicalMode(1);

  // loops until ^C
  while (driver->fd != -1) 
  {
    c = 0;
    if(serialHasChar(driver->fd))
    {
      while(serialHasChar(driver->fd))
      {
        uint8_t b;
        read(driver->fd, &b, 1);
        CSParse(b);
      }
    }

      while(userInputAvailable())
      {
        c = fgetc(stdin);
        if(c != '\r' && c!= '\n')
          write(driver->fd, &c, 1);
      }
  }
}

//@@ FIXME: write a daemonize function
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

  start(&driver);

  ttyCanonicalMode(0);
  return 0;
}

