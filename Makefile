ifeq ($(OS),Windows_NT) 
    detected_OS := Windows
else
    detected_OS := $(shell sh -c 'uname 2>/dev/null || echo Unknown')
endif 


ifeq ($(detected_OS), Linux)
exe: main_linux

lib_name := libsearch.a
remove_command := rm
file_name := Searcher
endif

ifeq ($(detected_OS), Windows)
exe: main_windows

lib_name := search.lib
remove_command := del
file_name := Searcher.exe
endif

lib: $(lib_name)

libsearch.a: src/search.cpp
	g++ -std=c++17 -pthread -c src/search.cpp  
	ar rvs libsearch.a search.o
	${remove_command} search.o

search.lib: src/search.cpp
	clang-cl /std:c++17 /c /EHsc src\search.cpp -m64
	llvm-lib search.obj
	${remove_command} search.obj

main_linux: main.cpp search.h lib  
	g++ -std=c++17 -pthread -o ${file_name} main.cpp $(lib_name)

main_windows: main.cpp search.h lib
	clang-cl /Fe${file_name} /EHsc main.cpp -m64 /link ${lib_name}

clean: 
	${remove_command} ${file_name}