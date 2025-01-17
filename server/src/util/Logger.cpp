/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Logger.cpp
*/

#include "util/Logger.hpp"

// Colors
const std::string RESET = "\033[0m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string RED = "\033[31m";
const std::string BLUE = "\033[34m";
const std::string PINK = "\033[95m";
const std::string CYAN = "\033[36m";
const std::string MAGENTA = "\033[35m";
const std::string WHITE = "\033[97m";
const std::string GRAY = "\033[90m";

/**
 * @brief Log an info message
 *
 * @param message The message to log
 */
void Logger::info(const std::string& message) {
    log(message, BLUE, "[INFO]");
}

/**
 * @brief Log a success message
 *
 * @param message The message to log
 */
void Logger::success(const std::string& message) {
    log(message, GREEN, "[SUCCESS]");
}

/**
 * @brief Log a warning message
 *
 * @param message The message to log
 */
void Logger::warning(const std::string& message) {
    log(message, YELLOW, "[WARNING]");
}

/**
 * @brief Log an error message
 *
 * @param message The message to log
 */
void Logger::error(const std::string& message) {
    log(message, RED, "[ERROR]");
}

/**
 * @brief Log a socket message
 *
 * @param message The message to log
 */
void Logger::socket(const std::string& message) {
    log(message, CYAN, "[SOCKET]");
}

/**
 * @brief Log a packet message
 *
 * @param message The message to log
 */
void Logger::packet(const std::string& message) {
    log(message, MAGENTA, "[PACKET]");
}

/**
 * @brief Log a thread message
 *
 * @param message The message to log
 */
void Logger::thread(const std::string& message) {
    log(message, PINK, "[THREAD]");
}

/**
 * @brief Log a debug message
 *
 * @param message The message to log
 */
void Logger::debug(const std::string& message) {
    log(message, WHITE, "[DEBUG]");
}

/**
 * @brief Log a trace message
 *
 * @param message The message to log
 */
void Logger::trace(const std::string& message) {
    log(message, GRAY, "[TRACE]");
}

/**
 * @brief Log a message
 *
 * @param message The message to log
 * @param color The color to use
 * @param level The level of the message
 */
void Logger::log(const std::string& message, const std::string& color,
                 const std::string& level) {
    std::cout << color << getTimestamp() << " " << level << GRAY << " >>> "
              << RESET << message << std::endl;
}

/**
 * @brief Get the current timestamp
 *
 * @return std::string The timestamp
 */
std::string Logger::getTimestamp() {
    const auto now = std::chrono::system_clock::now();
    const auto nowTime = std::chrono::system_clock::to_time_t(now);
    const auto nowMs = std::chrono::duration_cast<std::chrono::milliseconds>(
                           now.time_since_epoch()) %
                       1000;

    std::ostringstream timestamp;
    timestamp << std::put_time(std::localtime(&nowTime), "%Y-%m-%d %H:%M:%S")
              << "." << std::setfill('0') << std::setw(3) << nowMs.count();

    return timestamp.str();
}
