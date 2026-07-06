#pragma once

#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <vector>
#include <map>
#include "position.h"
#include "colors.h"

class Block
{
public:
  Block();
  void Draw(SDL_Renderer *renderer, int XOffset, int YOffset);
  void DrawHoldBlock(SDL_Renderer* renderer, int XPosition, int YPosition);
  void Move(int rows, int cols);
  std::vector<Position> GetCellPositions();
  void Rotate();
  void UndoRotation();
  int id;
  std::map<int, std::vector<Position>> cells;

private:
  int cellSize;
  int rotationState;
  std::vector<SDL_Color> colors;
  int rowOffset, columnOffset;
};
