#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <thread>
#include <future>
#include <atomic>
#include "search.h"

std::atomic<bool> is_done;
const auto root = std::filesystem::current_path().root_path();
const int max_thread_count = 8;

bool thread_function(const std::string& path, const std::string& name)
{
    std::filesystem::recursive_directory_iterator rdir_it(path);
    for (auto const& dir_entry : rdir_it) {
        if (is_done.load()) {
            break;
        }
        if (dir_entry.path().filename() == name) {
            is_done = true;
            std::cout << dir_entry.path().string() << std::endl;
            return true;
        }
    }

    return false; 
}

bool find(const std::string& name)
{
    int thread_count = 0;
    std::vector<std::future<bool>> v;
    auto wait_result = [&]()
    {
        for (auto &fut : v)
        {
            if (fut.get())
            {
                return true;
            }
        }
        return false;
    };

    std::filesystem::directory_iterator dir_it(root);
    try 
    {
        for (auto const& dir_entry : dir_it) {
            if (dir_entry.path().filename() == name) {
                std::cout << dir_entry.path().string() << std::endl;
                return true;
            }

            if (dir_entry.is_directory()) {
                if (thread_count == max_thread_count) {
                    if (wait_result()) {
                        return true;
                    }

                    v.resize(0);
                    thread_count = 0;
                }

                std::packaged_task<bool(const std::string&, const std::string&)> task(thread_function);
                v.push_back(task.get_future());
                std::thread t(std::move(task), dir_entry.path().string(), name);
                t.join();
                thread_count++;
            }
        }
    }
    catch(const std::filesystem::filesystem_error& e)
    {
        std::cerr<<e.what()<<std::endl;
        return false;
    }
    return wait_result();
}
