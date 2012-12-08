#include "alps.h"


float frand() {
  return rand()*(1.0/RAND_MAX);
}


/*
 * Returns a new AlpsVector
 */
AlpsVector alpsvector(float x, float y) {
  AlpsVector result = { x, y };

  return result;
}

/*
 * Returns a new AlpsVector with the summed up components of a and b.
 */
AlpsVector alpsvector_add(AlpsVector a, AlpsVector b) {
  return alpsvector(a.x+b.x,  a.y+b.y);
}

AlpsVector alpsvector_add_x_y(AlpsVector a, float x, float y) {
  return alpsvector(a.x+x,  a.y+y);
}

AlpsVector alpsvector_multiply(AlpsVector vector, float factor) {
  return alpsvector(vector.x*factor,  vector.y*factor);
}

char *alpsvector_inspect(AlpsVector vec)
{
    char *result=malloc(256); // overkill
    sprintf(result, "Vector<%.2lf %.2lf>", vec.x, vec.y);

    return result;
}



AlpsDrop *alpsdrop_init(AlpsDrop *drop, AlpsVector position) {
  drop->position = position;
  drop->color    = al_map_rgb(128,128,255);

  return drop;
}

AlpsDrop *alpsdrop_move(AlpsDrop *drop, float x, float y) {
  if (drop->position.y > SCREEN_W) {
    drop->position = alpsvector(rand()%(2*SCREEN_W)-SCREEN_W, -10.0);
  }
  drop->last_position = drop->position;
  drop->position      = alpsvector_add_x_y(drop->position, x, y);

  return drop;
}
AlpsDrop *alpsdrop_draw(AlpsDrop *drop) {
  if (drop->position.y > 0) {
    al_draw_line(
      drop->last_position.x, drop->last_position.y,
      drop->position.x,      drop->position.y,
      drop->color,
      1.5
    );
  }

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
  sprintf(result, "#<Drop x: %.0lf, y: %.0lf>", drop->position.x, drop->position.y);

  return result;
}


AlpsShower *alpsshower_initrandom(AlpsShower *shower) {
  int i;
  shower->intensity = (rand()%10) + 5;
  shower->index     = 0;
  shower->wind      = 4.0*(frand()-0.5);

  for(i=0; i<ALPS_SHOWER_DROPS; i++) {
    alpsdrop_init(shower->drops+i, alpsvector(rand()%(2*SCREEN_W)-(SCREEN_W/2), -(rand()%(SCREEN_H*2)))); 
  }
  alpsshower_tick(shower);

  return shower;
}
AlpsShower *alpsshower_each(AlpsShower *shower, AlpsDrop *(*iterator)(AlpsDrop *drop)) {
  int i;
  for(i=0; i<ALPS_SHOWER_DROPS; i++) iterator(shower->drops+i);

  return shower;
}

AlpsShower *alpsshower_tick(AlpsShower *shower) {
  int i;
  for(i=0; i<ALPS_SHOWER_DROPS; i++) {
    alpsdrop_move(shower->drops+i, shower->wind, 4.5);
  }

  return shower;
}
AlpsShower *alpsshower_draw(AlpsShower *shower) {
  return alpsshower_each(shower, &alpsdrop_draw);
}
