#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
// refs:
//   - http://www.cprogramming.com/tutorial/cfileio.html
//   - http://www.codingunit.com/c-tutorial-binary-file-io <- this is really good

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

int my_writer() {
  int c;
  FILE *ptr_myfile;
  struct rec my_record;

  ptr_myfile = fopen("test.bin", "wb");

  if (!ptr_myfile) {
    printf("Unable to open file!");
    return 1;
  }

  for (c = 1; c <= 10; c++) {
    my_record.x = c;
    fwrite(&my_record, sizeof(struct rec), 1, ptr_myfile);
  }

  fclose(ptr_myfile);
  return 0;
}

int my_reader() {
  int c;
  FILE *ptr_p;
  profile p;

  ptr_myfile = fopen("capture.bin", "rb");
  
  if (!ptr_p) {
    printf("Unable to open file!");
    return 1;
  }



  printf("%s\n", p.name);
  printf("%d\n", p.



  for (c = 1; c <= 10; c++) {
    fread(&p, sizeof(profile), 1, ptr_p);

    // Here, I need to change `p.name` to `p.type` or `p.op1`, etc, depending
    // on the location of the for loop.
    printf("%s\n", p.name);
  }

  fclose(ptr_myfile);
  return 0;
}

void main() {
  my_reader();
}
