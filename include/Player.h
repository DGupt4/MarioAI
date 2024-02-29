#pragma once

#include <string>
#include <unordered_map>
#include <Vector2D.h>
#include <Constants.h>
#include <SDL.h>

class Player {
public:
  Player(int w, int h);

  void process_input(SDL_Event event);
  void update(float delta_time, SDL_Rect &camera);
  void render(SDL_Renderer *renderer, SDL_Rect &camera);

  int get_x();
  int get_y();

private:
  Vector2D position;
  Vector2D velocity;
  float width;
  float height;

  std::unordered_map<Action, bool> key_state;
  void update_physics(float delta_time);
  void handle_key_state(Action move, bool press);
};
