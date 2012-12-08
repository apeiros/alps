#ifndef FRAMERATE_INCLUDED
#define FRAMERATE_INCLUDED

#include <math.h>

#define FRAMERATE_MEASURE_SPAN 20
#define FRAMERATE_INITIAL_DURATION 0.2

typedef struct FrameRate_  FrameRate;

struct FrameRate_ {
  double last_time;
  double last_duration;
  double durations[FRAMERATE_MEASURE_SPAN];
  double average;
  int index;
};

FrameRate *framerate_init(FrameRate *framerate, double current_time);
FrameRate *framerate_update(FrameRate *framerate, double current_time);
int framerate_fps(FrameRate *framerate);
int framerate_ms_per_frame(FrameRate *framerate);

#endif