#include <stdio.h>
#include <SDL2/SDL.h>

SDL_Window *game_window;
SDL_Renderer *game_renderer;

Uint8 bg_colour_r = 255;
Uint8 bg_colour_g = 0;
Uint8 bg_colour_b = 127;


void draw_background(Uint8 r, Uint8 g, Uint8 b) {
    SDL_SetRenderDrawColor(game_renderer, r, g, b, 255);
    SDL_RenderFillRect(game_renderer, NULL);
}

void initialize_rendering(void) {
    game_window = SDL_CreateWindow("fig engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 640, 0);
	game_renderer = SDL_CreateRenderer(game_window, 0, 0);
}

void final_render(void) {
    draw_background(bg_colour_r, bg_colour_g, bg_colour_b);
    SDL_RenderPresent(game_renderer);
}