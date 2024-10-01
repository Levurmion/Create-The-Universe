include ../../common.mk

.PHONY = all

OBJ := $(LINKED_LIST)/objects
BIN := $(LINKED_LIST)/bin

all: linked_list.o main.o
	$(CMD) $(OBJ)/linked_list.o $(OBJ)/main.o -o $(BIN)/main

main.o:
	$(CMD) -c main.cpp -o $(OBJ)/main.o

linked_list.o:
	$(CMD) -c linked_list.cpp -o $(OBJ)/linked_list.o