#pragma once

#include <filesystem>
#include <format>
#include <ctime>
#include <sstream>

#define ZOOM_LOG_TRACE(message) \
  Zoom::Log(Zoom::LoggerSeverity::TRACE, message, __FILE__, __LINE__)

#define ZOOM_LOG_INFO(message) \
  Zoom::Log(Zoom::LoggerSeverity::INFO, message, __FILE__, __LINE__)

#define ZOOM_LOG_DEBUG(message) \
  Zoom::Log(Zoom::LoggerSeverity::DEBUG, message, __FILE__, __LINE__)

#define ZOOM_LOG_WARN(message) \
  Zoom::Log(Zoom::LoggerSeverity::WARN, message, __FILE__, __LINE__)

#define ZOOM_LOG_ERROR(message) \
  Zoom::Log(Zoom::LoggerSeverity::ERROR, message, __FILE__, __LINE__)

#define ZOOM_LOG_FATAL(message) \
  Zoom::Log(Zoom::LoggerSeverity::FATAL, message, __FILE__, __LINE__)

namespace Zoom {

static const std::vector<std::string> LoggerSeverityColors = {
    "\x1b[90m", "\x1b[32m", "\x1b[0m", "\x1b[33m", "\x1b[31m", "\x1b[35m"};

static const std::vector<std::string> LoggerSeverityNames = {
    "TRACE", "INFO", "DEBUG", "WARN", "ERROR", "FATAL"};

enum class LoggerSeverity : uint8_t { TRACE, INFO, DEBUG, WARN, ERROR, FATAL };

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
      "{:>16}:{:02d} {} {}[{:5}]\x1b[0m {}", filename, line, timestamp, color, tag, message);

  std::cout << formattedMessage << std::endl;
};

}  // namespace Zoom