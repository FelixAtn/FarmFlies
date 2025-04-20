#pragma once

enum class LogLevel
{
	INFO,
	WARNING,
	ERROR_
};

class Log
{
public:

	static void Print(const std::string& text, LogLevel level = LogLevel::INFO)
	{
		std::string logMessage = GetLogLevel(level) + " " + text;
		std::cout << logMessage << std::endl;
	}

	template <typename T>
	static void Print(const std::string& text, T variable, LogLevel level = LogLevel::INFO)
	{
		std::string logMessage = GetLogLevel(level) + " " + text + ": ";
		std::cout << logMessage << variable << std::endl;
	}

	template <typename T> 
	static void PrintMemory(const std::string& text, const T& variable, LogLevel level = LogLevel::INFO)
	{
		std::string logMessage = GetLogLevel(level) + " " + text + ": ";
		std::cout << logMessage << static_cast<const void*>(&variable) << std::endl;
	}
private:
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

