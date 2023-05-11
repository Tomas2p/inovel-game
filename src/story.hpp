#ifndef STORY_HPP
#define STORY_HPP

#include <string>
#include <vector>

#include "option.hpp"
#include "scene.hpp"

// Clase para gestionar la historia
class Story {
 public:
  // Constructor
  Story(const std::string& filename);
  // Función principal
  void run();

 private:
  // Cargar la historia
  void loadStory(const std::string& filename);
  // Mostrar la escena
  void displayScene(const Scene& scene, const int& kLastScene);
  // Imprime las opciones
  void displayOptions(const Scene& scene);
  // Obtener la opción del jugador
  int getPlayerChoice(int maxOptions);

  std::string title, end_title;
  std::vector<Scene> scenes;
};

#endif