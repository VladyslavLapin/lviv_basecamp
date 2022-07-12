#include <functional>
#include <unordered_map>
#include <stdexcept>
#include "SearchSettings.h"

using NoArgHandle = std::function<void(SearchSettings&)>;
const std::unordered_map<std::string, NoArgHandle> NoArgs {
    {"--help", [](SearchSettings &s) { s.help = true; }},
    {"-h", [](SearchSettings &s) { s.help = true; }}
};

using OneArgHandle = std::function<void(SearchSettings&, const std::string&)>;
const std::unordered_map<std::string, OneArgHandle> OneArgs {
    {"--file", [](SearchSettings &s, const std::string &arg) {
        s.file = arg;
    }},

    {"--path", [](SearchSettings &s, const std::string &arg) {
        s.path = arg;
    }},
    {"-p", [](SearchSettings &s, const std::string &arg) {
        s.path = arg;
    }}
};

SearchSettings parse_settings(int argc, const char* argv[])
{
    SearchSettings settings;

    // argv[0] is the program name
    for (int i = 1; i < argc; i++) {
        std::string opt = argv[i];

        auto j = NoArgs.find(opt);
        if (j != NoArgs.end()) {
            j->second(settings);
            continue;
        }
        
        auto k = OneArgs.find(opt);
        if (k != OneArgs.end()) {
            ++i;
            if (i < argc) {
                k->second(settings, argv[i]);
            } else {
                throw std::runtime_error {"Missing param after " + opt};
            }
            continue;
        }

        std::cerr << "Unrecognized command-line option: " << opt << std::endl;
    }

    return settings;
}