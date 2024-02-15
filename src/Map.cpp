#include <SDL_image.h>
#include <fstream>
#include <iostream>
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

void Map::create_tile_texture(SDL_Renderer *renderer) {

  SDL_Surface *tile_sheet = IMG_Load("../res/tile_sheet.png");

  SDL_Surface *tile_surface =
      SDL_CreateRGBSurface(0, WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 32, 0, 0, 0, 0);

  for (int i = 0; i < tiles.size(); i++) {
    for (int j = 0; j < tiles[i].size(); j++) {

      int tile_id = tiles[i][j];

      if (tile_id == 1) {
        SDL_Rect block_sprite = {1, 137, TILE_SIZE/2, TILE_SIZE/2};
        SDL_Rect dest_rect = {i * TILE_SIZE/2, j * TILE_SIZE/2, TILE_SIZE/2, TILE_SIZE/2};
        SDL_BlitSurface(tile_sheet, &block_sprite, tile_surface, &dest_rect);
      }
    }
  }

  SDL_Surface *scaled_surface = SDL_CreateRGBSurface(0, WINDOW_WIDTH, WINDOW_HEIGHT, 32, 0, 0, 0, 0);
  SDL_Rect src_rect = {0, 0, tile_surface->w, tile_surface->h};
  SDL_Rect dest_rect= {0, 0, scaled_surface->w, scaled_surface->h};

  SDL_BlitScaled(tile_surface, &src_rect, scaled_surface, &dest_rect);
  tile_texture = SDL_CreateTextureFromSurface(renderer, scaled_surface);

  SDL_FreeSurface(tile_surface);
  SDL_FreeSurface(tile_sheet);
  SDL_FreeSurface(scaled_surface);
}

void Map::render(SDL_Renderer *renderer) {
  if (tile_texture != nullptr) {
    SDL_RenderCopy(renderer, tile_texture, NULL, NULL);
  }
}
