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
  
  if(gPlayer == 0) { return; }
  
  // Setup Player animation
  spriteClips_[0].x = 0;
  spriteClips_[0].y = 0;
  spriteClips_[0].w = 21;
  spriteClips_[0].h = 31;
  
  spriteClips_[1].x = 21;
  spriteClips_[1].y = 0;
  spriteClips_[1].w = 21;
  spriteClips_[1].h = 31;
  
  texture_ = SDL_CreateTextureFromSurface(renderer, gPlayer);
}

void Player::action(SDL_Point* target, std::vector<SDL_Rect>* obsticles)
{
  if(position_.x == target->x && position_.y == target->y) {
    isMoving = false;
  } else {
    position_.x = target->x;
    position_.y = target->y;
    isMoving = true;
  }
}

void Player::render(int ticks)
{
  
  constexpr int animationRate = 12;
  constexpr int animationLen = 2;
  
  SDL_Rect bounds = getBounds();
  
  if(isMoving){
    int frameToDraw = (ticks * animationRate / 1000) % animationLen;
    SDL_Rect bounds = getBounds();
    SDL_RenderCopy(renderer_, texture_, &spriteClips_[frameToDraw], &bounds);
  } else {
    SDL_RenderCopy(renderer_, texture_, &spriteClips_[0], &bounds );
  }
}
