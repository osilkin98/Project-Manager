#include "project_queue.h"
#include <iostream>
#include <fstream>

#define FILENAME "/home/oleg/.projects/projects.pjts"




project_manager::project_manager(const std::string& fname) : ofilename(fname) {
  std::cerr << "loading queue... ";
  load_queue(ofilename);
  std::cerr << "done\n";
}

project_manager::project_manager(void) : project_manager(FILENAME) {
  std::cerr << "exiting from default constructor\n";
}

void project_manager::load_queue(const std::string& fname) {
  std::ifstream input_file(fname);
  std::string input_string;
  if(input_file.is_open()) {
    while( std::getline(input_file, input_string) ) {
      // to ensure that we don't place the newline character into the queue
      project_queue.push_back(input_string.substr(0, input_string.size()));
    }
  } else {
    std::cerr << "file could not open\n";
  }
  input_file.close();
}

project_manager::~project_manager(void) {
  std::cerr << "printing to " << ofilename << "... ";
  write_queue();
  std::cerr << "done.\n";
}

void project_manager::write_queue(void) {
  std::ofstream output_file(ofilename);
  // while the queue is non-empty
  if(output_file.is_open()) {
    while(project_queue.size()) {
      output_file << project_queue.front() << '\n';
      project_queue.pop_front();
    }
  }
  output_file.close();
}



void project_manager::remove_from_front(void) {
  project_queue.pop_front();
}

void project_manager::insert(std::string& new_project) {
  project_queue.push_back(new_project);
}

void project_manager::remove(const size_t index) {
  if(index > 0 && index <= project_queue.size()) {
    project_queue.erase(project_queue.begin() + (index - 1));
  }
}

void project_manager::print(void) const {
  for(register size_t i = 0; i < project_queue.size(); ++i) {
    std::cout << i + 1 << '\t' << project_queue[i] << '\n';
  }
  std::cout << std::endl;
}

void project_manager::clear(void) {
  project_queue.clear();
  std::cerr << "cleared the queue\n";
}
