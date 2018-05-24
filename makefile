CC=g++ -std=c++11

hellomake: project_queue.cpp project_manager.cpp
	@$(CC) -o tester project_queue.cpp project_manager.cpp

addproject: project_queue.o add-project.cpp
	@$(CC) -o addproject add-project.cpp project_queue.o

project_queue.o: project_queue.cpp project_queue.h
	@$(CC) -c project_queue.cpp
