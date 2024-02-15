#pragma once

#include <SDL.h>
#include <iostream>
#include <vector>

class Map {
public:
  Map(std::string data_path);

  void load_map(std::string map_file);
  void create_tile_texture(SDL_Renderer *renderer);
  void render(SDL_Renderer *renderer);

private:
  std::vector<std::vector<int> > tiles;
  SDL_Texture *tile_texture;
};
