#include <stdio.h>
#include "alps.h"

int main(int argc, char * argv[]) {
  AlpsDrop drop;
  int i;

  drop  = alpsdrop(alpsvector(165.0, -1.0), alpsvector(1.2, 4.3));

  alpsdrop_print(drop);
  printf("\n");

  for(i=0; i<10; i++) {
    alpsdrop_tick(&drop);
    alpsdrop_print(drop);
    printf("\n");
  }

  return 0;
}
