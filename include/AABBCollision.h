#pragma once

#include <SDL.h>

class AABBCollision {
public:
  static bool check_collision(SDL_Rect &r1, SDL_Rect &r2);
};
