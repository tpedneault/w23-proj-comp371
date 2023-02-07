#pragma once

#include <filesystem>
#include <format>
#include <ctime>
#include <sstream>

#define AMBR_LOG_TRACE(message) \
  ambr::Log(ambr::LoggerSeverity::Trace, message, __FILE__, __LINE__)

#define AMBR_LOG_INFO(message) \
  ambr::Log(ambr::LoggerSeverity::Info, message, __FILE__, __LINE__)

#define AMBR_LOG_DEBUG(message) \
  ambr::Log(ambr::LoggerSeverity::Debug, message, __FILE__, __LINE__)

#define AMBR_LOG_WARN(message) \
  ambr::Log(ambr::LoggerSeverity::Warn, message, __FILE__, __LINE__)

#define AMBR_LOG_ERROR(message) \
  ambr::Log(ambr::LoggerSeverity::Error, message, __FILE__, __LINE__)

#define AMBR_LOG_FATAL(message) \
  ambr::Log(ambr::LoggerSeverity::Fatal, message, __FILE__, __LINE__)

namespace ambr {

static const std::vector<std::string> LoggerSeverityColors = {
    "\x1b[90m", "\x1b[32m", "\x1b[0m", "\x1b[33m", "\x1b[31m", "\x1b[35m"};

static const std::vector<std::string> LoggerSeverityNames = {
    "Trace", "Info", "Debug", "Warn", "Error", "Fatal"};

enum class LoggerSeverity : uint8_t { Trace, Info, Debug, Warn, Error, Fatal };

static void Log(LoggerSeverity severity, const std::string& message,
                const char* file, int line) {
  // Strip the path, keep online the filename.
  std::string filename(file);
  const size_t lastSlashPosition = filename.find_last_of("\\/");
  filename.erase(0, lastSlashPosition + 1);

  // Get the timestamp.
  std::time_t now = std::time(nullptr);
  std::tm timeinfo;
  localtime_s(&timeinfo, &now);

  std::stringstream ss;
  ss << std::put_time(&timeinfo, "%Y-%m-%d %H:%M:%S");
  const std::string timestamp = ss.str();

  const std::string& tag = LoggerSeverityNames[static_cast<uint8_t>(severity)];
  const std::string& color =
      LoggerSeverityColors[static_cast<uint8_t>(severity)];
  const std::string formattedMessage = std::format(
      "\x1b[90m{}\x1b[32m {}:{:02d} {}[{:5}]\x1b[0m {}", timestamp, filename, line, color, tag, message);

  std::cout << formattedMessage << std::endl;
};

}  // namespace ambr