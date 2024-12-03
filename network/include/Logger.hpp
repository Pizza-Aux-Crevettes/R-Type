/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Logger.hpp
*/

#pragma once

#include <sstream>
#include <string>

class Logger {
  public:
    static void info(const std::string& message);
    static void success(const std::string& message);
    static void warning(const std::string& message);
    static void error(const std::string& message);

  private:
    static void log(const std::string& message, const std::string& color,
                    const std::string& level);
    static std::string getTimestamp();
};
