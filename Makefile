CC = g++

INCLUDE_PATHS = -Iinclude

LIBRARY_PATHS = -Llibs

LINKER_FLAGS = -lGL -lglfw 

all: main

main:
	$(CC) main.cpp glad.c $(INCLUDE_PATHS) $(LINKER_FLAGS) -o a