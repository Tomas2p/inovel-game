// Metodos de la clase story
#include "story.hpp"

#include <algorithm>
#include <cstdlib>  // Para el comando clear
#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <sstream>

#include "ANSI-color-codes.hpp"  // Colores
#include "tools.hpp"

// Mapa de colores (dark, red, green, yellow, blue, purple, cyan, white)
std::map<char, std::string> colorMap{{'d', BLK}, {'r', RED}, {'g', GRN},
                                     {'y', YEL}, {'b', BLU}, {'m', MAG},
                                     {'c', CYN}, {'w', WHT}};

// Constructor
Story::Story(const std::string& filename) { loadStory(filename); }

// Carga la historia desde el archivo dado
void Story::loadStory(const std::string& filename) {
  std::ifstream file(filename);
  int sceneIDCount{1};
  // Abrir archivo
  if (!file.is_open()) {
    std::cerr << "Error al abrir el archivo " << filename << ".\n";
    return;
  }

  std::string line;
  int currentSceneIndex{-1};

  while (std::getline(file, line)) {
    // Encuentra la posicion de '.' en la linea de texto
    int posChar{int(line.find_first_of('.')) + 1};

    switch (line[0]) {
      case 'T':  // Comienza con 'T', es el título de la historia
        title = line.substr(posChar);
        continue;

      case 'E': {  // Comienza con 'E', es una nueva escena
        // Extrae el identificador de la escena
        int id{sceneIDCount};
        ++sceneIDCount;
        // Crea la nueva escena y la agrega al vector
        Scene newScene;
        newScene.id = id;
        newScene.intro = line.substr(posChar);
        currentSceneIndex = scenes.size();
        scenes.push_back(newScene);
        continue;
      }

      case 'A': {  // Pixel Art
        std::string str{line.substr(posChar)};
        std::vector<char> row;
        for (char c : str) row.push_back(c);
        scenes[currentSceneIndex].pixelArt.push_back(row);
        continue;
      }

      case '+': {  // Opciones '+' correcta
        Option newOption;
        newOption.text = line.substr(posChar);
        if (line[1] != '.') {
          // Valor de la siguiente escena es tamaño scenes + line[1]
          newOption.nextScene = scenes.size() + std::stoi(line.substr(1, 2));
        } else {
          // Valor de siguiente escena es tamaño scenes + 1
          newOption.nextScene = int(scenes.size() + 1);
        }
        scenes[currentSceneIndex].options.push_back(newOption);
        continue;
      }

      case '-': {  // Opcion '-' incorrecta
        Option newOption;
        newOption.text = line.substr(posChar);
        if (line[1] != '.') {
          // Valor de la siguiente escena es tamaño scenes - line[1]
          newOption.nextScene = scenes.size() - std::stoi(line.substr(1, 2));
        } else {
          // Valor de siguiente escena es tamaño scenes - 1
          newOption.nextScene = int(scenes.size() - 1);
        }
        scenes[currentSceneIndex].options.push_back(newOption);
        continue;
      }

      case 'F':  // Comienza con 'F', es el final de la historia
        endTitle = line.substr(posChar);
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

// Imprime el pixel art con los colores asignados
void Story::displayPixelArt(const Scene& scene) {
  for (const auto& row : scene.pixelArt) {
    for (char c : row) {
      auto it = colorMap.find(c);
      if (it != colorMap.end()) {
        // Aplica el color correspondiente al carácter "█"
        std::cout << it->second << "█" << CRESET;
      } else {
        // Imprime espacios ' '
        std::cout << ' ';
      }
    }
    std::cout << std::endl;
  }
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
  // Imprime el pixel art
  displayPixelArt(scene);
  std::cout << "\n" << scene.intro << "\n\n";
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
  std::cout << endTitle << "\n\n";
  pressEnter();
}
