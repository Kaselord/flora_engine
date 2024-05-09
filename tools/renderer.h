#pragma once
#include <SDL2/SDL.h>

Uint8 background_colour_r;
Uint8 background_colour_g;
Uint8 background_colour_b;

uint add_drawable_polygon(SDL_Vertex vertices, uint vertex_count, SDL_Texture *texture);
uint add_drawable_rect(SDL_Rect rect_object, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

void mod_drawable_polygon(uint i_polygon, SDL_Vertex vertices, uint vertex_count, SDL_Texture *texture);
void mod_drawable_rect(uint i_rect, SDL_Rect rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

void initialize_rendering(void);
void final_render(void);