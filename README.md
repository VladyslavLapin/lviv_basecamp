# Version 1.0 of search system program

- Make program of searching in root linux directory 
(If you want to switch searching path, you can change it in "search.cpp")

## Steps to prepare for build:

1. install cmake >= 3.8.2
2. install latest git
3. open terminal, go to location for project
4. checkout
```
git clone https://github.com/VladyslavLapin/lviv_basecamp.git
```

# Build on Windows for Windows
1. install Visual Studio 2019 or 2017
2. open terminal, go to "lviv_basecamp"
```
# build with VS 2019
cmake -B ./build/windows -G "Visual Studio 16 2019" -DCMAKE_GENERATOR_PLATFORM=x64 -DCMAKE_BUILD_TYPE=Release

# build with VS 2017
cmake -B ./build/windows -G "Visual Studio 15 2017" -DCMAKE_GENERATOR_PLATFORM=x64 -DCMAKE_BUILD_TYPE=Release

# build the app
cmake --build ./build/windows --config Release
```

# Build on Linux for Linux
1. open terminal, go to "lviv_basecamp"
```
# configure cmake
cmake -B ./build/linux -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release

# build the app
cmake --build ./build/linux --config Release
```