//
//  main.cpp
//  RoboChase
//
//  Created by nspool on 8/3/17.
//  Copyright © 2017 nspool. All rights reserved.
//

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"

#include <iostream>

#include "Scene.hpp"
#include "Projectile.hpp"
#include "Robit.hpp"
#include "Block.hpp"

#ifdef main
# undef main
#endif /* main */

int main(int argc, char * argv[]) {

  // Initialization

  // TODO: Move all of this common boilerplate into a seperate helper class or library

  SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);

  SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

  if(SDL_Init(SDL_INIT_TIMER|SDL_INIT_VIDEO) != 0) {
    SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Failed to initialise SDL.");
    return EXIT_FAILURE;
  }

  int img_flags = IMG_INIT_PNG | IMG_INIT_JPG;
  if(IMG_Init(img_flags) != img_flags) {
    SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "Failed to initialise SDL_Image.");
    return EXIT_FAILURE;
  }

  SDL_Window* window = SDL_CreateWindow("RoboChase", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

  if(window == nullptr)
  {
    SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "SDL_CreateWindow: SDL_Error: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

  if(renderer == nullptr)
  {
    SDL_LogCritical(SDL_LOG_CATEGORY_ERROR, "SDL_CreateRenderer: SDL Error: %s\n", SDL_GetError());
    return EXIT_FAILURE;
  }

  SDL_SetWindowTitle(window, "RoboChase");

  // TODO: replace with a texture
  SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);

  SDL_Event e;
  const Uint8* keystates = SDL_GetKeyboardState(NULL);

  SDL_Surface* title = IMG_Load("title.png");

  if(title == nullptr)
  {
    SDL_LogError(0, "%s", SDL_GetError());
    return 0;
  }

  while(true) {

    // Render the title screen

    bool start = false;

    SDL_Texture* titleTexture = SDL_CreateTextureFromSurface(renderer, title);
    constexpr SDL_Rect titleLoc = { 0,0, 256, 256 };
    SDL_Rect titleBounds = {SCREEN_WIDTH/2 - titleLoc.w/2, SCREEN_HEIGHT/2 - titleLoc.h/2, titleLoc.w, titleLoc.h};
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, titleTexture, &titleLoc, &titleBounds);
    SDL_RenderPresent(renderer);

    do {

      if(SDL_PollEvent(&e) != 0)
      {
        switch(e.type){
          case SDL_QUIT:
            SDL_DestroyWindow(window);
            SDL_Quit();
            return 0;
            break;
        }
      }

      if(keystates[SDL_SCANCODE_SPACE]) {
        start = true;
      }

    } while(!start);


    // Construct the initial scene

    Scene* scene = new Scene(renderer);

    for(int i = 0; i<5; i++){
        SDL_Point p = {static_cast<int>((int)rand() % LEVEL_WIDTH), static_cast<int>((int)rand() % LEVEL_HEIGHT)};
      scene->addSprite(new Block(renderer, p));
    }

    for(int i = 0; i<5; i++){
        SDL_Point p = { static_cast<int>((int)rand() % LEVEL_WIDTH), static_cast<int>((int)rand() % LEVEL_HEIGHT)};
      scene->addSprite(new Robit(renderer, p));
    }
  SDL_Log("adding player...");
    SDL_Point playerPosition = {100,100};
    scene->addPlayer(new Player(renderer, playerPosition));

    // Main event loop

    constexpr int delta = 2;
    bool quit = false;
    bool endgame = false;
    int lastProjectileTime = 0;

    do {

      if(SDL_PollEvent(&e) != 0)
      {
        switch(e.type){
          case SDL_QUIT:
            quit = true;
            break;
            //Window event occured
          case SDL_WINDOWEVENT:
            switch( e.window.event )
          {
              //Get new dimensions and repaint on window size change
            case SDL_WINDOWEVENT_SIZE_CHANGED:
              camera.w = e.window.data1;
              camera.h = e.window.data2;
              SDL_RenderPresent(renderer);
              break;
            default:
              break;
          }
            break;
        }
      }

      if(keystates[SDL_SCANCODE_UP]) {
        playerPosition.y = playerPosition.y - delta;
      }

      if(keystates[SDL_SCANCODE_DOWN]) {
        playerPosition.y = playerPosition.y + delta;
      }

      if(keystates[SDL_SCANCODE_LEFT]) {
        playerPosition.x = playerPosition.x - delta;
      }

      if(keystates[SDL_SCANCODE_RIGHT]) {
        playerPosition.x = playerPosition.x + delta;
      }

      camera.y = playerPosition.y - (SCREEN_HEIGHT/2);

      if(playerPosition.y < SCREEN_HEIGHT/2) {
        camera.y = 0;
      }

      if(playerPosition.y > (LEVEL_HEIGHT - SCREEN_HEIGHT/2)) {
        camera.y = LEVEL_HEIGHT - SCREEN_HEIGHT;
      }

      camera.x = playerPosition.x - (SCREEN_WIDTH/2);

      if(playerPosition.x < SCREEN_WIDTH/2) {
        camera.x = 0;
      }

      if(playerPosition.x > (LEVEL_WIDTH - SCREEN_WIDTH/2)) {
        camera.x = LEVEL_WIDTH - SCREEN_WIDTH;
      }

      SDL_RenderClear(renderer);
      playerPosition = scene->doEvent(camera, playerPosition);

      SDL_RenderPresent(renderer);

      if(keystates[SDL_SCANCODE_SPACE]) {
        int timeNow = SDL_GetTicks();
        if((lastProjectileTime + 250) < timeNow){
          SDL_Point projectilePosition = playerPosition;
          projectilePosition.y += 15;
          projectilePosition.x += 15;
          scene->addSprite(new Projectile(renderer, projectilePosition, scene->playerDirection));
          lastProjectileTime = SDL_GetTicks();
        }
      }

      bool gameOver = scene->isGameOver();
      bool gameWon = scene->isGameWon();

      if(gameOver){title = IMG_Load("lose.png");}
      if(gameWon){title = IMG_Load("win.png");}

      if(title == 0)
      {
        SDL_LogError(0, "%s", SDL_GetError());
        return 0;
      }

      if(gameWon || gameOver){
        endgame = true;
      }

    } while(!quit && !endgame);

    // Shutdown

    if(quit) {
      break;
    }
  }

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}

