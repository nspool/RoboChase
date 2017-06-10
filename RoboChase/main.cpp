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
#include "Robit.hpp"
#include "Block.hpp"

int main(int argc, const char * argv[]) {
  
  // Initialization
  
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0 || IMG_Init( IMG_INIT_PNG | IMG_INIT_JPG) < 0) {
    std::cerr << "Failed to Initialize SDL!" << std::endl;
    return 1;
  }
  
  SDL_Window* window = SDL_CreateWindow("RoboChase", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_MAXIMIZED);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  
  if(window == 0 || renderer == 0) {
    std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
    return 1;
  }
  
  SDL_SetWindowTitle(window, "RoboChase");
  SDL_SetRenderDrawColor(renderer, 0x37, 0xFD, 0xFC, 0xFF);
  
  
  // Construct the initial scene
  
  Scene* scene = new Scene(renderer);
  
  for(int i = 0; i<6; i++){
    SDL_Point p = {(int)arc4random_uniform(SCREEN_WIDTH), (int)arc4random_uniform(SCREEN_HEIGHT)};
    scene->addSprite(new Block(renderer, p));
  }
  
  for(int i = 0; i<3; i++){
    SDL_Point p = {(int)arc4random_uniform(SCREEN_WIDTH), (int)arc4random_uniform(SCREEN_HEIGHT)};
    scene->addSprite(new Robit(renderer, p));
  }
  
  SDL_Point playerPosition = {50,50};
  scene->addPlayer(new Player(renderer, playerPosition));
  
  
  // Main event loop
  
  SDL_Event e;
  bool quit = false;
  const Uint8* keystates = SDL_GetKeyboardState(NULL);
  constexpr int delta = 5;
  
  do {
    
    if(SDL_PollEvent(&e) != 0)
    {
      switch(e.type){
        case SDL_QUIT:
          quit = true;
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
    
    SDL_RenderClear(renderer);
    playerPosition = scene->doEvent(playerPosition);
    SDL_RenderPresent(renderer);
    
  } while(!quit);
  
  
  // Shutdown
  
  SDL_DestroyWindow(window);
  SDL_Quit();
  
  return 0;
}

