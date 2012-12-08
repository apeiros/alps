#include "framerate.h"

// initializes with 50fps, @5fps, it'll take 4s to drop down to the 5fps
FrameRate *framerate_init(FrameRate *framerate, double current_time) {
  int i;

  for(i=0; i<FRAMERATE_MEASURE_SPAN; i++) {
    framerate->durations[i] = FRAMERATE_INITIAL_DURATION;
  }
  framerate->average        = FRAMERATE_MEASURE_SPAN*FRAMERATE_INITIAL_DURATION;
  framerate->index          = 0;
  framerate->last_time      = current_time;
  framerate->last_duration  = FRAMERATE_INITIAL_DURATION;

  return framerate;
}

FrameRate *framerate_update(FrameRate *framerate, double current_time) {
  double duration;

  duration                                = current_time - framerate->last_time;
  framerate->average                     -= framerate->durations[framerate->index];
  framerate->last_time                    = current_time;
  framerate->last_duration                = duration;
  framerate->durations[framerate->index]  = duration;
  framerate->average                     += duration;
  framerate->index++;
  if (framerate->index == FRAMERATE_MEASURE_SPAN) framerate->index = 0;

  return framerate;
}
int framerate_fps(FrameRate *framerate) {
  return (int)lround(FRAMERATE_MEASURE_SPAN/framerate->average);
}
int framerate_ms_per_frame(FrameRate *framerate) {
  return (int)lround(framerate->average*1000/FRAMERATE_MEASURE_SPAN);
}
