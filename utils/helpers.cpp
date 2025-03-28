#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <thread>
#include <boost/asio.hpp>
#include "helpers.hpp"

std::string Helpers::get_current_time()
{
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
    return ss.str();
}

std::string Helpers::format_duration(std::chrono::milliseconds ms)
{
    using namespace std::chrono;
    auto secs = duration_cast<seconds>(ms);
    ms -= duration_cast<milliseconds>(secs);
    auto mins = duration_cast<minutes>(secs);
    secs -= duration_cast<seconds>(mins);

    std::stringstream ss;
    ss << mins.count() << "m " << secs.count() << "s " << ms.count() << "ms";
    return ss.str();
}

std::string Helpers::get_thread_id()
{
     std::stringstream ss;
    ss << std::this_thread::get_id();
    return ss.str();
}

bool Helpers::starts_with(const std::string &str, const std::string &prefix)
{
    return str.size() >= prefix.size() &&
           str.compare(0, prefix.size(), prefix) == 0;
}