#include "block.h"

Block::Block()
{
  cellSize = 30;
  rotationState = 0;
  colors = GetCellColors();
  rowOffset = 0, columnOffset = 0;
}

// TODO: Draw method currently draws hold block based on the position of currentblock
void Block::Draw(SDL_Renderer* renderer, int XOffset, int YOffset)
{
  std::vector<Position> tiles = GetCellPositions();
  for (Position item : tiles)
  {
    SDL_FRect cellRect = { item.col * cellSize + XOffset, item.row * cellSize + YOffset, static_cast<float>(cellSize - 1), static_cast<float>(cellSize - 1) };
    SDL_SetRenderDrawColor(renderer, colors[id].r, colors[id].g, colors[id].b, colors[id].a);
    /*if (id)*/
    SDL_RenderFillRect(renderer, &cellRect);
  }
}

void Block::DrawHoldBlock(SDL_Renderer* renderer, int XPosition, int YPosition)
{
  
}

void Block::Move(int rows, int cols)
{
  rowOffset += rows;
  columnOffset += cols;
}

std::vector<Position> Block::GetCellPositions()
{
  std::vector<Position> tiles = cells[rotationState];
  std::vector<Position> movedTiles;
  for (Position item : tiles)
  {
    Position newPosition = Position(item.row + rowOffset, item.col + columnOffset);
    movedTiles.push_back(newPosition);
  }
  return movedTiles;
}

void Block::Rotate()
{
  //rotationState = (rotationState + 1) % cells.size();
  rotationState++;
  if (rotationState == cells.size())
  {
    rotationState = 0;
  }
}

void Block::UndoRotation()
{
  rotationState--;
  if (rotationState < 0)
  {
    rotationState = cells.size() - 1;
  }
}
