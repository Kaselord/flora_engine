#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "tools/renderer.h"

bool game_running = true;
uint prev_tick_count = 0;
// the limit is 1000, it's recommended that 1/this has 3 or less digits after the comma
int target_framerate = 50;


void handle_input(void) {
	SDL_Event current_event;
	while (SDL_PollEvent(&current_event)) {
		if (current_event.type == SDL_QUIT) {
			game_running = false;
			puts("quit input");
		}
	}
}

void game_loop(void) {
	while (game_running == true) {
		float delta = (SDL_GetTicks() - prev_tick_count) / 1000.0;
		float target_delta = 1.0 / target_framerate;
		if (delta > target_delta) {
			prev_tick_count = SDL_GetTicks();

			// -- game logic under here --



			// -- rendering stuffs --
			
			final_render();
		}
		handle_input();
	}
}

int main(void) {
	initialize_rendering();
	SDL_Rect rect = {0, 0, 10, 10};
	game_loop();
	float exit_time = SDL_GetTicks() / 1000.0;
	printf("application quit after running for %f seconds\n", exit_time);
	return 0;
}