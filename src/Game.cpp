#include <iostream>

#include "Game.h"
#include "Map.h"
#include "Constants.h"

Game::Game()
    : window(nullptr), renderer(nullptr), player(50, 50), map("src/test_map.csv"),
      delta_time(0), quit(false) {

  if (!initialize()) {
    std::cout << "Initalization failed." << std::endl;
  }
}

Game::~Game() { cleanup(); }

bool Game::initialize() {

  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cout << "Error initalizing SDL:" << SDL_GetError() << std::endl;
    return false;
  }

  window =
      SDL_CreateWindow("Mario", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

  if (!window) {
    std::cout << "Error creating SDL window:" << SDL_GetError() << std::endl;
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, 0);

  if (!renderer) {
    std::cout << "Error creating renderer" << SDL_GetError() << std::endl;
    return false;
  }

  map.create_tile_texture(renderer);

  camera.x = 0;
  camera.y = 0;
  camera.w = WINDOW_WIDTH;
  camera.h = WINDOW_HEIGHT;

  return true;
}

void Game::cleanup() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void Game::process_input() {

  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      quit = true;
    } else {
      player.process_input(event);
    }
  }

}

void Game::update() {

  player.update(delta_time, camera);

  int center_pos = player.get_x() - (WINDOW_WIDTH / 2);
  if (center_pos > 0) {
    if (center_pos > camera.x) {
      camera.x = center_pos;
    }
  }
}

void Game::render() {

  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  map.render(renderer, camera);
  player.render(renderer, camera);

  SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
  SDL_RenderDrawLine(renderer, WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2,
                     WINDOW_HEIGHT);

  SDL_RenderPresent(renderer);
}

void Game::run() {

  Uint32 frame_start;
  Uint32 frame_end;
  int frame_time;

  while (!quit) {

    frame_start = SDL_GetTicks();

    process_input();
    update();
    render();

    frame_end = SDL_GetTicks();

    frame_time = frame_end - frame_start;
    if (FPS_TARGET > frame_time) {
      SDL_Delay(FPS_TARGET - frame_time);
    }

    delta_time = (SDL_GetTicks() - frame_start) / 1000.0f;
  }
}