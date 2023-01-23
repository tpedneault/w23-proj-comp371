#pragma once

namespace sc {

class SystemManager {
 public:
  virtual void Start() = 0;
  virtual void Update() = 0;
  virtual void Close() = 0;
 protected:
  unsigned int m_Id;
};

};