#pragma once
#include <SDL3/SDL_pixels.h>
#include <vector>

extern const SDL_Color LIGHT_GREY;
extern const SDL_Color DARK_GREY;
extern const SDL_Color GREEN;
extern const SDL_Color RED;
extern const SDL_Color ORANGE;
extern const SDL_Color YELLOW;
extern const SDL_Color PURPLE;
extern const SDL_Color CYAN;
extern const SDL_Color BLUE;
extern const SDL_Color LIGHT_BLUE;
extern const SDL_Color DARK_BLUE;
extern const SDL_Color BLACK;

std::vector<SDL_Color> GetCellColors();
