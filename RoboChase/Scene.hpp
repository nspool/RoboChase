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
#include <SDL.h>

#endif /* Scene_hpp */

#include "Player.hpp"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int LEVEL_WIDTH = 1024;
const int LEVEL_HEIGHT = 1024;

const int ROBOT_COUNT = 3;

class Scene
{
public:
  Scene(SDL_Renderer* _renderer);
  void addSprite(Sprite* sprite);
  void addPlayer(Player* player);
  void render(int ticks);
  bool isGameOver();
  bool isGameWon();
  SDL_Point doEvent(SDL_Rect camera, SDL_Point nextPos);
  Direction playerDirection = x;
private:
  bool gameOver_ = false;
  int destroyed_ = 0;
  int startTime_ = 0;
  Player* player_;
  SDL_Renderer* renderer_;
  SDL_Point prevPlayerPosition_ = {0,0};
  std::vector<Sprite*> sprites_;
};
