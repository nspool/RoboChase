//
//  Sprite.hpp
//  RoboChase
//
//  Created by nsp on 25/4/17.
//  Copyright © 2017 nspool. All rights reserved.
//

#ifndef Sprite_hpp
#define Sprite_hpp

#include <vector>
#include <SDL.h>

#include "SpriteSheet.hpp"

enum Direction { x, n, s, e, w, nw, ne, sw, se };

class Sprite
{
public:
    bool isObsticle() { return true; }
    bool isDestructable() { return false; }
    bool isProjectile() { return false; }
    bool isEnemy() { return false; }
    void render(SDL_Rect camera, int ticks) {}
    void doHit() {}
    void doCollision(SDL_Rect* rect) {}
    void action(SDL_Point* target, std::vector<SDL_Rect>* obsticles) {};
    SDL_Rect getBounds() { return { position_.x, position_.y, 50, 50 }; }
    SDL_Point position_ = {0, 200};
};

#endif /* Sprite_hpp */
