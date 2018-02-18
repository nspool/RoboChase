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

bool Scene::isGameOver() {
  return gameOver_;
}

bool Scene::isGameWon() {
  return (ROBOT_COUNT == destroyed_);
}

void Scene::addPlayer(Player* player) {
  player_ = player;
}

void Scene::addSprite(Sprite *sprite)
{
  sprites_.push_back(sprite);
}

SDL_Point Scene::doEvent(SDL_Rect camera, SDL_Point nextPos)
{
  std::vector<SDL_Rect> obsticles;
  
  SDL_Point newPos;
  
  // FIXME: Quick & Dirty collision detection
  for(unsigned i=0; i<sprites_.size(); i++){

    Sprite* r = sprites_.at(i);
    
    if(r->isObsticle()) {
      obsticles.push_back(r->getBounds());
    }
    
    for(unsigned j=0; j<sprites_.size(); j++){
      
      Sprite* s = sprites_.at(j);

      if(r == s) { continue; }
      
      SDL_Rect result = SDL_Rect();
      SDL_Rect r_rect = r->getBounds();
      SDL_Rect s_rect = s->getBounds();
      
      r_rect.x -= camera.x;
      r_rect.y -= camera.y;
      s_rect.x -= camera.x;
      s_rect.y -= camera.y;
      
      if(SDL_IntersectRect(&r_rect, &s_rect, &result)== SDL_TRUE) {
        if(s->isProjectile()) {
          r->doHit();
          if(r->isDestructable()) {
            // FIXME: this will crash when projectile is older than sprite!
            sprites_.erase(sprites_.begin() + j);
            sprites_.erase(sprites_.begin() + i);
            destroyed_++;
            SDL_Log("Sprites Destroyed: %d\n", destroyed_);
          }
        } else {
          r->doCollision(&s_rect);
          if(r->isProjectile()) {
            sprites_.erase(sprites_.begin() + i);
          }
        }
      }
    }
  }
  
  // FIXME: Update player position, *then* check for collision

  bool playerCollision = false;
  
  SDL_Rect s_rect;
  s_rect.x = nextPos.x;
  s_rect.y = nextPos.y;
  s_rect.w = 50;
  s_rect.h = 50;
  
  // Don't go outside the window bounds
  if(s_rect.x < 0 || s_rect.y < 0 || s_rect.x > (LEVEL_WIDTH - s_rect.w) || s_rect.y > (LEVEL_HEIGHT - s_rect.h)) {
    playerCollision = true;
  } else {
    for(unsigned j=0; j<sprites_.size(); j++){
      
      Sprite* r = sprites_.at(j);
      
      if(!r->isObsticle()) { continue ; }
      
      SDL_Rect result = SDL_Rect();
      SDL_Rect r_rect = r->getBounds();

      if(SDL_IntersectRect(&r_rect, &s_rect, &result) == SDL_TRUE) {
        r->doCollision(&s_rect);
        
        if(r->isEnemy()) {
          player_->captured();
          gameOver_ = true;
        }
        
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
    r->render(camera, ticks);
  }
  player_->render(camera, ticks);
  
  playerDirection = player_->direction_;
  
  return newPos;
}
