#ifndef OPTION_HPP
#define OPTION_HPP

#include <string>

// Struct para las opciones de la escena
struct Option {
  std::string text;
  bool value;
  int nextScene;
};

#endif