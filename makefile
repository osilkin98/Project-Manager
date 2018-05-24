CC=g++ -std=c++11

hellomake: project_queue.cpp project_manager.cpp
	@$(CC) -o tester project_queue.cpp project_manager.cpp

print-project: project_queue.o print-projects.cpp
	@$(CC) -o print-projects print-projects.cpp project_queue.o

add-project: project_queue.o add-project.cpp
	@$(CC) -o addproject add-project.cpp project_queue.o

project_queue.o: project_queue.cpp project_queue.h
	@$(CC) -c project_queue.cpp

