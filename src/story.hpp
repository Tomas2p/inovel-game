#ifndef STORY_HPP
#define STORY_HPP

#include <string>
#include <vector>

#include "option.hpp"
// #include "pixelart.hpp"
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
  // Imprime el pixel art con los colores asignados
  void displayPixelArt(const Scene& scene);
  // Usa ncurses para mostrar las escenas
  void displayScreen(const Scene& scene);
  // Obtiene el tamaño maximo vertical del pixelart
  int getPixelArtWidth(const Scene& scene);

  // Título y título final
  std::string title, endTitle;
  // Vector de escenas
  std::vector<Scene> scenes;
};

#endif