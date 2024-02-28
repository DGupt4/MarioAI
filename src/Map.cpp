#include <SDL_image.h>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

#include "Constants.h"
#include "Map.h"

Map::Map(std::string data_path) { load_map(data_path); }

void Map::load_map(std::string data_path) {

  std::ifstream data_file(data_path);
  std::string line, word;

  if (data_file.is_open()) {

    while (getline(data_file, line)) {
      std::vector<int> row;
      std::stringstream ss(line);

      while (getline(ss, word, ',')) {
        row.push_back(std::stoi(word));
      }

      tiles.push_back(row);
    }

    data_file.close();
  }
}

std::unordered_map<int, std::pair<int, int>> Map::assign_block_id() {

  int block_id = 48;
  std::unordered_map<int, std::pair<int, int>> sprite_atlas;

  for (int i = 1; i < 23; i++) {
    for (int j = 1; j < 49; j++) {
      sprite_atlas[block_id] =
          std::make_pair((j - 1) * TILE_HALF + j, i * TILE_HALF + (i + 1));
      block_id++;
    }
  }

  return sprite_atlas;
}

void Map::create_tile_texture(SDL_Renderer *renderer) {

  SDL_Texture *sprite_texture = IMG_LoadTexture(renderer, "../res/tile_sheet.png");

  map_texture = SDL_CreateTexture(
      renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
      get_width() / 2, get_height() / 2);

  SDL_SetRenderTarget(renderer, map_texture);
  SDL_SetTextureBlendMode(map_texture, SDL_BLENDMODE_BLEND);
  SDL_SetRenderDrawColor(renderer, BG_BLUE.r, BG_BLUE.g, BG_BLUE.b, BG_BLUE.a);
  SDL_RenderClear(renderer);

  auto sprite_atlas = assign_block_id();

  for (int i = 0; i < tiles.size(); i++) {
    for (int j = 0; j < tiles[i].size(); j++) {

      int tile_id = tiles[i][j];
      auto sprite = sprite_atlas[tile_id];

      if (tile_id != -1) {
        SDL_Rect src_rect = {sprite.first, sprite.second, TILE_HALF, TILE_HALF};
        SDL_Rect dest_rect = {j * TILE_HALF, i * TILE_HALF, TILE_HALF, TILE_HALF};
        SDL_RenderCopy(renderer, sprite_texture, &src_rect, &dest_rect);
      }
    }
  }

  SDL_SetRenderTarget(renderer, nullptr);
  SDL_DestroyTexture(sprite_texture);
}

int Map::get_height() { return tiles.size() * TILE_SIZE; }

int Map::get_width() { return tiles[0].size() * TILE_SIZE; }

void Map::render(SDL_Renderer *renderer, SDL_Rect &camera) {

  if (map_texture!= nullptr) {
    SDL_Rect src = {camera.x, camera.y, camera.w, camera.h};
    SDL_Rect dest = {0, 0, WINDOW_WIDTH * 2, WINDOW_HEIGHT*2};
    SDL_RenderCopy(renderer, map_texture, &src, &dest);
  }
}