#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "../lib/profile.h"
// refs:
//   - http://www.cprogramming.com/tutorial/cfileio.html
//   - http://www.codingunit.com/c-tutorial-binary-file-io <- this is really good

void main() {
  FILE *fp;
  profile p;

  // open our captured data
  fp = fopen("../capture.bin", "rb");
  if (!fp) { printf("Unable to open file!"); }

  fread(&p, sizeof(p), 1, fp);
  fclose(fp);

  printf("           Name:  %s\n", p.name);
  printf("           Type:  %d\n", p.type);
  printf("    Operation 1:  %d\n", p.op1 );
  printf("    Operation 2:  %d\n", p.op2 );
  printf("    Operation 3:  %d\n", p.op3 );
  printf("    Operation 4:  %d\n", p.op4 );
  printf("    Operation 5:  %d\n", p.op5 );
  printf("    Operation 6:  %d\n", p.op6 );
  printf("  Current Range:  %d\n", p.curr_range );
}
