#pragma once
#include <iostream>
#include <vector>
#include <SDL.h>

class Map {
  public:
    Map(std::string data_path);

    void load_map(std::string map_file);
    void render_map();

  private:
    std::vector<std::vector<int> > tiles;
};
