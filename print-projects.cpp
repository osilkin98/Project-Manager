#include "project_queue.h"
#include <cstdlib>

int main(const int argc, const char **argv) {
  project_manager my_projects;
  switch(argc) {
  case 1:
    goto SINGULAR;
  case 2: {
    if('0' <= argv[1][0] && argv[1][0] <= '9') {
      for(register size_t i = 0;
	  i < (my_projects.size() < atoi(argv[1]) ?
	       my_projects.size() : atoi(argv[1])); ++i) {
	std::cout << i + 1 << '\t' << my_projects[i] << '\n';
      }
      return 0;
    } else {
      goto SINGULAR;
    }
  }
  SINGULAR:
  default:
    my_projects.print();
    return 0;
  }
  return 0;
}
