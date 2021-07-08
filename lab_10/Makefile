GCC = g++
EXT = .bin
OBJ = ./build/
SRC = ./

compile: $(OBJ)jf-needle.o
	$(GCC) $(OBJ)jf-needle.o -o jf-needle$(EXT) --std=c++17

jf-needle$(EXT): $(OBJ)jf-needle.o
	$(GCC) $(OBJ)jf-needle.o -o jf-needle$(EXT) --std=c++17

$(OBJ)jf-needle.o: $(SRC)jf-needle.cpp $(SRC)Blosum.cpp  $(OBJ)
	$(GCC) -c $(SRC)jf-needle.cpp -o $(OBJ)jf-needle.o --std=c++17

$(OBJ): 
	mkdir $(OBJ)

.PHONY: clean

clean:
	rm -rf $(OBJ)