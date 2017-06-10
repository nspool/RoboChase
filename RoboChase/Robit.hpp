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

constexpr unsigned int SCREEN_WIDTH = 640;
constexpr unsigned int SCREEN_HEIGHT = 480;
static SDL_Point ORIGIN = {0,0};

#endif /* Robit_hpp */

class Robit : public Sprite
{
public:
  Robit(SDL_Renderer* _renderer, SDL_Point p);
  void render();
  void stop();
  void doCollision(SDL_Rect*);
  void action(SDL_Point* target, std::vector<SDL_Rect>* obsticles);
private:
  int startTime_;
  SDL_Point* currentTarget_ = nullptr;
  double rad_ = M_PI_2;
  double xDelta_ = 0;
  double yDelta_ = 0;
  SDL_Renderer* renderer_;
  SDL_Rect spriteClips_[3];
  SDL_Texture* texture_;
};
