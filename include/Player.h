#pragma once

#include <SDL.h>
#include <string>
#include <unordered_map>

class Player {
public:
  Player();

  void process_input(SDL_Event event);
  void update(float delta_time, SDL_Rect platform);
  void render(SDL_Renderer *renderer);

private:
  float x;
  float y;
  float velocity_x;
  float velocity_y;
  float width;
  float height;
  bool is_on_ground;

  std::unordered_map<std::string, bool> key_state;

  void handle_key_state(std::string move, bool press);
};
