/*
** EPITECH PROJECT, 2024
** B-CPP-500-TLS-5-2-rtype-anastasia.bouby
** File description:
** Logger.hpp
*/

#pragma once

#include <sstream>
#include <string>

/**
 * @class Logger
 * @brief A utility class for logging messages with various severity levels.
 *
 * The `Logger` class provides static methods to log messages in a standardized
 * format. Each log message includes a timestamp, severity level, and custom
 * text.
 */
class Logger {
  public:
    /**
     * @brief Logs an informational message.
     * @param message The message to log.
     */
    static void info(const std::string& message);

    /**
     * @brief Logs a success message.
     * @param message The message to log.
     */
    static void success(const std::string& message);

    /**
     * @brief Logs a warning message.
     * @param message The message to log.
     */
    static void warning(const std::string& message);

    /**
     * @brief Logs an error message.
     * @param message The message to log.
     */
    static void error(const std::string& message);

    /**
     * @brief Logs a message related to socket operations.
     * @param message The message to log.
     */
    static void socket(const std::string& message);

    /**
     * @brief Logs a message related to packet handling.
     * @param message The message to log.
     */
    static void packet(const std::string& message);

    /**
     * @brief Logs a message related to thread operations.
     * @param message The message to log.
     */
    static void thread(const std::string& message);

    /**
     * @brief Logs a debug message for troubleshooting.
     * @param message The message to log.
     */
    static void debug(const std::string& message);

    /**
     * @brief Logs a trace message for detailed program flow information.
     * @param message The message to log.
     */
    static void trace(const std::string& message);

  private:
    /**
     * @brief Logs a message with a specific color and severity level.
     *
     * @param message The message to log.
     * @param color The color code for the message.
     * @param level The severity level of the message (e.g., `[INFO]`).
     */
    static void log(const std::string& message, const std::string& color,
                    const std::string& level);

    /**
     * @brief Generates a timestamp for log messages.
     *
     * @return A formatted timestamp string (e.g., "2024-12-05 14:32:10.123").
     */
    static std::string getTimestamp();
};
