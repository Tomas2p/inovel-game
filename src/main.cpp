// Main.cpp para el programa principal de la novela
#include <filesystem>
#include <iostream>
#include <vector>

#include "story.hpp"

int main(int argc, char* argv[]) {
  // Limpia la pantalla
#ifdef _WIN32
  system("cls");
#else
  system("clear");
#endif

  std::string historiasDir{argv[1]};
  std::vector<std::string> historiasDisponibles;

  // Obtener todas las historias disponibles en la carpeta
  for (const auto& entry : std::filesystem::directory_iterator(historiasDir)) {
    if (entry.path().extension() == ".txt") {
      historiasDisponibles.push_back(entry.path().stem().string());
    }
  }

  // Mostrar las historias disponibles al usuario
  std::cout << "Historias disponibles en " << historiasDir << "/:\n";
  for (size_t i = 0; i < historiasDisponibles.size(); ++i) {
    std::cout << " [" << i + 1 << "] - " << historiasDisponibles[i]
              << std::endl;
  }

  // Solicitar al usuario que elija una historia
  int opcion;
  std::cout << "\nSeleccione la historia a jugar >>> ";
  std::cin >> opcion;

  // Verificar la opción seleccionada
  if (opcion >= 1 && opcion <= static_cast<int>(historiasDisponibles.size())) {
    std::string filename =
        historiasDir + "/" + historiasDisponibles[opcion - 1] + ".txt";
    Story story(filename);
    story.run();
  } else {
    std::cout << "Opción inválida. Saliendo del programa.\n";
  }

  return 0;
}
