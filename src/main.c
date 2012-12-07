#include "alps.h"
#include <stdlib.h>

#define SCREEN_W 640
#define SCREEN_H 480


int main_loop(ALLEGRO_DISPLAY * display, ALLEGRO_EVENT_QUEUE   * queue) {
  AlpsDrop drop;

  drop      = alpsdrop(alpsvector(165.0, -1.0), alpsvector(0.3, 1.2));
  int busy  = 1;

  ALLEGRO_EVENT event;
  while (busy) {
    // Gather userinput
    while(al_get_next_event(queue, &event)) {
      if(event.type == ALLEGRO_EVENT_KEY_DOWN) { 
        switch(((ALLEGRO_KEYBOARD_EVENT*)&event)->keycode) {
          case ALLEGRO_KEY_ESCAPE:
             busy = 0;
          default:
            break;
        }
      }
    }

    // Update Gamestate
    alpsdrop_tick(&drop);
    if (drop.position.y >= 640) {
      drop = alpsdrop(alpsvector(165.0, -1.0), alpsvector(1.2, 4.3));
    }

    // Drawing
    al_clear_to_color(al_map_rgb(0,0,0));
    al_put_pixel(drop.position.x, drop.position.y, al_map_rgb(128,128,255));
    al_flip_display();
  }
  return busy;
}



int main(void) {
  ALLEGRO_DISPLAY       * display;
  ALLEGRO_EVENT_QUEUE   * queue;
  al_init();
  display = al_create_display(SCREEN_W, SCREEN_H);
  if(!display)  return 1;
  queue   = al_create_event_queue();
  if(!queue)    return 2;
  
  al_install_keyboard();
  al_install_mouse();
  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_mouse_event_source());
  
  main_loop(display, queue);
  
  al_destroy_display(display);
  return 0;
}
