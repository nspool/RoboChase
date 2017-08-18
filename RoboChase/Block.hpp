//
//  Block.hpp
//  RoboChase
//
//  Created by nsp on 1/4/17.
//  Copyright © 2017 nspool. All rights reserved.
//

#ifndef Block_hpp
#define Block_hpp

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "Sprite.hpp"

#endif /* Block_hpp */

class Block : public Sprite
{
public:
  Block(SDL_Renderer* renderer_, SDL_Point p);
  void render(int ticks);
  void doHit();
  void doCollision(SDL_Rect*);
  bool isObsticle();
  bool isDestructable();
private:
  int hitPoints = 2;
  SDL_Renderer* renderer_ = 0;
  SDL_Rect spriteClips_[1];
  SDL_Texture* texture_;
  SDL_Rect getBounds() { return { position_.x, position_.y, 50, 50  }; }
};
