#include <engine.h>
#include <GL/glew.h>
#include <SDL2/SDL.h>

int main(void) {
	Window window;
	Time timeManager;
	Input inputManager;

	SDL_Init(SDL_INIT_VIDEO);
	window_create(&window, "ProjetX", ivec2_of(1080, 720));
	assert(glewInit() == GLEW_OK, "failed to init glew");
	time_init(&timeManager);
	input_init(&inputManager, &window);
	while (!window_shouldclose(&window)) {
		SDL_Event ev;

		time_update(&timeManager);
		input_update(&inputManager, time_now(&timeManager));
		window_update(&window);
		while (SDL_PollEvent(&ev)) {
			window_event_process(&window, &ev);
			input_event_process(&inputManager, &ev);
		}
		glClearColor(1, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		window_commit(&window);
	}
	input_end(&inputManager);
	window_destroy(&window);
	SDL_Quit();
	return 0;
}
