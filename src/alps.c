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



AlpsDrop *alpsdrop_init(AlpsDrop *drop, AlpsVector p, AlpsVector v) {
  drop->position = p;
  drop->velocity = v;

  return drop;
}

AlpsDrop *alpsdrop_initrandom(AlpsDrop *drop) {
  AlpsVector p = alpsvector(rand() % SCREEN_W, 0.0);
  AlpsVector v = alpsvector(0.0, 1 + ((double)(rand() % 10))/10);

  return alpsdrop_init(drop, p, v);
}

AlpsDrop *alpsdrop_tick(AlpsDrop *drop) {
  drop->position = alpsvector_add(drop->position, drop->velocity);
  if (drop->position.y >= SCREEN_H) {
    alpsdrop_initrandom(drop);
  }

  return drop;
}
AlpsDrop *alpsdrop_draw(AlpsDrop *drop) {
  ALLEGRO_COLOR DropColor;
  DropColor = al_map_rgb(128,128,255);

  al_draw_line(
    drop->position.x, drop->position.y,
    drop->position.x, drop->position.y+4,
    DropColor,
    1
  );

  return drop;
}

AlpsDrop *alpsdrop_print(AlpsDrop *drop) {
  char *s;
  s = alpsdrop_inspect(drop);
  printf("%s", s);
  free(s);

  return drop;
}
char *alpsdrop_inspect(AlpsDrop *drop) {
  char *result=malloc(256); // overkill
  sprintf(result, "#<Drop x: %.0lf, y: %.0lf, +x: %.2lf, +y: %.2lf>", drop->position.x, drop->position.y, drop->velocity.x, drop->velocity.y);

  return result;
}


AlpsShower *alpsshower_initrandom(AlpsShower *shower) {
  int i;
  shower->intensity  = 0;                // use later
  shower->abberation = 0.0;              // use later
  shower->velocity   = alpsvector(0, 0); // use later

  return alpsshower_each(shower, &alpsdrop_initrandom);
}
AlpsShower *alpsshower_each(AlpsShower *shower, AlpsDrop *(*iterator)(AlpsDrop *drop)) {
  int i;
  for(i=0; i<ALPS_SHOWER_DROPS; i++) iterator(shower->drops+i);

  return shower;
}

AlpsShower *alpsshower_tick(AlpsShower *shower) {
  return alpsshower_each(shower, &alpsdrop_tick);
}
AlpsShower *alpsshower_draw(AlpsShower *shower) {
  return alpsshower_each(shower, &alpsdrop_draw);
}
