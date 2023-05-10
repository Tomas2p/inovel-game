// Metodos de la clase story
#include "story.hpp"

#include <algorithm>
#include <cstdlib>  // Para el comando clear
#include <fstream>
#include <iostream>
#include <sstream>

#include "tools.hpp"

// Constructor
Story::Story(const std::string& filename) { loadStory(filename); }

// Carga la historia desde el archivo dado
void Story::loadStory(const std::string& filename) {
  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cerr << "Error al abrir el archivo " << filename << ".\n";
    return;
  }

  std::string line;
  bool isFirstLine{true};
  int currentSceneIndex{-1};

  while (std::getline(file, line)) {
    // Ignora las líneas vacías y los comentarios
    if (line.empty() || line[0] == '#') {
      continue;

      // Si es la primera línea, es el título de la historia
    } else if (isFirstLine) {
      title = line;
      isFirstLine = false;
      continue;

      // Si comienza con E, es el inicio de una nueva escena
    } else if (line[0] == 'E') {
      // Extrae el identificador de la escena
      int id = stoi(line.substr(1, line.find(':') - 1));
      // Crea la nueva escena y la agrega al vector
      Scene newScene;
      newScene.id = id;
      newScene.intro = line.substr(line.find(':') + 1, line.find('|'));
      currentSceneIndex = scenes.size();
      scenes.push_back(newScene);
      continue;

      // Si comienza con "+", es una opción correcta
    } else if (line[0] == '+') {
      Option newOption;
      newOption.text = line.substr(1);
      newOption.nextScene = -1;  // Se asignará el valor correcto más adelante
      scenes[currentSceneIndex].options.push_back(newOption);
      continue;

      // Si comienza con "-", es una opción incorrecta
    } else if (line[0] == '-') {
      Option newOption;
      newOption.text = line.substr(1);
      newOption.nextScene = -1;  // Se asignará el valor correcto más adelante
      scenes[currentSceneIndex].options.push_back(newOption);
      continue;

      // Si comienza con "=", es el final de la historia
    } else {
      scenes[currentSceneIndex].options.back().nextScene = -1;
      continue;
    }
  }
  file.close();
}

// Muestra la escena y opciones
void Story::displayScene(const Scene& scene) {
  clearScreen();

  // Imprime Escena id y la descripción
  for (int i{1}; i < int(25 + title.length()); ++i) std::cout << '-';
  std::cout << '\n';
  std::cout << " ---   " << title << " : Escena " << scene.id << "   ---\n";
  for (int i{1}; i < int(25 + title.length()); ++i) std::cout << '-';
  std::cout << "\n\n";
  std::cout << scene.intro << std::endl;

  // Imprime las opciones
  for (size_t i{0}; i < scene.options.size(); ++i) {
    std::cout << " [" << i + 1 << "] - " << scene.options[i].text << std::endl;
  }
}

// Para saber que opcion elige el jugador
int Story::getPlayerChoice(int maxOptions) {
  int playerChoice;
  std::cout << "\nElige una opción [1-" << maxOptions << "] >>> ";
  std::cin >> playerChoice;

  return playerChoice;
}

// Toda la ejecucion del programa
void Story::run() {
  int currentScene = 0;
  clearScreen();

  while (currentScene >= 0 && currentScene < int(scenes.size())) {
    // Imprime las escenas
    displayScene(scenes[currentScene]);

    // Imprime las opciones y las asigna a choice
    int choice{getPlayerChoice(scenes[currentScene].options.size())};

    // Asigna a nextScene la siguiente escena
    int nextScene{scenes[currentScene].options[choice - 1].nextScene};

    // Busca la siguiente escena por su identificador
    auto it{find_if(scenes.begin(), scenes.end(),
                    [nextScene](const Scene& s) { return s.id == nextScene; })};

    if (it != scenes.end()) {
      // Calcula el índice de la siguiente escena
      currentScene = distance(scenes.begin(), it);
    } else {
      // Final de la historia
      currentScene = -1;
    }
  }
  // Muestra el mensaje de finalización
  clearScreen();
  std::cout << ">> Fin de la historia <<\n";
  std::cout << "Presiona Enter para continuar...";
  std::cin.ignore();
  std::cin.get();
  clearScreen();
}
