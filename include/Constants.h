#pragma once

#include <SDL.h>

const int WINDOW_WIDTH = 512;
const int WINDOW_HEIGHT = 480;
const int FPS = 60;
const int FPS_TARGET = 1000 / FPS;

const int TILE_SIZE = 32;
const int TILE_HALF = 16;

const float ACCELERATION = 200.0f;
const float GRAVITY = 100.0f;
const float JUMP_FORCE = 100.0f;
const float MAX_SPEED = 200.0f;
const float FRICTION = 0.9f;

const SDL_Color BG_BLUE = {147, 186, 237, 255};

enum class Action {
  LEFT,
  RIGHT,
  DUCK,
  FIREBALL,
  SPRINT,
  JUMP
};