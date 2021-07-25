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

compile: $(OBJ)main.o $(OBJ)jf-FASTA-parser.o 
	$(CC) $(OBJ)/main.o $(OBJ)jf-FASTA-parser.o  -o jf-FASTA-parser$(EXT) $(CF)

jf-FASTA-parser$(EXT): $(OBJ)main.o $(OBJ)jf-FASTA-parser.o 
	$(CC) $(OBJ)main.o $(OBJ)jf-FASTA-parser.o  -o jf-FASTA-parser$(EXT) $(CF)

$(OBJ)main.o: main.cpp $(INC)argparse.hpp $(OBJ)
	$(CC) -c main.cpp -o $(OBJ)main.o  $(CF)

$(OBJ)jf-FASTA-parser.o: jf-FASTA-parser.cpp $(INC)argparse.hpp $(INC)jf-FASTA-parser.hpp $(OBJ)
	$(CC) -c jf-FASTA-parser.cpp -o $(OBJ)jf-FASTA-parser.o  $(CF)

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