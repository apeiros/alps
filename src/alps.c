#include "alps.h"

/*
 * Returns a new AlpsVector
 */
AlpsVector alpsvector(double x, double y) {
  AlpsVector result = { x, y };

  return result;
}

/*
 * Returns a new AlpsVector with the summed up components of a and b.
 */
AlpsVector alpsvector_add(AlpsVector a, AlpsVector b) {
  return alpsvector(a.x+b.x,  a.y+b.y);
}

char *alpsvector_inspect(AlpsVector vec)
{
    char *result=malloc(256); // overkill
    sprintf(result, "Vector<%.2lf %.2lf>", vec.x, vec.y);

    return result;
}



AlpsDrop alpsdrop(AlpsVector position, AlpsVector velocity) {
  AlpsDrop drop = {position, velocity};

  return drop;
}

char *alpsdrop_inspect(AlpsDrop drop) {
  char *result=malloc(256); // overkill
  sprintf(result, "#<Drop x: %.0lf, y: %.0lf, +x: %.2lf, +y: %.2lf>", drop.position.x, drop.position.y, drop.velocity.x, drop.velocity.y);

  return result;
}
void alpsdrop_print(AlpsDrop drop) {
  char *s;
  s = alpsdrop_inspect(drop);
  printf("%s", s);
  free(s);
}