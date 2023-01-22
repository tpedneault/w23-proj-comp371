#pragma once

namespace sc {

class SystemManager {
  virtual void Start() = 0;
  virtual void Update() = 0;
  virtual void Close() = 0;
};

};