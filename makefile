CC=g++ -std=c++11
EXE_DIR=/usr/bin

# depracated
# project_manager: project_queue.cpp project_manager.cpp
# 	@$(CC) -o tester project_queue.cpp project_manager.cpp

push: all
	@echo "Compiled all to bin directory and moving to /usr/bin"
	@echo "Copying bins/print-projects"
	@cp bins/print-projects $(EXE_DIR)/print-projects
	@chmod 777 $(EXE_DIR)/print-projects
	@echo "Copying bins/add-project"
	@cp bins/add-project $(EXE_DIR)/add-project
	@chmod 777 $(EXE_DIR)/add-project
	@echo "Copying bins/remove-project"
	@cp bins/remove-project $(EXE_DIR)/remove-project
	@chmod 777 $(EXE_DIR)/remove-project

all: print-project add-project remove-project

clear-projects: tries.o project_queue.o clear-projects.cpp
	@$(CC) -o bins/clear-projects clear-projects.cpp bins/project_queue.o bins/tries.o 

print-project: tries.o project_queue.o print-projects.cpp
	@$(CC) -o bins/print-projects print-projects.cpp bins/project_queue.o bins/tries.o

add-project: tries.o project_queue.o add-project.cpp
	@$(CC) -o bins/add-project add-project.cpp bins/project_queue.o bins/tries.o

remove-project:	tries.o project_queue.o remove-project.cpp
	@echo "Compiling the remove-project utility"
	@$(CC) -o bins/remove-project remove-project.cpp bins/tries.o bins/project_queue.o

project_queue.o: tries.o libs/project_queue.cpp libs/project_queue.h
	@$(CC) -c libs/project_queue.cpp -o bins/project_queue.o

tries.o: libs/tries.cpp libs/tries.h
	@echo "Creating Object File for Tries Class"
	@$(CC) -c libs/tries.cpp -o bins/tries.o
