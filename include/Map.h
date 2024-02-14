#pragma once
#include <SDL.h>
#include <iostream>
#include <vector>

class Map {
public:
  Map(std::string data_path);

  void load_map(std::string map_file);
  void render(SDL_Renderer *renderer);

private:
  std::vector<std::vector<int>> tiles;
};
