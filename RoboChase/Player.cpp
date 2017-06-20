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

  spriteClips_[2].x = 42;
  spriteClips_[2].y = 0;
  spriteClips_[2].w = 21;
  spriteClips_[2].h = 31;
  
  spriteClips_[3].x = 63;
  spriteClips_[3].y = 0;
  spriteClips_[3].w = 21;
  spriteClips_[3].h = 31;
  
  spriteClips_[4].x = 85;
  spriteClips_[4].y = 0;
  spriteClips_[4].w = 21;
  spriteClips_[4].h = 31;
  
  texture_ = SDL_CreateTextureFromSurface(renderer, gPlayer);
}

void Player::action(SDL_Point* target, std::vector<SDL_Rect>* obsticles)
{
  int yd = (position_.y - target->y);
  int xd = (position_.x - target->x);
  
  if(!xd && !yd) {
    direction_ = x;
  } else {
    if(xd < 0) { direction_ = w; }
    if(xd > 0) { direction_ = e; }
//    if(xd > 0) { direction_ = s; }
//    if(xd < 0) { direction_ = n; }

//    if(yd > 0 && xd > 0) { direction_ = sw; }
//    if(yd < 0 && xd < 0) { direction_ = ne; }
//    if(yd > 0 && xd < 0) { direction_ = nw; }
//    if(yd < 0 && xd > 0) { direction_ = se; }
    
    position_.x = target->x;
    position_.y = target->y;
  }
}

void Player::render(int ticks)
{
  
  constexpr int animationRate = 12;
  constexpr int animationLen = 2;
  
  
  SDL_Rect bounds = getBounds();
  
  if(direction_ != x){
    int offset = (direction_ == e) ? 1 : 3;
    int frameToDraw = (ticks * animationRate / 1000) % animationLen;
    SDL_Rect bounds = getBounds();
    SDL_RenderCopy(renderer_, texture_, &spriteClips_[frameToDraw + offset], &bounds);
  } else {
    SDL_RenderCopy(renderer_, texture_, &spriteClips_[0], &bounds );
  }
}
