HEADERS = -I.\
		-I include

SOURCES = source/ej1.cpp 

Ej1 : 
	g++ -std=c++17 -Wall -Wextra -Wpedantic -pthread $(HEADERS) -g example/main.cpp $(SOURCES) -o ej1
	./ej1

clean : 
	rm -f ej1 
	rm -f *.dSYM/ 

