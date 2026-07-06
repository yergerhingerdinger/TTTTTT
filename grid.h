#pragma once
#include <vector>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>

class Grid 
{
public:
  Grid();
  void InitializeGrid();
  void Print();
  void Draw(SDL_Renderer *renderer);
  bool IsCellOutside(int row, int col);
  bool IsCellEmpty(int row, int col);
  int ClearFullRows();
  int grid[20][10];

private:  
  bool IsRowFull(int row);
  void ClearRow(int row);
  void MoveRowDown(int row, int numberOfRowsToMoveDown);
  int numberOfRows;
  int numberOfCols;
  int cellSize;
  std::vector<SDL_Color> colors;
};
