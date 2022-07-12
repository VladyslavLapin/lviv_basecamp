#ifndef SEARCH_SETTINGS_H
#define SEARCH_SETTINGS_H

#include <iostream>
#include <optional>
#include <string>

struct SearchSettings {
    bool help {false};
    std::optional<std::string> file;
    std::optional<std::string> path;
};

SearchSettings parse_settings(int argc, const char* argv[]);

#endif