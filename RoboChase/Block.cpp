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
  
  // Setup Robit animation
  spriteClips_[0].x = 0;
  spriteClips_[0].y = 0;
  spriteClips_[0].w = 32;
  spriteClips_[0].h = 32;
  
  texture_ = SDL_CreateTextureFromSurface(renderer, gRobits);
}

void Block::render(int ticks)
{
  SDL_Rect blockLoc = getBounds();
  SDL_RenderCopy(renderer_, texture_, &spriteClips_[0], &blockLoc);
}

void Block::doHit(){
  printf("box has been hit!\n");
}

bool Block::isObsticle() {
  return true;
}

void Block::doCollision(SDL_Rect* rect)
{
//  printf("Block collision\n");
}
