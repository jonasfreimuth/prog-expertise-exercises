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

## recipes:

jf-GoUtil$(EXT): $(OBJ)main.o $(OBJ)jf-GoUtil.o 
	 $(CC) $(OBJ)main.o $(OBJ)jf-GoUtil.o -o jf-GoUtil$(EXT) $(CF)

compile: $(OBJ)main.o $(OBJ)jf-GoUtil.o 
	 $(CC) $(OBJ)main.o $(OBJ)jf-GoUtil.o -o jf-GoUtil$(EXT) $(CF)

$(OBJ)main.o: main.cpp argparse.hpp $(OBJ)
	 $(CC) -c main.cpp -o $(OBJ)main.o $(CF)

$(OBJ)jf-GoUtil.o: jf-GoUtil.cpp $(OBJ)
	 $(CC) -c jf-GoUtil.cpp -o $(OBJ)jf-GoUtil.o $(CF)

$(OBJ): 
	mkdir $(OBJ)

.PHONY: clean, cleanall

# remove object files that were created during compilation
clean:
	rm -rf $(OBJ)

# reset directory to the state before compilation, deleting also
# all binary files
cleanall:
	rm -rf $(OBJ) *$(EXT)

