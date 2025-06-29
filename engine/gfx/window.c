#include "window.h"
#include "../util/assert.h"
#include <GL/glew.h>
#include <SDL2/SDL_video.h>

void window_create(Window *window, const char *title, IVec2 size)
{
	*window = (Window){0};
	assert(SDL_WasInit(SDL_INIT_VIDEO), "SDL Video must be initialized");
	window->window = SDL_CreateWindow(
		title, 
		SDL_WINDOWPOS_CENTERED_DISPLAY(1),
		SDL_WINDOWPOS_CENTERED_DISPLAY(1),
		size.x, size.y,
		SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	assert(window->window, "failed to create sdl window");
	window->glContext = SDL_GL_CreateContext(window->window);
	assert(window->glContext, "failed to create gl context");
	window->size = size;
	window->shouldClose = false;
}

void window_event_process(Window *window, SDL_Event *ev)
{
	switch (ev->type) {
		case (SDL_QUIT):
			window->shouldClose = true;
			return ;
	};
	switch (ev->window.type) {
		case (SDL_WINDOWEVENT_RESIZED):
			window->size = 
				ivec2_of(ev->window.data1, ev->window.data2);
			return ;
	};
}

void window_update(Window *window)
{
	(void)window;
}

void window_commit(Window *window)
{
	glViewport(0, 0, window->size.x, window->size.y);
	SDL_GL_SwapWindow(window->window);
}

void window_destroy(Window *window)
{
	SDL_GL_DeleteContext(window->glContext);
	SDL_DestroyWindow(window->window);
	*window = (Window){0};
}

bool window_shouldclose(Window *window)	{
	return window->shouldClose;
}

bool window_grabstate_get(Window *window) {
	return window->grabState;
}

void window_grabstate_switch(Window *window) {
	window->grabState = !window->grabState;
}
