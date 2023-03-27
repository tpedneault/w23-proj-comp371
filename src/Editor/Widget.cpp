#include "Editor/Widget.h"

namespace ambr {
Widget::Widget(const String &id) : m_ID(id) {}

std::vector<Event> Widget::ForwardEvents() {
  std::vector<Event> events;
  for (const Event e : m_EventQueue) {
    events.push_back(e);
  }
  m_EventQueue.clear();
  return events;
}

void Widget::PublishEvent(const Event &e) {
  m_EventQueue.push_back(e);
}

void Widget::ProcessEvent(const Event &e) {
  switch (e.code) {
    default:
      break;
  }
}

const String &Widget::GetID() const {
  return m_ID;
}

};


