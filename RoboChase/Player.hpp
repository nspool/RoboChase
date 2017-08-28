//
//  Player.hpp
//  RoboChase
//
//  Created by nsp on 2/6/17.
//  Copyright © 2017 nspool. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include <vector>

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "Sprite.hpp"

#endif /* Player_hpp */

class Player : public Sprite
{
public:
  Player(SDL_Renderer* renderer, SDL_Point p);
  void move(int direction);
  void render(SDL_Rect camera, int ticks);
  void action(SDL_Point* target, std::vector<SDL_Rect>* obsticles);
  void captured();
  bool moving_ = false;
  Direction direction_ = x;
private:
  SDL_Renderer* renderer_;
  SpriteSheet sprite_;
};
