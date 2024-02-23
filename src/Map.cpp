#include <SDL_image.h>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

#include "Constants.h"
#include "Game.h"
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

  SDL_Surface *tile_surface = SDL_CreateRGBSurface(
      0, get_width() / 2, get_height() / 2, 32, 0, 0, 0, 0);
  SDL_FillRect(tile_surface, NULL,
               SDL_MapRGB(tile_surface->format, 147, 186, 237));

  int block_id = 48;

  std::map<int, std::pair<int, int> > sprite_atlas;

  for (int i = 1; i < 23; i++) {
    for (int j = 1; j < 49; j++) {
      sprite_atlas[block_id] = std::make_pair((j - 1) * TILE_SIZE / 2 + j,
                                              i * TILE_SIZE / 2 + (i + 1));
      block_id++;
    }
  }

  for (int i = 0; i < tiles.size(); i++) {
    for (int j = 0; j < tiles[i].size(); j++) {

      int tile_id = tiles[i][j];

      if (tile_id != -1) {
        SDL_Rect tile_rect = {sprite_atlas[tile_id].first,
                              sprite_atlas[tile_id].second, TILE_SIZE / 2,
                              TILE_SIZE / 2};
        SDL_Rect dest_rect = {j * TILE_SIZE / 2, i * TILE_SIZE / 2,
                              TILE_SIZE / 2, TILE_SIZE / 2};
        SDL_BlitSurface(tile_sheet, &tile_rect, tile_surface, &dest_rect);
      }
    }
  }

  SDL_Surface *scaled_surface =
      SDL_CreateRGBSurface(0, get_width(), get_height(), 32, 0, 0, 0, 0);
  SDL_Rect src_rect = {0, 0, tile_surface->w, tile_surface->h};
  SDL_Rect dest_rect = {0, 0, scaled_surface->w, scaled_surface->h};

  SDL_BlitScaled(tile_surface, &src_rect, scaled_surface, &dest_rect);
  tile_texture = SDL_CreateTextureFromSurface(renderer, scaled_surface);

  SDL_FreeSurface(tile_surface);
  SDL_FreeSurface(tile_sheet);
  SDL_FreeSurface(scaled_surface);
}

int Map::get_height() { return tiles.size() * TILE_SIZE; }

int Map::get_width() { return tiles[0].size() * TILE_SIZE; }

void Map::render(SDL_Renderer *renderer, SDL_Rect camera) {
  if (tile_texture != nullptr) {
    SDL_Rect src = {camera.x, camera.y, camera.w, camera.h};
    SDL_Rect dest = {0, 0, WINDOW_WIDTH, WINDOW_WIDTH};
    SDL_RenderCopy(renderer, tile_texture, &src, &dest);
  }
}