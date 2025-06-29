#pragma once

#include <SDL2/SDL.h>
#include "../math/vectors.h"
#include <stdbool.h>

typedef struct {
	SDL_Window *window;
	SDL_GLContext glContext;
	IVec2 size;
	bool shouldClose, grabState;
}	Window;

void window_create(Window *window, const char *title, IVec2 size);
void window_event_process(Window *window, SDL_Event *ev);
void window_update(Window *window);
void window_commit(Window *window);
void window_destroy(Window *window);
bool window_shouldclose(Window *window);
bool window_grabstate_get(Window *window);
void window_grabstate_switch(Window *window);
