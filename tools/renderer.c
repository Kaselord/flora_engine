#include <stdio.h>
#include <SDL2/SDL.h>

SDL_Window *game_window;
SDL_Renderer *game_renderer;

Uint8 bg_colour_r = 255;
Uint8 bg_colour_g = 0;
Uint8 bg_colour_b = 127;

typedef struct DrawablePolygon {
    SDL_Vertex vertices;
    uint vertex_count;
    // optional!
    SDL_Texture *texture;
} DrawablePolygon;

typedef struct DrawableRect {
    SDL_Rect rect;
    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;
} DrawableRect;

// info on what kinds of drawables should be rendered in what order
char draw_queue_indices[128] = {};
DrawablePolygon draw_queue_polygons[64];
DrawableRect draw_queue_rects[64];
// how much of the polygon drawing space is taken up
uint draw_space_taken_polygon = 0;
// how much of the rect drawing space is taken up
uint draw_space_taken_rect = 0;
// how much drawing space is taken up in total
uint draw_space_taken_global = 0;

uint add_drawable_polygon(SDL_Vertex vertices, uint vertex_count, SDL_Texture *texture) {
    DrawablePolygon polygon = {vertices, vertex_count, texture};
    // add polygon to polygon draw queue
    draw_queue_polygons[draw_space_taken_polygon] = polygon;
    // the next thing in queue to be drawn will be p - polygon
    draw_queue_indices[draw_space_taken_global] = 'p';
    // update length of polygon draw queue
    draw_space_taken_polygon++;
    // update length of global draw queue
    draw_space_taken_global++;
    return draw_space_taken_global - 1;
}

uint add_drawable_rect(SDL_Rect rect_object, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    DrawableRect rect = {rect_object, r, g, b, a};
    // add rect to rect draw queue
    draw_queue_rects[draw_space_taken_rect] = rect;
    // the next thing in queue to be drawn will be r - rect
    draw_queue_indices[draw_space_taken_global] = 'r';
    // update length of polygon draw queue
    draw_space_taken_rect++;
    // update length of global draw queue
    draw_space_taken_global++;
    return draw_space_taken_global - 1;
}

void initialize_rendering(void) {
    game_window = SDL_CreateWindow("flora engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 640, 0);
	game_renderer = SDL_CreateRenderer(game_window, 0, 0);
}

void final_render(void) {
    // draw background
    SDL_SetRenderDrawColor(game_renderer, bg_colour_r, bg_colour_g, bg_colour_b, 255);
    SDL_RenderFillRect(game_renderer, NULL);

    int i_rect = 0;
    int i_polygon = 0;

    for (int i = 0; i < draw_space_taken_global; i++) {

        switch (draw_queue_indices[i]) {
            case 'r':
            // render rectangle
            DrawableRect draw_rect = draw_queue_rects[i_rect];
            SDL_SetRenderDrawColor(game_renderer, draw_rect.r, draw_rect.g, draw_rect.b, draw_rect.a);
            SDL_RenderFillRect(game_renderer, &draw_rect.rect);
            // increment rect index counter
            i_rect++;
            break;
            case 'p':
            puts("polygon");
            // increment polygon index counter
            i_polygon++;
            break;
        }
    }

    // render everything onto the window
    SDL_RenderPresent(game_renderer);
}