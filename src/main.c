#include "alps.h"
#include <stdlib.h>

int main_loop(ALLEGRO_DISPLAY * display, ALLEGRO_EVENT_QUEUE   * queue) {
  AlpsShower shower;
  int busy, avgi;
  FrameRate fps;
  ALLEGRO_COLOR black;

  black = al_map_rgb(0,0,0);
  busy  = 1;

  alpsshower_initrandom(&shower);
  framerate_init(&fps, al_get_time());

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
    framerate_update(&fps, al_get_time());
    if (fps.last_duration < 0.016) { al_rest(0.016-fps.last_duration); }

    printf("\r%5d fps (%4dms/frame)", framerate_fps(&fps), framerate_ms_per_frame(&fps));
    fflush(stdout);

    // Drawing
    al_clear_to_color(black);
    alpsshower_draw(&shower);
    al_flip_display();
  }
  return busy;
}



int main(void) {
  ALLEGRO_DISPLAY       * display;
  ALLEGRO_EVENT_QUEUE   * queue;

  srand(time(NULL));
  al_init();
  display = al_create_display(SCREEN_W, SCREEN_H);
  if(!display)  return 1;
  queue   = al_create_event_queue();
  if(!queue)    return 2;
  
  al_install_keyboard();
  al_install_mouse();
  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_mouse_event_source());
  al_init_primitives_addon();

  main_loop(display, queue);
  printf("\n");
  
  al_destroy_display(display);
  return 0;
}
