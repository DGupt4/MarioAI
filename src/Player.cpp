#include <SDL_image.h>
#include <iostream>

#include "Player.h"
#include "AABBCollision.h"
#include "Constants.h"

Player::Player(int w, int h)
    : position(0, 0), velocity(0, 0), width(w), height(h),
      key_state() {}

void Player::process_input(SDL_Event event) {

  bool press_state = (event.type == SDL_KEYDOWN);

  if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
    switch (event.key.keysym.sym) {
    case SDLK_a:
      handle_key_state(Action::LEFT, press_state);
      break;
    case SDLK_s:
      handle_key_state(Action::DUCK, press_state);
      break;
    case SDLK_d:
      handle_key_state(Action::RIGHT, press_state);
      break;
    case SDLK_q:
      handle_key_state(Action::FIREBALL, press_state);
      break;
    case SDLK_LSHIFT:
      handle_key_state(Action::SPRINT, press_state);
      break;
    case SDLK_SPACE:
      handle_key_state(Action::JUMP, press_state);
      break;
    }
  }
}

void Player::update(float delta_time, SDL_Rect &camera) {

  update_physics(delta_time);

  // Bound player to camera
  if (position.x < camera.x) {
    position.x = camera.x;
    velocity.x = 0;
  } else if (position.x > camera.x + camera.w) {
    velocity.x = 0;
    position.x = camera.x + camera.w;
  }

}

void Player::update_physics(float delta_time) {

  // SDL_Rect temp = {static_cast<int>(x), static_cast<int>(y), static_cast<int>(width), static_cast<int>(height)};
  // is_on_ground = AABBCollision::check_collision(temp, platform);
  // Must check if the tiles belong to id 384

  if (key_state[Action::LEFT]) {
    velocity.x -= ACCELERATION * delta_time;
  } else if (key_state[Action::RIGHT]) {
    velocity.x += ACCELERATION * delta_time;
  } else {
    velocity.x *= FRICTION;
  }

  if (velocity.x > MAX_SPEED) {
    velocity.x = MAX_SPEED;
  }
  if (velocity.x < -MAX_SPEED) {
    velocity.x = -MAX_SPEED;
  }

  position.x += velocity.x * delta_time;
  position.y += velocity.y * delta_time;

}

void Player::render(SDL_Renderer *renderer, SDL_Rect &camera) {
  SDL_Texture *player_texture = IMG_LoadTexture(renderer, "../res/player_sheet.png"); // Move this elsewhere
  SDL_Rect src_rect = {1, 9, TILE_HALF, TILE_HALF};
  SDL_Rect dest_rect = {static_cast<int>(position.x - camera.x), static_cast<int>(position.y - camera.y), TILE_SIZE, TILE_SIZE};
  SDL_RenderCopy(renderer, player_texture, &src_rect, &dest_rect);
  SDL_SetRenderTarget(renderer, nullptr);
  SDL_DestroyTexture(player_texture);
}

void Player::handle_key_state(Action move, bool press) {
  key_state[move] = press;
}

int Player::get_x() { return position.x; }

int Player::get_y() { return position.y; }