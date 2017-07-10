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
  renderer_ = renderer;
}

void Scene::addPlayer(Player* player) {
  player_ = player;
}

void Scene::addSprite(Sprite *sprite)
{
  sprites_.push_back(sprite);
}

Direction Scene::doEvent(SDL_Point nextPos)
{
  std::vector<SDL_Rect> obsticles;
  
  SDL_Point newPos;
  
  // FIXME: Quick & Dirty collision detection
  for(auto& r : sprites_) {
    
    if(r->isObsticle()) {
      obsticles.push_back(r->getBounds());
    }
    
    for(auto& s : sprites_) {
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
  
  if(s_rect.x < 0 || s_rect.y < 0 || s_rect.x > (640 - s_rect.w) || s_rect.y > (480 - s_rect.h)) {
    playerCollision = true;
  } else {
    for(auto& r : sprites_) {
      
      if(!r->isObsticle()) { continue ; }
      
      SDL_Rect result = SDL_Rect();
      SDL_Rect r_rect = r->getBounds();
      if(SDL_IntersectRect(&r_rect, &s_rect, &result)== SDL_TRUE) {
        r->doCollision(&s_rect);
        playerCollision = true;
        break;
      }
    }
  }
  
  if(!playerCollision) {
    SDL_Rect playerPos = player_->getBounds();
    prevPlayerPosition_.x = playerPos.x;
    prevPlayerPosition_.y = playerPos.y;
    player_->action(&nextPos, &obsticles);
    newPos = nextPos;
  } else {
    newPos.x = prevPlayerPosition_.x;
    newPos.y = prevPlayerPosition_.y;
  }
  
  // Update the sprite goals & render the next frame
  int ticks = (SDL_GetTicks() - startTime_);
  for(auto& r : sprites_) {
    r->action(&newPos, &obsticles);
    r->render(ticks);
  }
  player_->render(ticks);
  
  return player_->direction_;
}
