#include <stdio.h>
#include <SDL2/SDL.h>

SDL_Window *game_window;
SDL_Renderer *game_renderer;

Uint8 bg_colour_r = 255;
Uint8 bg_colour_g = 0;
Uint8 bg_colour_b = 127;

typedef struct DrawablePolygon {
    SDL_Vertex *vertices;
    int vertex_count;
    // optional!
    SDL_Texture *texture;
} DrawablePolygon;

typedef struct DrawableRect {
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
    SDL_Rect rect;
} DrawableRect;

DrawablePolygon draw_queue_polygons[64];
DrawableRect draw_queue_rects[64];

void initialize_rendering(void) {
    game_window = SDL_CreateWindow("fire engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 640, 0);
	game_renderer = SDL_CreateRenderer(game_window, 0, 0);
}

void final_render(void) {
    // draw background
    SDL_SetRenderDrawColor(game_renderer, bg_colour_r, bg_colour_g, bg_colour_b, 255);
    SDL_RenderFillRect(game_renderer, NULL);

    // render everything onto the window
    SDL_RenderPresent(game_renderer);
}