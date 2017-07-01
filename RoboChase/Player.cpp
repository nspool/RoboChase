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
  sprite_ = SpriteSheet(gPlayer, 21);
  sprite_.texture_ = SDL_CreateTextureFromSurface(renderer, gPlayer);
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
    if(yd < 0) { direction_ = s; }
    if(yd > 0) { direction_ = n; }

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
    int offset = 0;
    switch(direction_) {
      case e:
        offset = 1; break;
      case w:
        offset = 3; break;
      case s:
        offset = 5; break;
      case n:
        offset = 7; break;
      default:
        break;
    }
    int frameToDraw = (ticks * animationRate / 1000) % animationLen;
    SDL_Rect bounds = getBounds();
    SDL_RenderCopy(renderer_, sprite_.texture_, &sprite_.spriteClips_[frameToDraw + offset], &bounds);
  } else {
    SDL_RenderCopy(renderer_, sprite_.texture_, &sprite_.spriteClips_[0], &bounds );
  }
}
