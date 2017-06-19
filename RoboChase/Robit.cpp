//
//  Robit.cpp
//  RoboChase
//
//  Created by nsp on 16/3/17.
//  Copyright © 2017 nspool. All rights reserved.
//

#include "Robit.hpp"

Robit::Robit(SDL_Renderer* renderer, SDL_Point p)
{
  
  position_ = p;
  renderer_ = renderer;
  
  // Load the robit
  SDL_Surface* gRobits = IMG_Load("robits.png");
  
  if(gRobits == 0)
  {
//    printf("Failed to load images! SDL_Error: %s\n", SDL_GetError());
  }
  
  // Setup Robit animation
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
  
  texture_ = SDL_CreateTextureFromSurface( renderer, gRobits );
}

void Robit::stop()
{
  SDL_Rect robitLoc = { position_.x, position_.y, 21, 31 };
  SDL_RenderCopy(renderer_, texture_, &spriteClips_[1], &robitLoc );
}

void Robit::doCollision(SDL_Rect* rect)
{
  double collisionRad = atan2((currentTarget_->y - rect->y), (currentTarget_->x - rect->x));
  double rad = collisionRad - 1.55 + ((double)arc4random_uniform(1) - 0.5);
  
  currentTarget_-> x = cos(rad);
  currentTarget_-> y = sin(rad);
}


void Robit::action(SDL_Point* target, std::vector<SDL_Rect>* obsticles)
{
  
  SDL_Point currentTarget = SDL_Point(*target);
  currentTarget_ = &currentTarget;
  
  bool willCollide = false;
  
  int width = 21;
  int height = 31;
  
  SDL_Rect P1 = { position_.x, position_.y };
  SDL_Rect P2 = { position_.x + width, position_.y + height };
  SDL_Rect P3 = { position_.x, position_.y + height };
  SDL_Rect P4 = { position_.x + width, position_.y };
  SDL_Rect center = {position_.x + width / 2, position_.y + height / 2};

  double collisionRad = 0;
  double collisionDistance = 100;
  
  for(SDL_Rect o: *obsticles) {
    
    if(o.x == position_.x && o.y == position_.y) { continue; }
    
    // Only avoid when close to the obsticle
    if(sqrt(pow(position_.x - o.x, 2) + pow(position_.y - o.y, 2)) > collisionDistance) { continue; }
    
    if(SDL_IntersectRectAndLine(&o, &P1.x, &P1.y, &currentTarget_->x, &currentTarget_->y) ||
       SDL_IntersectRectAndLine(&o, &P2.x, &P2.y, &currentTarget_->x, &currentTarget_->y) ||
       SDL_IntersectRectAndLine(&o, &P3.x, &P3.y, &currentTarget_->x, &currentTarget_->y) ||
       SDL_IntersectRectAndLine(&o, &P4.x, &P4.y, &currentTarget_->x, &currentTarget_->y)) {
      
      collisionRad = atan2((o.y - center.y), (o.x - center.x));
      willCollide = true;
      
      break;
    }
  }

  // Interpolate the line between the current position and the target
  double rad = atan2((currentTarget_->y - center.y), (currentTarget_->x - center.x));
  
  // Move perpendicular to the obsticle
  if(willCollide) {
    // For now, just change the angle
    rad = collisionRad - 1.55 + ((double)arc4random_uniform(1) - 0.5);
    currentTarget_-> x = cos(rad);
    currentTarget_-> y = sin(rad);

  }
  
  // Set the new coordinates
  xDelta_ += cos(rad);
  yDelta_ += sin(rad);
  
  if(xDelta_ > 1 || xDelta_ < -1){
    position_.x += (int)xDelta_;
    xDelta_ = 0;
  }
  
  if(yDelta_ > 1 || yDelta_ < -1){
    position_.y += (int)yDelta_;
    yDelta_ = 0;
  }
}

void Robit::render(int ticks)
{
  // Animate at some fixed framerate
  constexpr int animationRate = 12;
  constexpr int animationLen = 3;
  int frameToDraw = (ticks * animationRate / 1000) % animationLen;
  SDL_Rect bounds = getBounds();
  SDL_RenderCopy(renderer_, texture_, &spriteClips_[frameToDraw], &bounds);
}
