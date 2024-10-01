include ../../common.mk

.PHONY = all

OBJ := $(HASHMAP)/objects
BIN := $(HASHMAP)/bin


all: hashmap.o main.o
	$(CMD) $(OBJ)/hashmap.o $(OBJ)/main.o -o $(BIN)/main

main.o:
	$(CMD) -c main.cpp -o $(OBJ)/main.o

hashmap.o: linked_list.o
	$(CMD) -c hashmap.cpp -o $(OBJ)/hashmap.o

linked_list.o:
	$(CMD) -c $(LINKED_LIST)/linked_list.cpp -o $(LINKED_LIST)/objects/linked_list.o