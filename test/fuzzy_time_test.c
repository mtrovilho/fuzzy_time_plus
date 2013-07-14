#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ptbr_time.h"

int
main(int argc, char *argv[])
{
  char *line1 = malloc(32);
  char *line2 = malloc(32);
  char *line3 = malloc(32);
  
  for (int h = 0; h < 24; h++) {
    for (int m = 0; m < 60; m++) {
      fuzzy_time(h, m, line1, line2, line3);
      printf("|=(%02i:%02i)=|\n", h, m);
      printf("|%s\n", line1);
      printf("|%s\n", line2);
      printf("|%s\n", line3);
      printf("|=========|\n");
      printf("\n");
    }
  }
  
  free(line1);
  free(line2);
  free(line3);
}
