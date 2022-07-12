#include <iostream>
#include <filesystem>
#include "search.h"
#include "SearchSettings.h"

int main(int argc, const char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Wrong number of arguments!" << std::endl;
        return -1;
    }
    SearchSettings settings = parse_settings(argc, argv);

    // FIXME create a function that does some actions according to SearchSettings
    if (settings.help) {
        std::cout << "Help" << std::endl; // FIXME temporary
        return 0;
    }

    if (settings.file.has_value()) {
        if (!find(settings.file.value(), settings.path.value_or(std::filesystem::current_path().root_path().string()))) {
            std::cerr << "File is not found!" << std::endl;
        }
    } else {
        std::cerr << "Missing file name!" << std::endl;
        return -1;
    }

    return 0;
}