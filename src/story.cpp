// Metodos de la clase story
#include "story.hpp"

#include <algorithm>
#include <cstdlib>  // Para el comando clear
#include <fstream>
#include <iomanip>
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
  // Inicializacion de variables
  std::ifstream file(filename + ".txt");
  int sceneIDCount{1};
  std::string line;
  int currentSceneIndex{-1};
  const char kCommentPrefix{'#'};

  // Abrir archivo
  if (!file.is_open()) {
    std::cerr << "Error al abrir el archivo " << filename << ".txt.\n";
    return;
  }

  while (std::getline(file, line)) {
    // Encuentra la posicion de '.' en la linea de texto
    const int kPosOfCharToFilter{static_cast<int>(line.find_first_of('.')) + 1};

    // Ignorar lineas vacías o de comentarios
    if (line.empty() || line[0] == kCommentPrefix) continue;

    switch (line[0]) {
      case 'T': {  // Comienza con 'T', es el titulo de la historia
        title = line.substr(kPosOfCharToFilter);
        break;
      }

      case 'E': {  // Comienza con 'E', es una nueva escena
        // Extrae el identificador de la escena
        int id{sceneIDCount++};
        // Crea la nueva escena y la agrega al vector
        Scene newScene{id, line.substr(kPosOfCharToFilter)};
        currentSceneIndex = scenes.size();
        scenes.emplace_back(newScene);
        break;
      }

      case 'A': {  // Pixel Art
        std::string word = line.substr(kPosOfCharToFilter);
        scenes[currentSceneIndex].pixelArt =
            loadPixelArtFromFile(filename, word);
        break;
      }

      case '+':    // Opcion '+' avanza escena
      case '-': {  // Opcion '-' retrocede escena
        Option newOption;
        newOption.text = line.substr(kPosOfCharToFilter);
        if (line[1] != '.') {
          // Valor de la siguiente escena es tamaño scenes - line[1]
          newOption.nextScene =
              static_cast<int>(scenes.size() + std::stoi(line.substr(
                                                   0, kPosOfCharToFilter - 1)));
        } else {
          // Valor de siguiente escena es tamaño scenes - 1
          newOption.nextScene =
              static_cast<int>(scenes.size() + (line[0] == '+' ? 1 : -1));
        }
        scenes[currentSceneIndex].options.emplace_back(newOption);
        break;
      }

      case 'F': {  // Comienza con 'F', es el final de la historia
        endTitle = line.substr(kPosOfCharToFilter);
        scenes[currentSceneIndex].options.back().nextScene = -1;
        break;
      }

      default:  // Ignora las líneas vacías, los comentarios y el resto
        break;
    }
  }
  file.close();
}

// Carga el pixelart desde el archivo dado
pixelArt Story::loadPixelArtFromFile(
    const std::string& filename, const std::string& word) {
  pixelArt pixelArt;
  std::ifstream artFile(filename + ".art");
  if (!artFile.is_open()) {
    std::cerr << "Error al abrir el archivo " << filename + ".art.\n";
    return pixelArt;
  }
  std::string line;
  bool foundWord{false}, searchArt{false};
  while (std::getline(artFile, line)) {
    // Ignorar líneas vacías o de comentarios
    if (line.empty() || line[0] == '#') continue;
    // Encontró la línea A indicando el comienzo del arte
    if (line.substr(0, 2) == "A.") {
      if (line.substr(2) == word)
        foundWord = true, searchArt = true;
      else
        searchArt = false;
      continue;
    }
    if (searchArt) pixelArt.emplace_back(line.begin(), line.end());
  }
  artFile.close();
  if (!foundWord) {
    std::cerr << "No se encontró el arte para la palabra \"" << word
              << "\" en el archivo " << filename + ".art"
              << ".\n";
  }
  return pixelArt;
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
      // auto it = colorMap.find(c);
      // Imprime el caracter correspondiente o espacio
      // !ispunct(int(c))
      //     ? (it != colorMap.end() ? (std::cout << it->second + '#' + CRESET)
      //                             : (std::cout << ' '))
      //     : (std::cout << c);
      std::cout << c;
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
  // Imprime Escena id y el titulo de la historia
  std::cout << "* " << title << " : Escena [" << scene.id << "-" << kLastScene
            << "] *\n\n";

  // Imprime el pixel art
  displayPixelArt(scene);

  // Imprime la descripcion de la escena
  std::cout << "\n" << scene.intro << "\n";

  // Imprime las opciones
  displayOptions(scene);
}

// Obtiene el tamaño maximo vertical del pixelart
int Story::getPixelArtWidth(const Scene& scene) {
  int maxWidth{0};
  for (int i{0}; i < int(scene.pixelArt.size()); ++i)
    maxWidth += scene.pixelArt[i].size();
  return maxWidth / int(scene.pixelArt.size());
}

// Para saber que opcion elige el jugador
int Story::getPlayerChoice(int maxOptions) {
  int playerChoice;
  std::cout << "Elige una opción [1-" << maxOptions << "] >>> ";
  std::cin >> playerChoice;
  return playerChoice - 1;
}

// Toda la ejecucion del programa
void Story::run() {
  int currentScene{0}, kScenesCount{int(scenes.size())};
  clearScreen();
  while (currentScene >= 0 && currentScene < kScenesCount) {
    // Mezcla las opciones de las escenas
    vectorShuffle(scenes[currentScene].options);
    // Imprime las escenas
    displayScene(scenes[currentScene], kScenesCount);
    // Asigna a choice la opción elegida por el jugador
    int choice{getPlayerChoice(scenes[currentScene].options.size())};
    // Asigna a nextScene la siguiente escena
    int nextScene{scenes[currentScene].options[choice].nextScene};
    // Busca la siguiente escena por su identificador
    auto it{find_if(scenes.begin(), scenes.end(),
                    [nextScene](const Scene& s) { return s.id == nextScene; })};
    // Pasa a la siguiente escena o alfinal de la historia
    it != scenes.end() ? (currentScene = distance(scenes.begin(), it))
                       : (currentScene = -1);
  }
  clearScreen();
  // Muestra el mensaje de finalización
  std::cout << endTitle << "\n\n";
  pressEnter();
}
