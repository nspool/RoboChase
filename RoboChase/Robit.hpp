//
//  Robit.hpp
//  RoboChase
//
//  Created by nsp on 16/3/17.
//  Copyright © 2017 nspool. All rights reserved.
//

#ifndef Robit_hpp
#define Robit_hpp

#include <vector>

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "Sprite.hpp"

#endif /* Robit_hpp */

class Robit : public Sprite
{
public:
  Robit(SDL_Renderer* _renderer, SDL_Point p);
  void render(SDL_Rect camera, int ticks);
  void doHit();
  void doCollision(SDL_Rect*);
  bool isDestructable();
  void action(SDL_Point* target, std::vector<SDL_Rect>* obsticles);
private:
  SDL_Point* currentTarget_ = {0};
  double rad_ = M_PI_2;
  double xDelta_ = 0;
  double yDelta_ = 0;
  SDL_Renderer* renderer_;
  SpriteSheet sprite_;
};
