#include <engine.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>

int main(void) {
	Window window;

	SDL_Init(SDL_INIT_VIDEO);
	window_create(&window, "ProjetX", ivec2_of(1080, 720));
	assert(glewInit() == GLEW_OK, "failed to init glew");
	while (!window_shouldclose(&window)) {
		SDL_Event ev;

		while (SDL_PollEvent(&ev)) {
			window_event_process(&window, &ev);
		}
		window_update(&window);
		glClearColor(1, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		window_commit(&window);
	}
	window_destroy(&window);
	SDL_Quit();
	return 0;
}
