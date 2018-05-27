CC=g++ -std=c++11

project_manager: project_queue.cpp project_manager.cpp
	@$(CC) -o tester project_queue.cpp project_manager.cpp

print-project: project_queue.o print-projects.cpp
	@$(CC) -o print-projects print-projects.cpp project_queue.o

add-project: project_queue.o add-project.cpp
	@$(CC) -o add-project add-project.cpp project_queue.o

remove-project:	tries.o project_queue.o remove-project.cpp
	echo "Compiling the remove-project utility"
	@$(CC) -o remove-project remove-project.cpp tries.o project_queue.o

project_queue.o: project_queue.cpp project_queue.h
	@$(CC) -c project_queue.cpp

tries.o: tries.cpp tries.h
	echo "Creating Object File for Tries Class"
	@$(CC) -c tries.cpp
