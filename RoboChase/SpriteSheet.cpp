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
  clips = new SDL_Rect[sprites];
  
  for(int i=0; i<sprites; i++) {
    clips[i].x = i*width;
    clips[i].y = 0;
    clips[i].w = 21;
    clips[i].h = 31;
  }
}
