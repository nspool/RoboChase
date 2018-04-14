//
//  SpriteSheet.hpp
//  RoboChase
//
//  Created by nsp on 29/6/17.
//  Copyright © 2017 nspool. All rights reserved.
//

#ifndef SpriteSheet_hpp
#define SpriteSheet_hpp

#include <SDL.h>

#endif /* SpriteSheet_hpp */

class SpriteSheet
{
public:
  SpriteSheet();
  SpriteSheet(SDL_Surface*, int);
  SDL_Rect* clips;
  SDL_Texture* texture;
private:
  void init(SDL_Surface*, int);
};
