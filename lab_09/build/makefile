GPP = g++
EXT = .bin
BIN = ../bin/
SRC = ../
OBJ = ./

compile: $(OBJ)main.o $(OBJ)PESport.o $(OBJ)XPESport.o $(BIN)
	$(GPP) $(OBJ)main.o $(OBJ)PESport.o $(OBJ)XPESport.o \
	-o $(BIN)XPESport$(EXT) -std=c++17

XPESport$(EXT): main.o PESport.o XPESport.o $(BIN)
	$(GPP) main.o PESport.o XPESport.o -o $(BIN)XPESport$(EXT) -std=c++17

main.o: $(SRC)main.cpp $(SRC)XPESport.hpp
	$(GPP) -c $(SRC)main.cpp -o main.o -std=c++17

XPESport.o: $(SRC)XPESport.cpp $(SRC)XPESport.hpp
	$(GPP) -c $(SRC)XPESport.cpp -o XPESport.o -std=c++17
	
PESport.o: $(SRC)PESport.cpp $(SRC)PESport.hpp
	$(GPP) -c $(SRC)PESport.cpp -o PESport.o -std=c++17

PESport$(EXT): main_PE.o PESport.o $(BIN)
	$(GPP) main_PE.o PESport.o -o $(BIN)PESport$(EXT) -std=c++17

main_PE.o: $(SRC)main_PE.cpp $(SRC)PESport.hpp
	$(GPP) -c $(SRC)main_PE.cpp -o main_PE.o -std=c++17

$(BIN): 
	mkdir $(BIN)

.PHONY: clean cleanall

clean:
	rm -f $(OBJ)/*.o

cleanall:
	rm -f $(OBJ)/*.o
	rm -rf $(BIN)

