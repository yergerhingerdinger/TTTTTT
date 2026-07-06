#include "grid.h"
#include <iostream>
#include "colors.h"

Grid::Grid()
{
  numberOfRows = 20;
  numberOfCols = 10;
  cellSize = 30;
  InitializeGrid(); 
  colors = GetCellColors();
}

void Grid::InitializeGrid()
{
  for (int i = 0; i < numberOfRows; i++)
  {
    for (int j = 0; j < numberOfCols; j++)
    {
      grid[i][j] = 0;
    }
  }
}

void Grid::Print()
{
  for (int i = 0; i < numberOfRows; i++)
  {
    for (int j = 0; j < numberOfCols; j++)
    {
      std::cout << grid[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

void Grid::Draw(SDL_Renderer *renderer)
{
  for (int i = 0; i < numberOfRows; i++)
  {
    for (int j = 0; j < numberOfCols; j++)
    {
      int cellValue = grid[i][j];
      //SDL_FRect cellRect = { j * cellSize + 11, i * cellSize + 11, static_cast<float>(cellSize - 1), static_cast<float>(cellSize - 1) };
      SDL_FRect cellRect = { j * cellSize + 180, i * cellSize + 11, static_cast<float>(cellSize - 1), static_cast<float>(cellSize - 1) };
      SDL_SetRenderDrawColor(renderer, colors[cellValue].r, colors[cellValue].g, colors[cellValue].b, colors[cellValue].a);      
      SDL_RenderFillRect(renderer, &cellRect);
    }
  }
}

bool Grid::IsCellOutside(int row, int col)
{
  if (row >= 0 && row < numberOfRows && col >= 0 && col < numberOfCols)
  {
    return false;
  }
  return true;
}

bool Grid::IsCellEmpty(int row, int col)
{
  if(grid[row][col] == 0)
  {
    return true;
  }
  return false;
}

int Grid::ClearFullRows()
{
  int clearedRows = 0;
  for (int i = numberOfRows - 1; i >= 0; i--)
  {
    if (IsRowFull(i))
    {
      ClearRow(i);
      ++clearedRows;
    }
    else if (clearedRows > 0)
    {
      MoveRowDown(i, clearedRows);
    }
  }
  return clearedRows;
}

bool Grid::IsRowFull(int row)
{
  for (int j = 0; j < numberOfCols; j++)
  {
    if (grid[row][j] == 0)
    {
      return false;
    }
  }
  return true;
}

void Grid::ClearRow(int row)
{
  for (int j = 0; j < numberOfCols; j++)
  {
    grid[row][j] = 0;
  }
}

void Grid::MoveRowDown(int row, int numberOfRowsToMoveDown)
{
  for (int j = 0; j < numberOfCols; j++)
  {
    grid[row + numberOfRowsToMoveDown][j] = grid[row][j];
    grid[row][j] = 0;
  }
}
