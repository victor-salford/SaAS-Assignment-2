#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <thread>

class Helpers
{
public:
    Helpers() = delete;

    // Time-related utilities
    static std::string get_current_time();
    static std::string format_duration(std::chrono::milliseconds ms);

    // Thread utilities
    static std::string get_thread_id();

    // String utilities
    static bool starts_with(const std::string &str, const std::string &prefix);
};

#endif