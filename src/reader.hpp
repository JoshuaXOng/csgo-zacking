#pragma once
#include <Windows.h>
#include <exception>

class ReaderException : public std::runtime_error {
  public:
    ReaderException(const char* message): std::runtime_error(message) {}
};

struct ReaderResult {
  uintptr_t address;
  DWORD value;
};

class Reader {
  public: 
    Reader(HANDLE csgo_process, uintptr_t client_module,  uintptr_t engine_module) {
      this->csgo_process = csgo_process;
      this->client_module = client_module;
      this->engine_module = engine_module;
    }

    virtual ReaderResult get_value() = 0;
  protected:
    HANDLE csgo_process;
    uintptr_t client_module;
    uintptr_t engine_module;
};