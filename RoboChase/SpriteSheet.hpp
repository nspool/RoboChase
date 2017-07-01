//
//  SpriteSheet.hpp
//  RoboChase
//
//  Created by nsp on 29/6/17.
//  Copyright © 2017 nspool. All rights reserved.
//

#ifndef SpriteSheet_hpp
#define SpriteSheet_hpp

#include <SDL2/SDL.h>

#endif /* SpriteSheet_hpp */

class SpriteSheet
{
public:
  SpriteSheet();
  SpriteSheet(SDL_Surface*, int);
  SDL_Rect* spriteClips_;
  SDL_Texture* texture_;
private:
  void init(SDL_Surface*, int);
};
