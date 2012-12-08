#include "alps.h"
#include <stdlib.h>

int main_loop(ALLEGRO_DISPLAY * display, ALLEGRO_EVENT_QUEUE   * queue) {
  AlpsShower shower;
  int busy, avgi;
  double current_time, last_time, avg;
  double avga[] = {0.02,0.02,0.02,0.02,0.02,0.02,0.02,0.02,0.02,0.02};

  alpsshower_initrandom(&shower);
  busy      = 1;
  avgi      = 0;
  avg       = 0.2;
  last_time = al_get_time();

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
    alpsshower_tick(&shower);

    // Print framerate to console
    current_time  = al_get_time();
    avga[avgi]    = current_time - last_time;
    last_time     = current_time;
    avg          += avga[avgi];
    avgi++;
    if (avgi == 10) avgi = 0;
    avg -= avga[avgi];

    printf("\r%5d frames (%4dms/frame)", (int)lround(10/avg), (int)lround(avg*100));
    fflush(stdout);

    // Drawing
    al_clear_to_color(al_map_rgb(0,0,0));
    alpsshower_draw(&shower);
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
  printf("\n");
  
  al_destroy_display(display);
  return 0;
}
