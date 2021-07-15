jf-GoUtil.bin: build/main.o build/jf-GoUtil.o 
	g++ build/main.o build/jf-GoUtil.o -o jf-GoUtil.bin -std=c++17

build/main.o: main.cpp argparse.hpp build
	g++ -c main.cpp -o build/main.o -std=c++17

build/jf-GoUtil.o: jf-GoUtil.cpp build
	g++ -c jf-GoUtil.cpp -o build/jf-GoUtil.o -std=c++17

build: 
	mkdir build
