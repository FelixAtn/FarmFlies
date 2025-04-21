/*!
 * \file Log.h
 *
 * \brief Provides a lightweight static logging utility for console output.
 *
 * The Log class is designed to help with debugging and structured output to the console.
 * It supports multiple log levels (INFO, WARNING, ERROR) and can display both text
 * and variable values. It also includes a memory address printer for pointer tracking.
 *
 * \author Felix Atanasescu - HE20830
 * \date April 2025
 */

#pragma once

 /**
  * @enum LogLevel
  * @brief Specifies the severity or type of log message.
  */
enum class LogLevel
{
	INFO,    ///< General information about normal operations
	WARNING, ///< A non-critical issue or unexpected behavior
	ERROR_   ///< A critical error that may affect functionality
};

/**
 * @class Log
 * @brief Static utility class for formatted console logging.
 *
 * Supports logging plain text, variables with context, and memory addresses.
 * Automatically prepends log level tags to each message.
 */
class Log
{
public:

	/**
	 * @brief Prints a plain text message with a given log level.
	 *
	 * @param text The message to display.
	 * @param level The severity level (default is LogLevel::INFO).
	 */
	static void Print(const std::string& text, LogLevel level = LogLevel::INFO)
	{
		std::string logMessage = GetLogLevel(level) + " " + text;
		std::cout << logMessage << std::endl;
	}

	/**
	 * @brief Prints a message with an associated variable value.
	 *
	 * The message and value are displayed on the same line for clarity.
	 *
	 * @tparam T The type of the variable.
	 * @param text Descriptive text for the log entry.
	 * @param variable The value to be logged.
	 * @param level The severity level (default is LogLevel::INFO).
	 */
	template <typename T>
	static void Print(const std::string& text, T variable, LogLevel level = LogLevel::INFO)
	{
		std::string logMessage = GetLogLevel(level) + " " + text + ": ";
		std::cout << logMessage << variable << std::endl;
	}

	/**
	 * @brief Prints the memory address of a given variable.
	 *
	 * Useful for debugging object lifetimes, references, or pointer tracking.
	 *
	 * @tparam T The type of the variable.
	 * @param text Descriptive text for the log entry.
	 * @param variable The variable whose address should be displayed.
	 * @param level The severity level (default is LogLevel::INFO).
	 */
	template <typename T>
	static void PrintMemory(const std::string& text, const T& variable, LogLevel level = LogLevel::INFO)
	{
		std::string logMessage = GetLogLevel(level) + " " + text + ": ";
		std::cout << logMessage << static_cast<const void*>(&variable) << std::endl;
	}

private:
	/**
	 * @brief Returns the string representation of a log level.
	 *
	 * @param level The LogLevel to convert.
	 * @return A string tag like "[INFO]", "[WARNING]", or "[ERROR]".
	 */
	static std::string GetLogLevel(LogLevel level)
	{
		switch (level)
		{
		case LogLevel::INFO: return "[INFO]";
		case LogLevel::WARNING: return "[WARNING]";
		case LogLevel::ERROR_: return "[ERROR]";
		default: return "[UNKNOWN]";
		}
	}
};