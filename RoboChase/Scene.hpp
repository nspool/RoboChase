//
//  Scene.hpp
//  RoboChase
//
//  Created by nsp on 29/3/17.
//  Copyright © 2017 nspool. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

#endif /* Scene_hpp */

//#include "Sprite.hpp"
#include "Player.hpp"

class Scene
{
public:
  Scene(SDL_Renderer* _renderer);
  void addSprite(Sprite* sprite);
  void addPlayer(Player* player);
  void render(int ticks);
  SDL_Point doEvent(SDL_Point nextPos);
private:
  int startTime_;
  Player* player_;
  SDL_Renderer* renderer_;
  SDL_Point prevPlayerPosition_ = {0,0};
  std::vector<Sprite*> sprites_;
};
