//
//  Scene.cpp
//  RoboChase
//
//  Created by nsp on 29/3/17.
//  Copyright © 2017 nspool. All rights reserved.
//

#include "Scene.hpp"

Scene::Scene(SDL_Renderer* renderer)
{
  _renderer = renderer;
}

void Scene::AddPlayer(Player* player) {
  _player = player;
}

void Scene::Add(Sprite *sprite)
{
  _sprites.push_back(sprite);
}

SDL_Point Scene::doEvent(SDL_Point nextPos)
{
  std::vector<SDL_Rect> obsticles;
  
  SDL_Point newPos;
  
  // FIXME: Quick & Dirty collision detection
  for(auto& r : _sprites) {
    
    if(r->isObsticle()) {
      obsticles.push_back(r->getBounds());
    }
    
    for(auto& s : _sprites) {
      if(r == s) { continue; }
      SDL_Rect result = SDL_Rect();
      SDL_Rect r_rect = r->getBounds();
      SDL_Rect s_rect = s->getBounds();
      if(SDL_IntersectRect(&r_rect, &s_rect, &result)== SDL_TRUE) {
        r->doCollision(&s_rect);
      }
    }
  }
  
  // FIXME: Update player position, *then* check for collision

  bool playerCollision = false;
  
  SDL_Rect s_rect;
  s_rect.x = nextPos.x;
  s_rect.y = nextPos.y;
  s_rect.w = 21;
  s_rect.h = 31;
  
  for(auto& r : _sprites) {
    SDL_Rect result = SDL_Rect();
    SDL_Rect r_rect = r->getBounds();
    if(SDL_IntersectRect(&r_rect, &s_rect, &result)== SDL_TRUE) {
      r->doCollision(&s_rect);
      playerCollision = true;
      break;
    }
  }
  
  if(!playerCollision) {
    SDL_Rect playerPos = _player->getBounds();
    _prevPlayerPosition.x = playerPos.x;
    _prevPlayerPosition.y = playerPos.y;
    _player->action(&nextPos, &obsticles);
    newPos = nextPos;
  } else {
    newPos.x = _prevPlayerPosition.x;
    newPos.y = _prevPlayerPosition.y;
  }
  
  // Update the sprite goals & render the next frame
  for(auto& r : _sprites) {
    r->action(_playerPosition, &obsticles);
    r->render();
  }
  
  _player->render();
  
  return newPos;
}
