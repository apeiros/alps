#ifndef ALPS_H_INCLUDED
#define ALPS_H_INCLUDED


#define SCREEN_W 1024
#define SCREEN_H 768
#define ALPS_SHOWER_DROPS 1000

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

typedef struct AlpsVector_  AlpsVector;
typedef struct AlpsDrop_    AlpsDrop;
typedef struct AlpsShower_  AlpsShower;

struct AlpsVector_ {
  double x;
  double y;
};

struct AlpsDrop_ {
  AlpsVector position;
  AlpsVector velocity;
};

struct AlpsShower_ {
  int         intensity;
  float       abberation;
  AlpsVector  velocity;
  AlpsDrop    drops[ALPS_SHOWER_DROPS];
};

AlpsVector  alpsvector(double x, double y);
AlpsVector  alpsvector_add(AlpsVector a, AlpsVector b);
char        *alpsvector_inspect(AlpsVector vec);

AlpsDrop    *alpsdrop_init(AlpsDrop *drop, AlpsVector p, AlpsVector v);
AlpsDrop    *alpsdrop_initrandom(AlpsDrop *drop);
AlpsDrop    *alpsdrop_print(AlpsDrop *drop);
AlpsDrop    *alpsdrop_draw(AlpsDrop *drop);
AlpsDrop    *alpsdrop_tick(AlpsDrop *drop);
char        *alpsdrop_inspect(AlpsDrop *drop);

AlpsShower  *alpsshower_initrandom(AlpsShower *shower);
AlpsShower  *alpsshower_each(AlpsShower *shower, AlpsDrop *(*iterator)(AlpsDrop *drop));
AlpsShower  *alpsshower_tick(AlpsShower *shower);
AlpsShower  *alpsshower_draw(AlpsShower *shower);


#endif
