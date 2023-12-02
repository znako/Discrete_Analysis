CXXFLAGS+=-std=c++11 -w -O2 -Wextra -Wall -Werror -Wno-sign-compare -Wno-unused-result -pedantic -lm
CXX=g++



main: main.o
	$(CXX) $^ $(CXXFLAGS) -o main

main.o: main.cpp TPair.hpp TBTree.hpp
	$(CXX) $^ $(CXXFLAGS) -c main.cpp

run:
	./main

pack:
	zip lab.zip -r Makefile src