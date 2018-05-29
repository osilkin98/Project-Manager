#ifndef PROJECT_MANAGER_H
#define PROJECT_MANAGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <deque>

struct project {
  std::string location, title;
  void operator()(void) const { std::cout << title << ": " << location << std::endl; }
  project(const std::string& fpath, const std::string& pname)
    : location(fpath), title(pname) { }
};


class project_manager {
private:
  std::deque< project > project_queue; // stores locations of .pjt files
  std::string ofilename;
public:
  project_manager(void);
  project_manager(const std::string& fname);
  ~project_manager(void);
private:
  // currently writes to the queue the locations of the pjt files
  void write_queue(void);
  
  // for reading from a file
  void load_queue(const std::string& fname);

  // void swap_in_queue(const size_t a, const size_t b);
  
public:
  const size_t size(void) const { return project_queue.size(); }

  // returns the title of the project object at index i
  const std::string& operator[](const size_t i) const;

  // inserts a new project under the default local directory
  void insert(std::string& new_project);

  // inserts a project file at path
  void insert(std::string path, std::string& new_project);

  // checks to see if an exisiting .pjt file exists at path.
  // if so, it inserts it into the queue, otherwise, it exists.
  void insert_path(std::string path);

  void remove_from_front(void);

  // removes a file from queue based on index
  bool remove(const int index);

  // removes a file from the queue based on the project name
  bool remove(const std::string& str);

  void print(void) const;

  void clear(void);
};




#endif
