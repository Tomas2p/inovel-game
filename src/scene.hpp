#ifndef SCENE_HPP
#define SCENE_HPP

#include <string>
#include <vector>

#include "option.hpp"

// Struct para gestionar las escenas
struct Scene {
  // ID de la escena
  int id;
  // Texto de la escena
  std::string intro;
  // Vector de opciones
  std::vector<Option> options;
  // Matriz con el pixelart
  std::vector<std::vector<char>> pixelArt;
};

#endif