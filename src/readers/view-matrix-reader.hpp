#pragma once
#include "../memory-utils/memory-utils.hpp"
#include "../reader.hpp"

struct ViewMatrix {
  float elements[16];
};

class ViewMatrixReader : public Reader {
  public:
    ViewMatrixReader(HANDLE csgo_process, uintptr_t client_module, uintptr_t engine_module) 
    : Reader(csgo_process, client_module, engine_module) {}

    ReaderResult get_value() {
      uintptr_t view_matrix_address = follow_pointer_chain(this->csgo_process, this->client_module + 0x4DC4D84, { });
      DWORD view_matrix_value;
      ReadProcessMemory(csgo_process, (BYTE*) view_matrix_address, &view_matrix_value, sizeof(DWORD), 0);
      return { view_matrix_address, view_matrix_value };
    }

    ViewMatrix get_value_as_matrix() {
      uintptr_t view_matrix_address = follow_pointer_chain(this->csgo_process, this->client_module + 0x4DC4D84, { });
      ViewMatrix view_matrix_value;
      ReadProcessMemory(csgo_process, (BYTE*) view_matrix_address, &view_matrix_value, sizeof(ViewMatrix), 0);
      return view_matrix_value;
    }
};