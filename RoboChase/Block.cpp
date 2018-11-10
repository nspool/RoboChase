//
//  Block.cpp
//  RoboChase
//
//  Created by nsp on 1/4/17.
//  Copyright © 2017 nspool. All rights reserved.
//

#include "Block.hpp"

Block::Block(SDL_Renderer* renderer, SDL_Point p)
{
  position_ = p;
  renderer_ = renderer;

  // Load the robit
  SDL_Surface* gRobits = IMG_Load( "block.png" );

  SDL_Log("Adding a block at %d %d", p.x, p.y);

  if(gRobits == 0)
  {
    SDL_LogError(0, "%s", SDL_GetError());
    return;
  }

  // Setup Robit animation
  spriteClips_[0].x = 0;
  spriteClips_[0].y = 0;
  spriteClips_[0].w = 32;
  spriteClips_[0].h = 32;

  texture_ = SDL_CreateTextureFromSurface(renderer, gRobits);
}

void Block::render(SDL_Rect camera, int ticks)
{
      SDL_Log("Rending block %d %d", position_.x, position_.y);

  SDL_Rect blockLoc = getBounds();
  SDL_Rect result = SDL_Rect();

  if(SDL_IntersectRect(&camera, &blockLoc, &result)== SDL_TRUE) {
    blockLoc.x -= camera.x;
    blockLoc.y -= camera.y;
    SDL_RenderCopy(renderer_, texture_, &spriteClips_[0], &blockLoc);
  }
}

void Block::doHit(){
  hitPoints--;
}

bool Block::isDestructable(){
  return (hitPoints < 1);
}

bool Block::isObsticle() {
  return true;
}

void Block::doCollision(SDL_Rect* rect)
{
//  printf("Block collision\n");
}
