#pragma once
#include <Windows.h>

struct ReaderResult {
  uintptr_t address;
  DWORD value;
};

class Reader {
  public: 
    Reader(HANDLE csgo_process, uintptr_t client_module) {
      this->csgo_process = csgo_process;
      this->client_module = client_module;
    }

    virtual ReaderResult get_value() = 0;
  protected:
    HANDLE csgo_process;
    uintptr_t client_module;
};