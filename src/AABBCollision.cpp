#include "AABBCollision.h"

#include <iostream>

// Use references here or something?
// Consider overloading to have (x,y,w,h, rect)...
bool AABBCollision::check_collision(SDL_Rect &r1, SDL_Rect &r2) {
  if (r1.x + r1.w < r2.x || r1.x > r2.x + r2.w || r1.y + r1.h < r2.y ||
      r1.y > r2.y + r2.h) {
    return false;
  }
  return true;
}
