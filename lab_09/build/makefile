GPP = g++
SRC = ../

XPESports: main.o PESport.o XPESport.o
	$(GPP) main.o PESport.o XPESport.o -o $(SRC)XPESport

main.o: $(SRC)main.cpp $(SRC)XPESport.h
	$(GPP) -c $(SRC)main.cpp -o main.o

XPESport.o: $(SRC)XPESport.cpp $(SRC)XPESport.h
	$(GPP) -c $(SRC)XPESport.cpp -o XPESport.o
	
PESport.o: $(SRC)PESport.cpp $(SRC)PESport.h
	$(GPP) -c $(SRC)PESport.cpp -o PESport.o

.PHONY: clean

clean:
	rm -f ./*.o
