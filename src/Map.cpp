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

void Map::render(SDL_Renderer *renderer) {

  SDL_Surface *tile_surface =
      SDL_CreateRGBSurface(0, WINDOW_WIDTH, WINDOW_HEIGHT, 32, 0, 0, 0, 0);
  SDL_Texture *tile_texture =
      SDL_CreateTextureFromSurface(renderer, tile_surface);

  for (int i = 0; i < tiles.size(); i++) {
    for (int j = 0; j < tiles[i].size(); j++) {

      int tile = tiles[i][j];
      SDL_FreeSurface(tile_surface);

      if (tile == 1) {
        SDL_Rect temp = {i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE};
        SDL_RenderCopy(renderer, tile_texture, NULL, &temp);
      }
    }
  }
}
