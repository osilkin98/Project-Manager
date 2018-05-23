#ifndef PROJECT_MANAGER_H
#define PROJECT_MANAGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <deque>

class project_manager {
private:
  std::deque< std::string > project_queue;
  std::string ofilename;
public:
  project_manager(void);
  project_manager(const std::string& fname);
  ~project_manager(void);
private:
  // 
  void write_queue(void);
  // for reading from a file
  void load_queue(const std::string& fname);
  // void swap_in_queue(const size_t a, const size_t b);
  
public:
  void insert(std::string& new_project);
  void remove_from_front(void);
  void remove(const size_t index);
  void print(void) const;
  void clear(void);
};

#endif
