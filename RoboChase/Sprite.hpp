//
//  Sprite.hpp
//  RoboChase
//
//  Created by nsp on 25/4/17.
//  Copyright © 2017 nspool. All rights reserved.
//

#ifndef Sprite_hpp
#define Sprite_hpp

#include <vector>
#include <SDL2/SDL.h>

#include "SpriteSheet.hpp"

enum Direction { x, n, s, e, w, nw, ne, sw, se };

struct Sprite
{
public:
  virtual bool isObsticle() { return true; }
  virtual void render(int ticks) {}
  virtual void stop() {}
  virtual void doCollision(SDL_Rect* rect) {}
  virtual void action(SDL_Point* target, std::vector<SDL_Rect>* obsticles) {};
  virtual SDL_Rect getBounds() { return { position_.x, position_.y, 21, 31 }; }
  SDL_Point position_ = {0, 200};
};

#endif /* Sprite_hpp */
