# makefile for the maze problem
CXX := g++
CXXFLAGS := -std=c++11
SRC := $(wildcard *.cpp)

target: $(SRC) conio.h
	$(CXX) $(CXXFLAGS) -o $@ $(SRC)

clean:
	$(RM) target
