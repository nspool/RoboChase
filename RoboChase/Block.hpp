//
//  Block.hpp
//  RoboChase
//
//  Created by nsp on 1/4/17.
//  Copyright © 2017 nspool. All rights reserved.
//

#ifndef Block_hpp
#define Block_hpp

#include <SDL.h>
#include "SDL_image.h"
#include <SDL_timer.h>

#include "Sprite.hpp"

#endif /* Block_hpp */

class Block : public Sprite
{
public:
  Block(SDL_Renderer* renderer_, SDL_Point p);
  void render(SDL_Rect camera, int ticks);
  void doHit();
  void doCollision(SDL_Rect*);
  bool isObsticle();
  bool isDestructable();
  void action(SDL_Point* target, std::vector<SDL_Rect>* obsticles) { };
private:
  int hitPoints = 10;
  SDL_Renderer* renderer_ = 0;
  SDL_Rect spriteClips_[1];
  SDL_Texture* texture_;
  SDL_Rect getBounds() { return { position_.x, position_.y, 50, 50  }; }
};
