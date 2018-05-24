#include "project_queue.h"
#include <cctype>
#include <cstdlib>

/* 
   int main(void) {
   project_manager my_projects;
   std::string my_str;
   for(size_t i = 0; i < 3; ++i) {
   std::cout << "Enter a project name: " << std::flush;
   std::getline(std::cin, my_str);
   my_projects.insert(my_str);
   }
   my_projects.print();
   return 0;
   }
*/

int main(const int argc, const char **argv) {
  project_manager my_projects;
  if(argc == 1) {
    my_projects.print();
  } else {
    bool request_print = false;
    for(register int i = 1; i < argc; ++i) {
      switch(argv[i][1]) {
      case 'p': { // print in iteration
	my_projects.print();
	break;
      }
      case 'P': { // request print
	request_print = true;
	break;
      }
      case 'c':
	my_projects.clear();
	break;
      case 'n': { // new project
	size_t max_project;
	if(i + 1 == argc) { // default to just inserting one project.
	  max_project = 1;
	} else if(!isdigit(argv[i + 1][0])) {
	  max_project = 1;
	} else {
	  max_project = atoi(argv[i + 1]);
	  ++i;
	}
	std::string instr;
	for(register size_t k = 0; k < max_project; ++k) {
	  std::cout << "New Project Name: " << std::flush;
	  std::getline(std::cin, instr);
	  my_projects.insert(instr);
	  std::cout << "added.\n";
	}
	break;
      }
	// case 'r': // remove a project from the top. 
      default: {
	std::cerr << "Unknown argument, skipping.\n";
	break;
      }
      }
    }
    if(request_print) {
      my_projects.print();
    }
  }
  
}
