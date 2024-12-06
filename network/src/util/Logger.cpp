/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Logger.cpp
*/

#include "util/Logger.hpp"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>

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

void Logger::info(const std::string& message) {
    log(message, BLUE, "[INFO]");
}

void Logger::success(const std::string& message) {
    log(message, GREEN, "[SUCCESS]");
}

void Logger::warning(const std::string& message) {
    log(message, YELLOW, "[WARNING]");
}

void Logger::error(const std::string& message) {
    log(message, RED, "[ERROR]");
}

void Logger::socket(const std::string& message) {
    log(message, CYAN, "[SOCKET]");
}

void Logger::packet(const std::string& message) {
    log(message, MAGENTA, "[PACKET]");
}

void Logger::thread(const std::string& message) {
    log(message, PINK, "[THREAD]");
}

void Logger::debug(const std::string& message) {
    log(message, WHITE, "[DEBUG]");
}

void Logger::trace(const std::string& message) {
    log(message, GRAY, "[TRACE]");
}

void Logger::log(const std::string& message, const std::string& color,
                 const std::string& level) {
    std::cout << color << getTimestamp() << " " << level << GRAY << " >>> "
              << RESET << message << std::endl;
}

std::string Logger::getTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto nowTime = std::chrono::system_clock::to_time_t(now);
    auto nowMs = std::chrono::duration_cast<std::chrono::milliseconds>(
                     now.time_since_epoch()) %
                 1000;

    std::ostringstream timestamp;
    timestamp << std::put_time(std::localtime(&nowTime), "%Y-%m-%d %H:%M:%S")
              << "." << std::setfill('0') << std::setw(3) << nowMs.count();
    return timestamp.str();
}
