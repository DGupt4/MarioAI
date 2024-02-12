#include <iostream>

#include "Game.h"
#include "Map.h"
#include "Constants.h"

Game::Game() : window(NULL), renderer(NULL), player(), map("src/test_map.csv"), delta_time(0), ground_rect(), quit(false) {
  if (!initialize()) {
    std::cout << "Initalization failed." << std::endl;
  }
}

Game::~Game() {
  cleanup();
}

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

  ground_rect.x = 0;
  ground_rect.y = 430;
  ground_rect.w = 640;
  ground_rect.h = 50;

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
      } else{
        player.process_input(event);
      }
    }
}

void Game::update() {
  player.update(delta_time, ground_rect);
}

void Game::render() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  // Test Platform 
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderFillRect(renderer, &ground_rect);

  player.render(renderer);

  SDL_RenderPresent(renderer);
}

void Game::run() {

  int frame_start;
  int frame_time;

  while (!quit) {
    process_input();
    update();
    render();

    frame_start = SDL_GetTicks();
    frame_time = SDL_GetTicks() - frame_start;

    if (FPS_TARGET > frame_time) {
      SDL_Delay(FPS_TARGET - frame_time);
    }

    delta_time = (SDL_GetTicks() - frame_start) / 1000.0f;

  }
}
