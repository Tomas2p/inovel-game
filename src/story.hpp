#pragma once
#include <string>
#include <vector>

#include "option.hpp"
#include "scene.hpp"

// Clase para gestionar la historia
class Story {
 public:
  Story(const std::string& filename);
  void run();

 private:
  void loadStory(const std::string& filename);
  void displayScene(const Scene& scene);
  int getPlayerChoice(int maxOptions);

  std::string title;
  std::vector<Scene> scenes;
};
