GPP = g++
EXT = .bin
SRC = ../

XPESport$(EXT): main.o PESport.o XPESport.o
	$(GPP) main.o PESport.o XPESport.o -o $(SRC)XPESport$(EXT)

main.o: $(SRC)main.cpp $(SRC)XPESport.hpp
	$(GPP) -c $(SRC)main.cpp -o main.o

XPESport.o: $(SRC)XPESport.cpp $(SRC)XPESport.hpp
	$(GPP) -c $(SRC)XPESport.cpp -o XPESport.o
	
PESport.o: $(SRC)PESport.cpp $(SRC)PESport.hpp
	$(GPP) -c $(SRC)PESport.cpp -o PESport.o

PESport$(EXT): main_PE.o PESport.o
	$(GPP) main_PE.o PESport.o -o $(SRC)PESport$(EXT)

main_PE.o: $(SRC)main_PE.cpp $(SRC)PESport.hpp
	$(GPP) -c $(SRC)main_PE.cpp -o main_PE.o

.PHONY: clean

clean:
	rm -f ./*.o
