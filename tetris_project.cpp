// tetris_project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "game.h"
#include "colors.h"
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>

double lastUpdateTime = 0;

bool EventTriggered(double interval)
{
  double currentTimeInSeconds = SDL_GetTicks() / 1000.0;
  if (currentTimeInSeconds - lastUpdateTime >= interval)
  {
    lastUpdateTime = currentTimeInSeconds;
    return true;
  }
  return false;
}

int main(int argc, char* argv[])
{
  std::srand(static_cast<unsigned int>(std::time(nullptr)));

  constexpr int kScreenWidth = 680;
  constexpr int kScreenHeight = 620;  
   
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_CreateWindowAndRenderer("TETRIS!", kScreenWidth, kScreenHeight, 0, &window, &renderer);
  SDL_SetRenderVSync(renderer, 1);
  TTF_Init();

  std::string fontPath{ "Fonts\\Super Mario Bros. NES.ttf" };
  TTF_Font* font = TTF_OpenFont(fontPath.c_str(), 25);
  TTF_TextEngine* textEngine = TTF_CreateRendererTextEngine(renderer);

  TTF_Text* scoreText = TTF_CreateText(textEngine, font, "Score", 0);  
  TTF_Text* nextText = TTF_CreateText(textEngine, font, "Next", 0);
  TTF_Text* gameOverText = TTF_CreateText(textEngine, font, "GAMEOVER", 0); // TODO: Fix this later - Text goes over the boundaries
  TTF_Text* holdText = TTF_CreateText(textEngine, font, "Hold", 0);
  
  TTF_Text* scoreRenderedText = TTF_CreateText(textEngine, font, "0", 0);
  int scoreRenderedWidth{ 0 };
  
  // Drawing a rectangle for UI
  SDL_FRect scoreRect { 500.0f, 55.0f, 170.0f, 60.0f };
  SDL_FRect nextRect { 500.0f, 215.0f, 170.0f, 180.0f };     
  SDL_FRect holdRect {5.0f, 50.0f, 170.0f, 180.0f };

  bool done = false;

  SDL_Init(SDL_INIT_VIDEO);
  
  // TODO: Get rid of later
  char* cwd = SDL_GetCurrentDirectory();
  if (cwd)
    SDL_Log("Current Working Directory: %s\n", cwd);  

  Game game = Game();

  SDL_Event e;
  SDL_zero(e);

  while (!done)
  {
    while (SDL_PollEvent(&e))
    {
      if (e.type == SDL_EVENT_QUIT)
        done = true;

      if (e.type == SDL_EVENT_KEY_DOWN)
      {
        if (e.key.key == SDLK_ESCAPE) // Exit game with ESC key
          done = true;
        else
          game.HandleInput(&e);
      }
        
    }

    if (EventTriggered(0.2))
    {
      game.MoveBlockDown();
    }      
    // Do game logic, present a frame, etc.

    // Fill the background dark blue    
    SDL_SetRenderDrawColor(renderer, BLACK.r, BLACK.g, BLACK.b, BLACK.a);
    SDL_RenderClear(renderer);
    
    // Render Text
    TTF_DrawRendererText(scoreText, 525, 15);
    TTF_DrawRendererText(nextText, 540, 175);
    TTF_DrawRendererText(holdText, 35, 15);
    if (game.gameOver)
    {
      TTF_DrawRendererText(gameOverText, 500, 450);
    }           

    // Render UI Rectangles
    SDL_SetRenderDrawColor(renderer, LIGHT_GREY.r, LIGHT_GREY.g, LIGHT_GREY.b, LIGHT_GREY.a);    
    SDL_RenderFillRect(renderer, &scoreRect); // SDL_FRect scoreRect{ 320.0f, 55.0f, 170.0f, 60.0f };
    SDL_RenderFillRect(renderer, &nextRect);
    SDL_RenderFillRect(renderer, &holdRect);

    char scoreRender[10];    
    sprintf_s(scoreRender, "%d", game.score);    
    TTF_GetStringSize(font, scoreRender, 0, &scoreRenderedWidth, nullptr);
    TTF_SetTextString(scoreRenderedText, scoreRender, 0);
    TTF_DrawRendererText(scoreRenderedText, (500 + (170 - scoreRenderedWidth) / 2), 70);    

    game.Draw(renderer);

    // Update Screen
    SDL_RenderPresent(renderer);
  }

  // Clean up resources before destroying window
  TTF_DestroyText(scoreText);
  TTF_DestroyRendererTextEngine(textEngine);
  TTF_CloseFont(font);

  SDL_DestroyWindow(window);

  // Clean up
  SDL_Quit();
  return 0;
}
