#include "project_queue.h"
#include "tries.h"
#include <iostream>
#include <fstream>


#define FILENAME "/home/oleg/.projects/projects.pjts"

#define MAX_PROJECTS 99

project_manager::project_manager(const std::string& fname) : ofilename(fname) {
  // std::cerr << "loading queue... ";
  load_queue(ofilename);
  // std::cerr << "done\n";
}

project_manager::project_manager(void) : project_manager(FILENAME) {
  // std::cerr << "exiting from default constructor\n";
}

void project_manager::load_queue(const std::string& fname) {
  std::ifstream input_file(fname);
  std::string input_string;
  if(input_file.is_open()) {
    std::string title_holder, path_holder;
    size_t a, b;
    std::ifstream file_tracker;
    while( std::getline(input_file, path_holder) ) {
      // to ensure that we don't place the newline character into the queue
      // project_queue.push_back(input_string.substr(0, input_string.size()));

      file_tracker.open(path_holder);
      if(file_tracker.is_open()) {
	std::getline(file_tracker, title_holder);
	a = title_holder.find_first_of('[');
	b = title_holder.find_last_of(']');
	if(a == std::string::npos || b == std::string::npos) { // improperly formatted file
	  std::cerr << "Error: Imporperly formatted file '"<< path_holder << "', skipping\n";
	  file_tracker.close();
	  continue;
	} else { // otherwise it works fine 
	  project_queue.push_back(project(path_holder, title_holder.substr(a + 1, (b - a) - 1)));
	}
      }
      file_tracker.close();
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
      output_file << project_queue.front().location << '\n';
      project_queue.pop_front();
    }
  }
  output_file.close();
}

const std::string& project_manager::operator[](const size_t i) const {
  return project_queue.at(i).title;
}

void project_manager::remove_from_front(void) {
  project_queue.pop_front();
}

void project_manager::insert(std::string path, std::string& new_project) {
  if(project_queue.size() == MAX_PROJECTS) {
    std::cerr << "Error: Cannot insert new project; queue is full\n";
    return;
  }
  project_queue.push_back(project("", new_project));
}

bool project_manager::remove(const std::string& str) {
  prefix_trie tries;
  for(register int i = 0; i < project_queue.size(); ++i) {
    tries.insert(project_queue[i].title, i);
  }
  const int index = tries.retrieve(str);
  if(index == -1) {
    for(register size_t i = 0; i < str.size(); ++i) {
      if(isalpha(str[i])) {
	return false;
      }
    }
    return remove(std::stoi(str));
  } else {
    project_queue.erase(project_queue.begin() + index);
    return true;
  }
}

bool project_manager::remove(const int index) {
  if(index > 0 && index <= project_queue.size()) {
    project_queue.erase(project_queue.begin() + (index - 1));
    return true;
  }
  return false;
}

void project_manager::print(void) const {
  for(register size_t i = 0; i < project_queue.size(); ++i) {
    //std::cout << i + 1 << '\t' << project_queue[i] << '\n';
    project_queue[i]();
  }
  std::cout << std::endl;
}

void project_manager::clear(void) {
  project_queue.clear();
  // std::cerr << "cleared the queue\n";
}

int main(void) {
  project_manager my_projects;
  my_projects.print();
  return 0;
}
