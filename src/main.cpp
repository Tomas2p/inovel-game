// Main.cpp para el programa principal de la novela
#include <filesystem>
#include <iostream>
#include <vector>

#include "story.hpp"

int main(int argc, char* argv[]) {
  // Verificar si se proporcionó un argumento con la ruta de la carpeta
  if (argc < 2) {
    std::cerr << "Debe proporcionar la ruta de la carpeta de historias como "
                 "argumento.\n";
    return 1;
  }

  std::filesystem::path historiasDir{argv[1]};

  // Verificar si la ruta de la carpeta es válida
  if (!std::filesystem::is_directory(historiasDir)) {
    std::cerr << "\nLa ruta proporcionada no es una carpeta válida.\n";
    return 1;
  }

  // Limpia la pantalla
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif

  std::cout << "* INovel++ interactive novel *\n\n";
  std::vector<std::string> historiasDisponibles;

  // Obtener todas las historias disponibles en la carpeta
  for (const auto& entry :
       std::filesystem::recursive_directory_iterator(historiasDir)) {
    if (entry.path().extension() == ".txt") {
      historiasDisponibles.push_back(entry.path().string());
    }
  }

  // Si no hay historias
  if (historiasDisponibles.empty()) {
    std::cout << "No se encontraron historias disponibles en " << historiasDir
              << " y sus subdirectorios.\n";
    return 1;
  }

  // Mostrar las historias disponibles al usuario
  std::cout << "Hay " << historiasDisponibles.size()
            << " historias disponibles en " << historiasDir << "/:\n\n";
  for (size_t i = 0; i < historiasDisponibles.size(); ++i) {
    int posStart{int(historiasDisponibles[i].find_last_of('/'))},
        posEnd{int(historiasDisponibles[i].find_first_of('.'))};
    std::cout << " [" << i + 1 << "] - "
              << historiasDisponibles[i].substr(posStart + 1,
                                                (posEnd - posStart) - 1)
              << std::endl;
  }

  // Solicitar al usuario que elija una historia
  int opcion;
  std::cout << "\nSeleccione la historia a jugar >>> ";
  std::cin >> opcion;

  // Verificar la opción seleccionada
  if (opcion >= 1 && opcion <= static_cast<int>(historiasDisponibles.size())) {
    int posEnd{int(historiasDisponibles[opcion - 1].find_first_of('.'))};
    std::string filename{historiasDisponibles[opcion - 1].substr(0, posEnd)};
    Story story(filename);
    story.run();
  } else {
    std::cout << "Opción inválida. Saliendo del programa.\n";
  }

  return 0;
}
