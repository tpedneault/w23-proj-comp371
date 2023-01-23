#pragma once

#include <cstdint>

namespace sc {

enum class EventCode : uint16_t {
  LOG_TRACE,
  LOG_DEBUG,
  LOG_INFO,
  LOG_WARN,
  LOG_ERROR,
  LOG_FATAL,
};

struct Event {
  EventCode code;
  void* data;
};

};