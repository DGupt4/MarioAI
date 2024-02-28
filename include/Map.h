#pragma once

#include <iostream>
#include <vector>
#include <SDL.h>

class Map {
public:
  Map(std::string data_path);

  void load_map(std::string map_file);
  void create_tile_texture(SDL_Renderer *renderer);
  void render(SDL_Renderer *renderer, SDL_Rect &camera);
  std::unordered_map<int, std::pair<int, int> > assign_block_id();

  int get_width();
  int get_height();

private:
  std::vector<std::vector<int> > tiles;
  SDL_Texture *map_texture;
};
