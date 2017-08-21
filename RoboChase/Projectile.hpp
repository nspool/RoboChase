//
//  Projectile.hpp
//  RoboChase
//
//  Created by nsp on 9/7/17.
//  Copyright © 2017 nspool. All rights reserved.
//

#ifndef Projectile_hpp
#define Projectile_hpp

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2/SDL_timer.h>

#include "Sprite.hpp"

#endif /* Projectile_hpp */

class Projectile : public Sprite
{
public:
  Projectile(SDL_Renderer* renderer_, SDL_Point p, Direction d);
  void render(SDL_Rect camera, int ticks);
  void doHit();
  void doCollision(SDL_Rect*);
  bool isObsticle();
  bool isProjectile();
  SDL_Rect getBounds() { return { position_.x, position_.y, 5, 5  }; }
private:
  Direction direction_ = n;
  SDL_Renderer* renderer_ = 0;
  SpriteSheet sprite_;
  SDL_Texture* texture_;
};

