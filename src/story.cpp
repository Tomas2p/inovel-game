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
  int currentSceneIndex{-1};

  while (std::getline(file, line)) {
    switch (line[0]) {
      case 'T':  // Comienza con T, es el título de la historia
        title = line.substr(line.find(':') + 1);
        continue;

      case 'E': {  // Comienza con E, es una nueva escena
        // Extrae el identificador de la escena
        int id = stoi(line.substr(1, line.find(':') - 1));
        // Crea la nueva escena y la agrega al vector
        Scene newScene;
        newScene.id = id;
        newScene.intro = line.substr(line.find(':') + 1, line.find('|'));
        currentSceneIndex = scenes.size();
        scenes.push_back(newScene);
        continue;
      }

      case '+': {  // Comienza con "+", es una opción correcta
        Option newOption;
        newOption.text = line.substr(1);
        // Se asignará el valor de la siguiente escena
        newOption.nextScene = scenes.size() + 1;
        scenes[currentSceneIndex].options.push_back(newOption);
        continue;
      }

      case '-': {  // Comienza con "-", es una opción incorrecta
        Option newOption;
        newOption.text = line.substr(1);
        // Se asignará el valor -1 de fin
        newOption.nextScene = scenes.size() - 1;
        scenes[currentSceneIndex].options.push_back(newOption);
        continue;
      }

      case 'F':  // Comienza con "F", es el final de la historia
        end_title = line.substr(line.find(':') + 1);
        scenes[currentSceneIndex].options.back().nextScene = -1;
        continue;

      default:  // Ignora las líneas vacías, los comentarios y el resto
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
  std::cout << scenes.size();

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
  std::cout << end_title << "\n\n";
  pressEnter();
}
