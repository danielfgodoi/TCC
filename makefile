all:
	cd GlobalBlockAlignment \
	mkdir -p bin/ && g++ src/Main.cpp src/BlockAlignment.cpp -o bin/BlockAlignment -Ofast -std=c++11
	
	cd LocalBlockAlignment \
	mkdir -p bin/ && g++ src/Main.cpp src/BlockAlignment.cpp -o bin/BlockAlignment -Ofast -std=c++11
	
	cd LocalBlockAlignment\ \(concatenation\)/ \
	mkdir -p bin/ && g++ src/Main.cpp src/BlockAlignment.cpp -o bin/BlockAlignment -Ofast -std=c++11
	
	cd Semi-GlobalBlockAlignment \
	mkdir -p bin/ && g++ src/Main.cpp src/BlockAlignment.cpp -o bin/BlockAlignment -Ofast -std=c++11
	
	@echo ""