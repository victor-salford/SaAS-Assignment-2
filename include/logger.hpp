#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <fstream>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>
#include "helpers.hpp"

class Logger
{
public:
    enum class Level
    {
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        CRITICAL
    };

    // Delete copy constructor
    Logger(const Logger &) = delete;

    // Get singleton instance
    static Logger &get_instance()
    {
        static Logger instance;
        return instance;
    }

    // Initialize logger
    static void initialize(const std::string &filename = "", Level min_level = Level::INFO)
    {
        std::lock_guard<std::mutex> lock(get_mutex());

        auto &logger = get_instance();
        logger.min_level_ = min_level;

        if (!filename.empty())
        {
            logger.output_file_.open(filename, std::ios::app);
            if (!logger.output_file_.is_open())
            {
                throw std::runtime_error("Failed to open log file: " + filename);  // Refactor
            }
        }
    }

    // Single logging method
    static void writeToFile(Level level, const std::string &message)
    {
        auto &logger = get_instance();

        // Skip if message level is below minimum
        if (level < logger.min_level_)
        {
            return;
        }

        std::stringstream ss;
        ss << "[" << Helpers::get_current_time() << "] "
           << "[" << Helpers::get_thread_id() << "] "
           << "[" << level_to_string(level) << "] "
           << message << "\n";

        std::lock_guard<std::mutex> lock(get_mutex());

        if (logger.output_file_.is_open())
        {
            logger.output_file_ << ss.str() << std::flush;
        }
        else
        {
            std::cout << ss.str() << std::flush;
        }
    }

private:
    Logger() = default;

    ~Logger()
    {
        if (output_file_.is_open())
        {
            output_file_.close();
        }
    }

    static std::mutex &get_mutex()
    {
        static std::mutex mutex;
        return mutex;
    }

    static std::string level_to_string(Level level)
    {
        switch (level)
        {
        case Level::DEBUG:
            return "DEBUG";
        case Level::INFO:
            return "INFO";
        case Level::WARNING:
            return "WARNING";
        case Level::ERROR:
            return "ERROR";
        case Level::CRITICAL:
            return "CRITICAL";
        default:
            return "UNKNOWN";
        }
    }

    Level min_level_ = Level::INFO;
    std::ofstream output_file_;
};

#endif // LOGGER_HPP