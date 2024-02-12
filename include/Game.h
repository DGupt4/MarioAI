#pragma once

#include <iostream>
#include <SDL.h>

#include "Player.h"
#include "Map.h"

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
    Player player;
    Map map;

    float delta_time;
    SDL_Rect ground_rect;
    bool quit;
};
