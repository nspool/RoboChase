//
//  Scene.hpp
//  RoboChase
//
//  Created by nsp on 29/3/17.
//  Copyright © 2017 nspool. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

#endif /* Scene_hpp */

//#include "Sprite.hpp"
#include "Player.hpp"

class Scene
{
public:
  Scene(SDL_Renderer* _renderer);
  void Add(Sprite* sprite);
  void AddPlayer(Player* player);
  void Render();
  SDL_Point doEvent(SDL_Point nextPos);
private:
  Player* _player;
  SDL_Renderer* _renderer;
  SDL_Point* _playerPosition;
  std::vector<Sprite*> _sprites;
};
