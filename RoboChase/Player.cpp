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
    SDL_LogError(0, "%s", SDL_GetError());
    return;
  }
  sprite_ = SpriteSheet(gPlayer, 21);
  sprite_.texture = SDL_CreateTextureFromSurface(renderer, gPlayer);
}

void Player::action(SDL_Point* target, std::vector<SDL_Rect>* obsticles)
{
  int yd = (position_.y - target->y);
  int xd = (position_.x - target->x);
  
  if(yd == 0 && xd == 0) {
    moving_ = false;
    return;
  }
  
  moving_ = true;
  if(xd < 0) { direction_ = w; }
  if(xd > 0) { direction_ = e; }
  if(yd < 0) { direction_ = s; }
  if(yd > 0) { direction_ = n; }
  position_.x = target->x;
  position_.y = target->y;
}

void Player::captured()
{
  SDL_Log("Player captured");
}

void Player::render(SDL_Rect camera, int ticks)
{
  
  constexpr int animationRate = 12;
  constexpr int animationLen = 2;
  
  SDL_Rect bounds = getBounds();
  
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
  
  bounds.x -= camera.x;
  bounds.y -= camera.y;
  
  int frameToDraw = (moving_) ? (ticks * animationRate / 1000) % animationLen : 0;
      
  SDL_RenderCopy(renderer_, sprite_.texture, &sprite_.clips[frameToDraw + offset], &bounds);
  
}
