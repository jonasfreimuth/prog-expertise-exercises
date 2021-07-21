# where prject specific header files lie
INC = ./

# where object files will be stored
OBJ = ./build/

# file extension for executables
EXT = .bin

# compiler path
CC =  g++

# compiler flags
CF = -std=c++17

compile: $(OBJ)main.o $(OBJ)class.o 
$(CC) $(OBJ)/main.o $(OBJ)class.o  -o class$(EXT) $(CF)

class$(EXT): $(OBJ)main.o $(OBJ)class.o 
$(CC) $(OBJ)main.o $(OBJ)class.o  -o class$(EXT) $(CF)

$(OBJ)main.o: main.cpp $(INC)argparse.hpp $(OBJ)
	$(CC) -c main.cpp -o $(OBJ)main.o  $(CF)

$(OBJ)class.o: class.cpp $(INC)argparse.hpp $(INC)class.hpp $(OBJ)
	$(CC) -c class.cpp -o $(OBJ)class.o  $(CF)

build:
	mkdir $(OBJ)

.PHONY: clean, cleanall

# remove object files that were created during compilation
clean:
	rm -rf $(OBJ)

# reset directory to the state before compilation, deleting also
# all binary files
cleanall:
	rm -rf $(OBJ) *$(EXT)