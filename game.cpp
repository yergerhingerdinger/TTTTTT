#include "game.h"
#include <random>
#include <SDL3/SDL.h>

Game::Game() {
  grid = Grid();
  blocks = GetAllBlocks();
  currentBlock = GetRandomBlock();
  nextBlock = GetRandomBlock();
  gameOver = false;      
}

Game::~Game()
{
    // TODO: Add audio/music/sounds
}

Block Game::GetRandomBlock()
{
  if (blocks.empty())
  {
    blocks = GetAllBlocks();
  }
  int randomIndex = rand() % blocks.size();
  Block block = blocks[randomIndex];
  blocks.erase(blocks.begin() + randomIndex);
  return block;  
}

std::vector<Block> Game::GetAllBlocks()
{
  return { IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock() };
}

void Game::Draw(SDL_Renderer *renderer)
{
  grid.Draw(renderer);
  currentBlock.Draw(renderer, 180, 11); // TODO: remove comment later but original is (11, 11)
  switch (nextBlock.id)
  {
  case 3:
    nextBlock.Draw(renderer, 435, 290);
    break;
  case 4:
    nextBlock.Draw(renderer, 435, 280);
    break;
  default:
    nextBlock.Draw(renderer, 450, 270);
    break;
  }
  if (holdBlock.id) // SDL_FRect holdRect {5.0f, 50.0f, 170.0f, 180.0f };
  {
    holdBlock.Draw(renderer, 0, 0);    
  }
}

void Game::HandleInput(SDL_Event* event)
{
  if (gameOver && (event->type == SDL_EVENT_KEY_DOWN != 0)) 
  {
    gameOver = false;
    Reset();
  }

  switch (event->key.key)
  {
    case SDLK_LEFT:
      MoveBlockLeft();
      break;
    case SDLK_RIGHT:
      MoveBlockRight();
      break;
    case SDLK_DOWN:
      MoveBlockDown();
      UpdateScore(0, 1);
      break;
    case SDLK_UP:
      RotateBlock();
      break;
    case SDLK_LSHIFT:
      printf("Checking left shift: ");
      HoldBlock();
      break;
  }
}

void Game::HoldBlock()
{  
  if (!holdBlock.id)
  {
    holdBlock = currentBlock;
    currentBlock = nextBlock;
  }
  else
  {
    printf("Checking here: ");
    holdBlock = currentBlock;
    currentBlock = holdBlock;
    printf("", holdBlock.id);
  }  
}

void Game::MoveBlockLeft()
{
  if (!gameOver)
  {
    currentBlock.Move(0, -1);
    if (IsBlockOutside() || DoesBlockFit() == false)
    {
      currentBlock.Move(0, 1);
    }
  }  
}

void Game::MoveBlockRight()
{
  if (!gameOver)
  {
    currentBlock.Move(0, 1);
    if (IsBlockOutside() || DoesBlockFit() == false)
    {
      currentBlock.Move(0, -1);
    }
  }  
}

void Game::MoveBlockDown()
{
  if (!gameOver)
  {
    currentBlock.Move(1, 0);
    if (IsBlockOutside() || DoesBlockFit() == false)
    {
      currentBlock.Move(-1, 0);
      LockBlock();
    }
  }  
}

bool Game::IsBlockOutside()
{
  std::vector<Position> tiles = currentBlock.GetCellPositions();
  for (Position item : tiles)
  {
    if (grid.IsCellOutside(item.row, item.col))
    {
      return true;
    }
  }
  return false;
}

void Game::RotateBlock()
{
  if (!gameOver)
  {
    currentBlock.Rotate();
    if (IsBlockOutside())
    {
      currentBlock.UndoRotation();
    }
  }  
}

void Game::LockBlock()
{
  std::vector<Position> tiles = currentBlock.GetCellPositions();
  for (Position item : tiles)
  {
    grid.grid[item.row][item.col] = currentBlock.id;
  }
  currentBlock = nextBlock;
  // Game Over Check
  if (DoesBlockFit() == false)
  {
    gameOver = true;
  }

  nextBlock = GetRandomBlock();
  printf("Next Block ID: %d\n", nextBlock.id);
  grid.ClearFullRows();
  int rowsCleared = grid.ClearFullRows();
  UpdateScore(rowsCleared, 0);  
}

bool Game::DoesBlockFit()
{
  std::vector<Position> tiles = currentBlock.GetCellPositions();
  for (Position item : tiles)
  {
    if (grid.IsCellEmpty(item.row, item.col) == false)
    {
      return false;
    }
  }
  return true;
}

void Game::Reset()
{
  grid.InitializeGrid();
  blocks = GetAllBlocks();
  currentBlock = GetRandomBlock();
  nextBlock = GetRandomBlock();
  score = 0;
}

void Game::UpdateScore(int linesCleared, int moveDownPoints)
{
  switch (linesCleared)
  {
  case 1:
      score += 100;
      break;
  case 2:
      score += 300;
      break;
  case 3:
      score += 500;
      break;
  default:      
      break;
  }

  score += moveDownPoints;
}
