#pragma once

#include "dynlist.h"
#include "../gfx/window.h"
#include "../math/vectors.h"
#include <SDL2/SDL.h>

#define INPUT_INVALID (0 << 0)
#define INPUT_PRESSED (1 << 0)
#define INPUT_RELEASED (1 << 1)
#define INPUT_DOWN (1 << 2)
#define INPUT_REPEAT (1 << 3)
#define INPUT_PRESENT (1 << 7)

// give an offset for mouse buttons
#define _INPUT_MOUSEBUTTON_OFFSET SDL_NUM_SCANCODES
enum {
	INPUT_MOUSE_LEFT = _INPUT_MOUSEBUTTON_OFFSET,
	INPUT_MOUSE_MIDDLE,
	INPUT_MOUSE_RIGHT,
	INPUT_MOUSE_BUTTON2,
	INPUT_MOUSE_BUTTON1,
	INPUT_HANDLED_COUNT,
};

typedef struct {
	unsigned char state;
	float last;
} InputInfos;

typedef struct {
	Window *window;
	float now;
	struct {
		IVec2 pos, motion, scroll;
	}	mouse;
	InputInfos buttons[INPUT_HANDLED_COUNT];
	Dynlist clear;
}	Input;

void input_init(Input *input, Window *window);
void input_end(Input *input);
void input_update(Input *input, float now);
void input_event_process(Input *input, SDL_Event *ev);
unsigned char input_state(Input *input, int code);
float input_last(Input *input, int code);
InputInfos input_infos(Input *input, int code);
IVec2 input_mouse_pos(Input *input);
IVec2 input_mouse_scroll(Input *input);
IVec2 input_mouse_motion(Input *input);
