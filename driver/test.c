#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "../lib/profile.h"


/**
 * Tests the protochip collect function.
 *
 * Right now this is just a dummy test file.
 *
 * TODO:
 *  - Simulate reading from a port, like the real cheapstat
 *  - Simulate a few of the different chemical signals, or get sample data and use that
 *  - Instead of rdtest, the function should be called cktest
 *  - Instead of mktest, actually use the collect.c function
 *  - Actually compare the output of mktest/collect.c and rdtest for correctness,
 *    instead of printing it out
 * 
 */

void mktest() {
  FILE *test;
  profile p;

  test = fopen("../tmp/test.bin","wb");
  if (!test) { printf("Unable to open test file!"); }

  strcpy(p.name, "Prof");
  p.type       = 1;
  p.op1        = 100;
  p.op2        = 10;
  p.op3        = 10;
  p.op4        = 10;
  p.op5        = 10;
  p.op6        = 10;
  p.curr_range = 10;

  fwrite(&p, sizeof(p), 1, test);

  fclose(test);
}


void rdtest() {
  FILE *t;
  profile prof;

  t = fopen("../tmp/test.bin", "rb");
  if (!t) { printf("Unable to open test file!"); }

  fread(&prof, sizeof(prof), 1, t);

  fclose(t);

  printf("         Name:  %s\n", prof.name);
  printf("         Type:  %d\n", prof.type);
  printf("        Bytes:  %d\n", sizeof(prof));
  printf("  Operation 1:  %d\n", prof.op1 );
  printf("  Operation 2:  %d\n", prof.op2 );
  printf("  Operation 3:  %d\n", prof.op3 );
  printf("  Operation 4:  %d\n", prof.op4 );
  printf("  Operation 5:  %d\n", prof.op5 );
  printf("  Operation 6:  %d\n", prof.op6 );
  printf("Current Range:  %d\n", prof.curr_range );
}


void main() {
  printf("Making test file.\n");
  mktest();
  printf("Done!\n");

  printf("Reading the test file.\n");
  rdtest();
  printf("Done!\n");
};
