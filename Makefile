ifeq ($(OS),Windows_NT) 
    detected_OS := Windows
else
    detected_OS := $(shell sh -c 'uname 2>/dev/null || echo Unknown')
endif 


ifeq ($(detected_OS), Linux)
exe: main_linux

lib_name := libsearch.a
endif

ifeq ($(detected_OS), Windows)
exe: main_windows

lib_name := search.lib
endif

lib: $(lib_name)

libsearch.a: src/search.cpp
	g++ -std=c++17 -pthread -c src/search.cpp  
	ar rvs libsearch.a search.o
	rm search.o

search.lib: src/search.cpp
	clang-cl /std:c++17 /c /EHsc /MD src\search.cpp
	llvm-lib search.obj
	rm search.obj

main_linux: main.cpp search.h lib  
	g++ -std=c++17 -pthread -o Searcher main.cpp $(lib_name)

main_windows: main.cpp search.h lib
	clang-cl /FeSearcher /EHsc main.cpp /link ${lib_name}

clean: 
	rm Searcher