// g++ main.cpp $(sdl2-config --cflags --libs) -o prog && ./prog
#include "Game.h"

int main() {
  Game game;
  game.run();

  return 0;
}
