#include <iostream>
#include <fstream>

#include "Map.h"

Map::Map(std::string data_path) {
  load_map(data_path);
} 

void Map::load_map(std::string data_path) {
  std::ifstream data_file(data_path);
  std::string line;

  if (data_file.is_open()) {
    while (getline(data_file, line)) {
      std::cout << line << std::endl;
      // Push this info into tiles vector
    }
    data_file.close();
  }

}

void Map::render_map() {

}

