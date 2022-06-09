ifeq ($(OS),Windows_NT) 
    detected_OS := Windows
else
    detected_OS := $(shell sh -c 'uname 2>/dev/null || echo Unknown')
endif 

exe: main

ifeq ($(detected_OS), Linux)
lib_name := libsearch.a
lib: $(lib_name)

endif

libsearch.a: src/search.cpp
	g++ -std=c++17 -pthread -c src/search.cpp  
	ar rvs libsearch.a search.o
	rm search.o

main: main.cpp search.h lib  
	g++ -std=c++17 -pthread -o Searcher main.cpp $(lib_name)

clean: 
	rm Searcher