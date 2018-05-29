#include "libs/project_queue.h"
#include <cctype>

// clear all projects
int main(const int argc, const char **argv) {
  std::cout << "Are you sure you want to clear all projects?[y/n] " << std::flush;
  char c;
  std::cin >> c;
  std::cin.clear();
  std::cin.ignore(256, '\n');
  while(tolower(c) != 'y' && tolower(c) != 'n') {
    std::cout << "Invalid response, please enter \"Yes\" or \"No\": " << std::flush;
    std::cin >> c;
    std::cin.clear();
    std::cin.ignore(256, '\n');
  }
  
  if(tolower(c) == 'y') {
    project_manager my_projects;
    std::cout << "Clearing queue... ";
    my_projects.clear();
    std::cout << "done." << std::endl;
  }
  return 0;
}
