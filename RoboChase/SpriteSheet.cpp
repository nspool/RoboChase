//
//  SpriteSheet.cpp
//  RoboChase
//
//  Created by nsp on 29/6/17.
//  Copyright © 2017 nspool. All rights reserved.
//

#include "SpriteSheet.hpp"

SpriteSheet::SpriteSheet()
{
}

SpriteSheet::SpriteSheet(SDL_Surface* sheet, int width)
{
  init(sheet, width);
}

void SpriteSheet::init(SDL_Surface* sheet, int width)
{
  int sprites = (sheet->w / width);
  spriteClips_ = new SDL_Rect[sprites];
  
  for(int i=0; i<sprites; i++) {
    spriteClips_[i].x = i*width;
    spriteClips_[i].y = 0;
    spriteClips_[i].w = 21;
    spriteClips_[i].h = 31;
  }
}
