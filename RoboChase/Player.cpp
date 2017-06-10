//
//  Player.cpp
//  RoboChase
//
//  Created by nsp on 2/6/17.
//  Copyright © 2017 nspool. All rights reserved.
//

#include "Player.hpp"


Player::Player(SDL_Renderer* renderer, SDL_Point p)
{
  renderer_ = renderer;
  position_ = p;
  
  // Load the robit
  SDL_Surface* gPlayer = IMG_Load("player.png");
  
  if(gPlayer == 0)
  {
//    printf("Failed to load images! SDL_Error: %s\n", SDL_GetError());
  }
  
  // Setup Robit animation
  spriteClips_[0].x = 0;
  spriteClips_[0].y = 0;
  spriteClips_[0].w = 21;
  spriteClips_[0].h = 31;
  
  texture_ = SDL_CreateTextureFromSurface( renderer, gPlayer );
}

void Player::action(SDL_Point* target, std::vector<SDL_Rect>* obsticles)
{
  position_.x = target->x;
  position_.y = target->y;
}

void Player::render()
{
  SDL_Rect bounds = getBounds();
  SDL_RenderCopy(renderer_, texture_, &spriteClips_[0], &bounds );
}
