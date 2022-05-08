#pragma once
#include <Windows.h>

class Writer {
  public: 
    Writer(HANDLE csgo_process, uintptr_t client_module,  uintptr_t engine_module) {
      this->csgo_process = csgo_process;
      this->client_module = client_module;
      this->engine_module = engine_module;
    }

    virtual void set_value(DWORD* value) = 0;
  protected:
    HANDLE csgo_process;
    uintptr_t client_module;
    uintptr_t engine_module;
};