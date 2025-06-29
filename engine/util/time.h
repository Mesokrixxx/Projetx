#pragma once

typedef struct {
	unsigned long long frequency, start;
	float now, last;
	float delta;
}	Time;

void time_init(Time *time);
void time_update(Time *time);
float time_delta(Time *time);
float time_now(Time *time);
