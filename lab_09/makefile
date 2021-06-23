GPP = g++
EXT = .bin
OBJ = ./build/
SRC = ./

compile: $(OBJ)main.o $(OBJ)PESport.o $(OBJ)XPESport.o
	$(GPP) $(OBJ)main.o $(OBJ)PESport.o $(OBJ)XPESport.o \
	-o $(SRC)XPESport$(EXT) -std=c++17

XPESport$(EXT): $(OBJ)main.o $(OBJ)PESport.o $(OBJ)XPESport.o
	$(GPP) $(OBJ)main.o $(OBJ)PESport.o $(OBJ)XPESport.o \
	-o $(SRC)XPESport$(EXT) -std=c++17

$(OBJ)main.o: $(SRC)main.cpp $(SRC)XPESport.hpp $(OBJ)
	$(GPP) -c $(SRC)main.cpp -o $(OBJ)main.o -std=c++17

$(OBJ)XPESport.o: $(SRC)XPESport.cpp $(SRC)XPESport.hpp $(OBJ)
	$(GPP) -c $(SRC)XPESport.cpp -o $(OBJ)XPESport.o \
	-std=c++17
	
$(OBJ)PESport.o: $(SRC)PESport.cpp $(SRC)PESport.hpp
	$(GPP) -c $(SRC)PESport.cpp -o $(OBJ)PESport.o \
	-std=c++17

PESport$(EXT): main_PE.o PESport.o
	$(GPP) $(OBJ)main_PE.o $(OBJ)PESport.o -o $(SRC)PESport$(EXT) \
	-std=c++17

$(OBJ)main_PE.o: $(SRC)main_PE.cpp $(SRC)PESport.hpp $(OBJ)
	$(GPP) -c $(SRC)main_PE.cpp -o $(OBJ)main_PE.o -std=c++17

 $(OBJ): 
	mkdir $(OBJ)

.PHONY: clean

clean:
	rm -f $(OBJ)*.o
