GPP = g++
EXT = .bin
SRC = ../

XPESport$(EXT): main.o PESport.o XPESport.o
	$(GPP) main.o PESport.o XPESport.o -o $(SRC)XPESport$(EXT) -std=c++17

main.o: $(SRC)main.cpp $(SRC)XPESport.hpp
	$(GPP) -c $(SRC)main.cpp -o main.o -std=c++17

XPESport.o: $(SRC)XPESport.cpp $(SRC)XPESport.hpp
	$(GPP) -c $(SRC)XPESport.cpp -o XPESport.o -std=c++17
	
PESport.o: $(SRC)PESport.cpp $(SRC)PESport.hpp
	$(GPP) -c $(SRC)PESport.cpp -o PESport.o -std=c++17

PESport$(EXT): main_PE.o PESport.o
	$(GPP) main_PE.o PESport.o -o $(SRC)PESport$(EXT) -std=c++17

main_PE.o: $(SRC)main_PE.cpp $(SRC)PESport.hpp
	$(GPP) -c $(SRC)main_PE.cpp -o main_PE.o -std=c++17

.PHONY: clean

clean:
	rm -f ./*.o
