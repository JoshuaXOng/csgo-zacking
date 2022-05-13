#pragma once
#include <winuser.h>
#include "../types.hpp"
#include "../memory-utils/memory-utils.hpp"
#include "../reader.hpp"

class WindowDimReader : public Reader {
  public:
    WindowDimReader(HANDLE csgo_process, uintptr_t client_module, uintptr_t engine_module) 
    : Reader(csgo_process, client_module, engine_module) {
      this->window_handle = FindWindowA(NULL, "Counter-Strike: Global Offensive - Direct3D 9");
      if (!this->window_handle)
        throw ReaderException("Could not find the CSGO window.");
    }

    ReaderResult get_value() {
      return {};
    }

    Vec2 get_value_as_matrix() {   
      LPRECT bounding_coords;
      bool is_sucessful = GetClientRect(this->window_handle, bounding_coords);
      if (!is_sucessful)
        return {};

      return {
        (float) bounding_coords->right - (float) bounding_coords->left,
        (float) bounding_coords->bottom - (float) bounding_coords->top
      };
    }
  private:
    HWND window_handle;
};