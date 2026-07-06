#pragma once
#include "grid.h"
#include "blocks.cpp"
#include <SDL3_mixer/SDL_mixer.h>

class Game
{
public:
  Game();
  ~Game();
  void Draw(SDL_Renderer* renderer);
  void HandleInput(SDL_Event* event);  
  void MoveBlockDown();    
  bool gameOver;
  int score;  

private:
  void HoldBlock();
  void MoveBlockLeft();
  void MoveBlockRight();
  Block GetRandomBlock();
  std::vector<Block> GetAllBlocks();
  bool IsBlockOutside();
  void RotateBlock();
  void LockBlock();
  bool DoesBlockFit();
  void Reset();
  void UpdateScore(int linesCleared, int moveDownPoints);
  Grid grid;
  std::vector<Block> blocks;
  Block currentBlock;
  Block nextBlock;  
  Block holdBlock;
};
