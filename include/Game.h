#pragma once

#include <SDL.h>

#include <iostream>

#include "Map.h"
#include "Player.h"

class Game {
public:
  Game();
  ~Game();

  void run();

private:
  bool initialize();
  void cleanup();
  void process_input();
  void update();
  void render();

  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Rect camera;

  Player player;
  Map map;

  float delta_time;
  bool quit;
};
