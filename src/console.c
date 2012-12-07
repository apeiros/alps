#include <stdio.h>
#include "alps.h"

int main(int argc, char * argv[]) {
  AlpsVector pos, vel;
  AlpsDrop drop;
  int i;

  pos   = alpsvector(165.0, -1.0);
  vel   = alpsvector(1.2, 4.3);
  drop  = alpsdrop(pos, vel);

  alpsdrop_print(drop);
  printf("\n");

  for(i=0; i<10; i++) {
    alpsdrop_tick(&drop);
    alpsdrop_print(drop);
    printf("\n");
  }

  return 0;
}
