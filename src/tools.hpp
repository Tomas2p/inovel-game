#ifndef TOOLS_HPP
#define TOOLS_HPP
// Funciones adicionales

#include <iostream>
#include <string>

#ifdef _WIN32
const std::string CLEAR_COMMAND = "cls";
#else
const std::string CLEAR_COMMAND = "clear";
#endif

// Limpia la pantalla
void clearScreen() { system(CLEAR_COMMAND.c_str()); }

// Espera a que se presione la tecla ENTER
void pressEnter() {
  std::cout << "Presiona Enter para continuar...";
  std::cin.ignore(), std::cin.get();
  clearScreen();
}

#endif