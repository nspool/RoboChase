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
  constexpr int v = 7;
  switch(direction_) {
    case e:
      position_.x -= v; break;
    case w:
      position_.x += v; break;
    case s:
      position_.y += v; break;
    case n:
      position_.y -= v; break;
    default:
      position_.x -= v; break;
      break;
  }
  
  SDL_Rect blockLoc = getBounds();
  SDL_RenderCopy(renderer_, texture_, &sprite_.clips[0], &blockLoc);
}

void Projectile::doHit(){
  
}

bool Projectile::isObsticle() {
  return false;
}

bool Projectile::isProjectile() {
  return true;
}

void Projectile::doCollision(SDL_Rect* rect)
{
  //  printf("Block collision\n");
}
