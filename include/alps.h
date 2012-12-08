#ifndef ALPS_H_INCLUDED
#define ALPS_H_INCLUDED


#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "framerate.h"

#define SCREEN_W 1024
#define SCREEN_H 768
#define ALPS_SHOWER_DROPS 1000

typedef struct AlpsVector_  AlpsVector;
typedef struct AlpsDrop_    AlpsDrop;
typedef struct AlpsShower_  AlpsShower;

struct AlpsVector_ {
  float x;
  float y;
};

struct AlpsDrop_ {
  AlpsVector    position;
  AlpsVector    last_position;
  ALLEGRO_COLOR color;
};

struct AlpsShower_ {
  int         intensity;  // drops per tick generated
  int         index;
  float       wind;       // horizontal velocity
  AlpsDrop    drops[ALPS_SHOWER_DROPS];
};

float       frand();

AlpsVector  alpsvector(float x, float y);
AlpsVector  alpsvector_add(AlpsVector a, AlpsVector b);
AlpsVector  alpsvector_multiply(AlpsVector vector, float factor);
char        *alpsvector_inspect(AlpsVector vec);

AlpsDrop    *alpsdrop_init(AlpsDrop *drop, AlpsVector position);
AlpsDrop    *alpsdrop_move(AlpsDrop *drop, float x, float y);
AlpsDrop    *alpsdrop_print(AlpsDrop *drop);
AlpsDrop    *alpsdrop_draw(AlpsDrop *drop);
char        *alpsdrop_inspect(AlpsDrop *drop);

AlpsShower  *alpsshower_initrandom(AlpsShower *shower);
AlpsShower  *alpsshower_each(AlpsShower *shower, AlpsDrop *(*iterator)(AlpsDrop *drop));
AlpsShower  *alpsshower_tick(AlpsShower *shower);
AlpsShower  *alpsshower_draw(AlpsShower *shower);


#endif
