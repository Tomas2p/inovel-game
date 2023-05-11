// Metodos de la clase story
#include "story.hpp"

#include <algorithm>
#include <cstdlib>  // Para el comando clear
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>

#include "tools.hpp"

// Constructor
Story::Story(const std::string& filename) { loadStory(filename); }

// Carga la historia desde el archivo dado
void Story::loadStory(const std::string& filename) {
  std::ifstream file(filename);
  int sceneIDCount{1};
  // Carácter por el que filtar en los txt
  const char kCharToFilter{'.'};

  if (!file.is_open()) {
    std::cerr << "Error al abrir el archivo " << filename << ".\n";
    return;
  }

  std::string line;
  int currentSceneIndex{-1};

  while (std::getline(file, line)) {
    switch (line[0]) {
      case 'T':  // Comienza con 'T', es el título de la historia
        title = line.substr(line.find(kCharToFilter) + 1);
        continue;

      case 'E': {  // Comienza con 'E', es una nueva escena
        // Extrae el identificador de la escena
        int id{sceneIDCount};
        ++sceneIDCount;
        // Crea la nueva escena y la agrega al vector
        Scene newScene;
        newScene.id = id;
        newScene.intro = line.substr(line.find(kCharToFilter) + 1);
        currentSceneIndex = scenes.size();
        scenes.push_back(newScene);
        continue;
      }

      case '+': {  // Opciones '+' correcta
        Option newOption;
        newOption.text = line.substr(line.find(kCharToFilter) + 1);
        // Valor de la siguiente escena es  tamaño scenes + line[1]
        if (line[1] != '.') {
          newOption.nextScene =
              std::stoi(line.substr(0, line.find(kCharToFilter))) +
              scenes.size();
          // Valor de siguiente escena es tamaño scenes + 1
        } else {
          newOption.nextScene = int(scenes.size() + 1);
        }
        scenes[currentSceneIndex].options.push_back(newOption);
        continue;
      }

      case '-': {  // Opcion '-' incorrecta
        Option newOption;
        newOption.text = line.substr(line.find(kCharToFilter) + 1);
        // Valor de la siguiente escena es  tamaño scenes + line[1]
        if (line[1] != '.') {
          newOption.nextScene =
              std::stoi(line.substr(0, line.find(kCharToFilter))) +
              scenes.size();
          // Valor de siguiente escena es tamaño scenes - 1
        } else {
          newOption.nextScene = int(scenes.size() - 1);
        }
        scenes[currentSceneIndex].options.push_back(newOption);
        continue;
      }

      case 'F':  // Comienza con 'F', es el final de la historia
        end_title = line.substr(line.find(kCharToFilter) + 1);
        scenes[currentSceneIndex].options.back().nextScene = -1;
        continue;

      default:  // Ignora las líneas vacías, los comentarios y el resto
        continue;
    }
  }
  file.close();
}

// Mezcla el vector dado
auto vectorShuffle(std::vector<Option>& vector) {
  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(vector.begin(), vector.end(), g);
}

// Imprime las opciones
void Story::displayOptions(const Scene& scene) {
  for (size_t i{0}; i < scene.options.size(); ++i) {
    std::cout << " [" << i + 1 << "] - " << scene.options[i].text << '\n';
  }
}

// Muestra la escena y opciones
void Story::displayScene(const Scene& scene, const int& kLastScene) {
  clearScreen();
  // Imprime Escena id y la descripción
  std::cout << "* " << title << " : Escena [" << scene.id << "-" << kLastScene
            << "] *\n\n";
  std::cout << scene.intro << "\n\n";
}

// Para saber que opcion elige el jugador
int Story::getPlayerChoice(int maxOptions) {
  int playerChoice;
  std::cout << "\nElige una opción [1-" << maxOptions << "] >>> ";
  std::cin >> playerChoice;
  return playerChoice - 1;
}

// Toda la ejecucion del programa
void Story::run() {
  int currentScene{0}, kScenesCount{int(scenes.size())};
  clearScreen();
  while (currentScene >= 0 && currentScene < kScenesCount) {
    // Imprime las escenas
    displayScene(scenes[currentScene], kScenesCount);

    // Mezcla las opciones de las escenas
    vectorShuffle(scenes[currentScene].options);

    // Imprime las opciones de las escenas
    displayOptions(scenes[currentScene]);

    // Asigna e choice la opción elegida por el jugador
    int choice{getPlayerChoice(scenes[currentScene].options.size())};

    // Asigna a nextScene la siguiente escena
    int nextScene{scenes[currentScene].options[choice].nextScene};

    // Busca la siguiente escena por su identificador
    auto it{find_if(scenes.begin(), scenes.end(),
                    [nextScene](const Scene& s) { return s.id == nextScene; })};

    if (it != scenes.end()) {  // Calcula el índice de la siguiente escena
      currentScene = distance(scenes.begin(), it);
    } else {  // Final de la historia
      currentScene = -1;
    }
  }
  clearScreen();
  // Muestra el mensaje de finalización
  std::cout << end_title << "\n\n";
  pressEnter();
}
