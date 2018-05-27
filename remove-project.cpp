#include "project_queue.h"



int main(const int argc, const char **argv) {
  if(argc > 2) { // invalid for now
    std::cerr << "Error: Too many parameters. Did you mean to use quotation marks?\n";
    return 1;
  } else {
    project_manager projects;
    std::string str;
    if(argc == 2) {
      str = argv[1];
      
    } else {
      projects.print();
      std::cout << "Select The Project You'd Like to Remove: " << std::flush;
      std::getline(std::cin, str);
    }
    
    if(projects.remove(str)) {
      std::cout << "Done." << std::endl;
      return 0;
    } else {
      std::cout << "Could Not Locate Project." << std::endl;
      return 1;
    }
  }
}
