#include <iostream>

#include "AABBCollision.h"
#include "Constants.h"
#include "Player.h"

// TODO: Find a better fix for width, height, x, y
Player::Player()
    : x(50), y(300), velocity_x(0), velocity_y(0), width(50), height(50),
      key_state(), is_on_ground(false) {}

void Player::process_input(SDL_Event event) {

  bool press_state = (event.type == SDL_KEYDOWN);

  if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
    switch (event.key.keysym.sym) {
    case SDLK_a:
      handle_key_state("LEFT", press_state);
      break;
    case SDLK_s:
      handle_key_state("DUCK", press_state);
      break;
    case SDLK_d:
      handle_key_state("RIGHT", press_state);
      break;
    case SDLK_q:
      handle_key_state("FIREBALL", press_state);
      break;
    case SDLK_LSHIFT:
      handle_key_state("SPRINT", press_state);
      break;
    case SDLK_SPACE:
      handle_key_state("JUMP", press_state);
      break;
    }
  }
}

void Player::update(float delta_time, SDL_Rect platform) {

  bool is_on_ground = false;

  if (key_state["LEFT"]) {
    velocity_x -= ACCELERATION * delta_time;
  } else if (key_state["RIGHT"]) {
    velocity_x += ACCELERATION * delta_time;
  } else {
    velocity_x *= FRICTION;
  }

  if (velocity_x > MAX_SPEED)
    velocity_x = MAX_SPEED;
  if (velocity_x < -MAX_SPEED)
    velocity_x = -MAX_SPEED;

  SDL_Rect temp = {x, y, width, height};
  is_on_ground = AABBCollision::check_collision(temp, platform);

  if (!is_on_ground) {
    velocity_y += GRAVITY * delta_time;
  } else {
    velocity_y = 0;
  }

  if (key_state["JUMP"] && is_on_ground) {
    velocity_y = -JUMP_FORCE;
    is_on_ground = false;
  }

  // TODO
  if (key_state["SPRINT"]) {
  }
  if (key_state["FIREBALL"]) {
  }
  if (key_state["DUCK"]) {
  }

  x += velocity_x * delta_time;
  y += velocity_y * delta_time;
}

void Player::render(SDL_Renderer *renderer) {
  SDL_Rect playerRect = {x, y, width, height};
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderFillRect(renderer, &playerRect);
}

void Player::handle_key_state(std::string move, bool press) {
  key_state[move] = press;
}
