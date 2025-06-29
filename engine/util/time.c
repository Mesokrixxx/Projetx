#include "time.h"
#include <SDL2/SDL_timer.h>

void time_init(Time *time) {
	*time = (Time){0};
	time->start = SDL_GetPerformanceCounter();
	time->frequency = SDL_GetPerformanceFrequency();
}

void time_update(Time *time) {
	unsigned long long now, diff;

	now = SDL_GetPerformanceCounter();
	diff = now - time->start;
	time->last = time->now;
	time->now = (float)diff / (float)time->frequency;
	time->delta = time->now - time->last;
}

float time_delta(Time *time) {
	return (time->delta);
}

float time_now(Time *time) {
	return (time->now);
}
