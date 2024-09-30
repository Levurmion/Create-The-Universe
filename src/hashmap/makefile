.PHONY = all

CXX := g++
CXXFLAGS := -Wall -std=c++17
CMD := $(CXX) $(CXXFLAGS)
OBJ := ./objects
BIN := ./bin


all: hashmap.o main.o
	$(CMD) $(OBJ)/hashmap.o $(OBJ)/main.o -o $(BIN)/main

main.o:
	$(CMD) -c main.cpp -o $(OBJ)/main.o

hashmap.o:
	$(CMD) -c hashmap.cpp -o $(OBJ)/hashmap.o