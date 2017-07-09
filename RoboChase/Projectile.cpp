//
//  Projectile.cpp
//  RoboChase
//
//  Created by nsp on 9/7/17.
//  Copyright © 2017 nspool. All rights reserved.
//

#include "Projectile.hpp"

Projectile::Projectile(SDL_Renderer* renderer, SDL_Point p, Direction direction)
{
  position_ = p;
  renderer_ = renderer;
  direction_ = direction;
  
  // Load the robit
  SDL_Surface* gProjectile = IMG_Load("projectile.png");
  sprite_ = SpriteSheet(gProjectile, 16);
  
  texture_ = SDL_CreateTextureFromSurface(renderer, gProjectile);
}

void Projectile::render(int ticks)
{
  position_.x--;
  SDL_Rect blockLoc = getBounds();
  SDL_RenderCopy(renderer_, texture_, &sprite_.clips[0], &blockLoc);
}

void Projectile::stop(){
  
}

bool Projectile::isObsticle() {
  return false;
}

void Projectile::doCollision(SDL_Rect* rect)
{
  //  printf("Block collision\n");
}
