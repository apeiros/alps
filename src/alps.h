#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define ALPS_SHOWER_DROPS 100

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

AlpsDrop    alpsdrop(AlpsVector position, AlpsVector velocity);
char        *alpsdrop_inspect(AlpsDrop drop);
void        alpsdrop_print(AlpsDrop drop);
void        alpsdrop_tick(AlpsDrop *drop);