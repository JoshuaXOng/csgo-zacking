#pragma once
#include <winuser.h>
#include <memory>
#include "../types.hpp"
#include "../memory-utils/memory-utils.hpp"
#include "../reader.hpp"

#define CSGO_WINDOW_NAME "Counter-Strike: Global Offensive - Direct3D 9"

class WindowLocationReader : public Reader {
  public:
    WindowLocationReader(HANDLE csgo_process, uintptr_t client_module, uintptr_t engine_module) 
    : Reader(csgo_process, client_module, engine_module) {
      this->window_handle = FindWindowA(NULL, CSGO_WINDOW_NAME);
      if (!this->window_handle)
        throw ReaderException("Could not find the CSGO window.");
    }

    ReaderResult get_value() {
      return {};
    }

    Vec2 get_value_as_matrix() {   
      RECT origin;
      bool is_sucessful = GetWindowRect(this->window_handle, &origin);
      if (!is_sucessful)
        return {};

      return {
        (float) origin.left,
        (float) origin.top
      };
    }
  private:
    HWND window_handle;
};