#include <iostream>
#include "search.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Wrong number of arguments!" << std::endl;
        return -1;
    }
    
    if (!find(argv[1])) {
        std::cerr << "File is not found!" << std::endl;
    }
    return 0;
}