#include "colors.h"


const SDL_Color LIGHT_GREY = { 50,50,50,255 };
const SDL_Color DARK_GREY = { 26, 31, 40, 255 };

const SDL_Color LIGHT_GREEN = { 144, 238, 144, 255 };
const SDL_Color GREEN = { 47, 230, 23, 255 };
const SDL_Color DARK_GREEN = { 44, 100, 44, 255 };

const SDL_Color RED = { 232, 18, 18, 255 };
const SDL_Color ORANGE = { 226, 116, 17, 255 };
const SDL_Color YELLOW = { 237, 234, 4, 255 };
const SDL_Color PURPLE = { 166, 0, 247, 255 };
const SDL_Color CYAN = { 21, 204, 209, 255 };

const SDL_Color BLUE = { 13, 64, 216, 255 };
const SDL_Color LIGHT_BLUE = { 59, 85, 162, 255 };
const SDL_Color DARK_BLUE = { 44, 44, 127, 255 };

const SDL_Color BLACK = { 0, 0, 0, 255 };

std::vector<SDL_Color> GetCellColors()
{
  return { DARK_GREY, GREEN, RED, ORANGE, YELLOW, PURPLE, CYAN, BLUE, BLACK, LIGHT_GREY };
}
