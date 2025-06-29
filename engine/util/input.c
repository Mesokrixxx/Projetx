#include "input.h"
#include "assert.h"

void input_init(Input *input, Window *window)
{
	*input = (Input){0};

	input->window = window;
	dynlist_create(&input->clear, sizeof(int), 32);
	for (int i = 0; i < INPUT_HANDLED_COUNT; i++)
		input->buttons[i].state = INPUT_PRESENT;
}

void input_end(Input *input)
{
	dynlist_destroy(&input->clear);
	*input = (Input){0};
}

void input_update(Input *input, float now)
{
	static bool grabState;
	bool currentGrabState;

	input->now = now;
	input->mouse.motion = ivec2_of(0, 0);
	input->mouse.scroll = ivec2_of(0, 0);
	dynlist_foreach(&input->clear,
		input->buttons[*(int*)data].state &= ~(INPUT_PRESSED | INPUT_RELEASED);
	);
	dynlist_clear(&input->clear);
	currentGrabState = window_grabstate_get(input->window);
	if (grabState != currentGrabState) {
		grabState = currentGrabState;
		SDL_SetWindowMouseGrab(
			input->window->window, grabState ? SDL_TRUE : SDL_FALSE);
		SDL_ShowCursor(grabState ? SDL_FALSE : SDL_TRUE);
		SDL_SetRelativeMouseMode(grabState ? SDL_TRUE : SDL_FALSE);
	}
}

void input_event_process(Input *input, SDL_Event *ev)
{
	bool repeat = false;
	bool down;
	int code;

	switch (ev->type) {
		case (SDL_MOUSEMOTION):
			input->mouse.motion =
				ivec2_add(input->mouse.motion,
					ivec2_of(ev->motion.xrel, ev->motion.yrel));
			input->mouse.pos = 
				ivec2_of(ev->motion.x, input->window->size.y - ev->motion.y - 1);
			break;
		case (SDL_MOUSEWHEEL):
			input->mouse.scroll = 
				ivec2_add(input->mouse.scroll, ivec2_of(ev->wheel.preciseX, ev->wheel.preciseY));
			break;
		case (SDL_MOUSEBUTTONDOWN):
		case (SDL_MOUSEBUTTONUP):
		case (SDL_KEYDOWN):
		case (SDL_KEYUP):
			if (ev->type == SDL_KEYDOWN
				|| ev->type == SDL_KEYUP)
			{
				down = ev->type == SDL_KEYDOWN;
				repeat = ev->key.repeat;
				code = ev->key.keysym.scancode;
			} else if (ev->type == SDL_MOUSEBUTTONDOWN
				|| ev->type == SDL_MOUSEBUTTONUP) 
			{
				down = ev->type == SDL_MOUSEBUTTONDOWN;
				code = _INPUT_MOUSEBUTTON_OFFSET + ev->button.button - 1;
			}
			else
				assert(false, "switch statement error");
			if (code >= INPUT_HANDLED_COUNT) {
				fprintf(stderr, "input not handled: %d\n", code);
				break ;
			}
			
			unsigned char lastState = input->buttons[code].state;
			float lastProcess = input->buttons[code].last;

			if (lastProcess == input->now && repeat)
				break ; // Can't have repeat and pressed at the same time
			
			unsigned char newState = INPUT_PRESENT;

			if (repeat)
				newState |= INPUT_DOWN | INPUT_REPEAT;
			else if (down) {
				if (!(lastState & INPUT_DOWN)) {
					newState |= INPUT_PRESSED;
					dynlist_append(&input->clear, &code);
				}
				newState |= INPUT_DOWN;
			} else if (lastState & INPUT_DOWN) {
				newState |= INPUT_RELEASED;
				dynlist_append(&input->clear, &code);
			}
			if ((newState & INPUT_PRESSED) || (newState & INPUT_RELEASED))
				input->buttons[code].last = input->now;
			input->buttons[code].state = newState;
			break ;
	}
}

unsigned char input_state(Input *input, int code)
{
	assert(code < INPUT_HANDLED_COUNT, "unknow input %d", code);
	return (input->buttons[code].state);
}

float input_last(Input *input, int code)
{
	assert(code < INPUT_HANDLED_COUNT, "unknow input %d", code);
	return (input->buttons[code].last);
}

InputInfos input_infos(Input *input, int code)
{
	assert(code < INPUT_HANDLED_COUNT, "unknow input %d", code);
	return (input->buttons[code]);
}

IVec2 input_mouse_pos(Input *input)
{
	return (input->mouse.pos);
}

IVec2 input_mouse_scroll(Input *input)
{
	return (input->mouse.scroll);
}

IVec2 input_mouse_motion(Input *input)
{
	return (input->mouse.motion);
}
