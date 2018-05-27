#include "libs/project_queue.h"

int main(const int argc, const char **argv) {
  if(argc == 1) {
    std::cerr << argv[0] << ": No Arguments Specified\n";
    return 1;
  } else {
    project_manager my_projects;
    std::string instr;
    for(register int i = 1; i < argc; ++i) {
      instr = argv[i];
      my_projects.insert(instr);
    }
    std::cout << "Current Queue:\n";
    my_projects.print();
    std::cout << std::endl;
    return 0;
  }
}
