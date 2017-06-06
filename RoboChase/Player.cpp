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
  _renderer = renderer;
  _p = p;
  
  // Load the robit
  SDL_Surface* gPlayer = IMG_Load("player.png");
  
  if(gPlayer == 0)
  {
    printf("Failed to load images! SDL_Error: %s\n", SDL_GetError());
  }
  
  // Setup Robit animation
  _spriteClips[0].x = 0;
  _spriteClips[0].y = 0;
  _spriteClips[0].w = 21;
  _spriteClips[0].h = 31;
  
  _texture = SDL_CreateTextureFromSurface( renderer, gPlayer );
}

void Player::action(SDL_Point* target, std::vector<SDL_Rect>* obsticles)
{
  _p.x = target->x;
  _p.y = target->y;
}

void Player::render()
{
  SDL_Rect bounds = getBounds();
  SDL_RenderCopy( _renderer, _texture, &_spriteClips[0], &bounds );
}
