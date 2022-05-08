#pragma once
#include "../memory-utils/memory-utils.hpp"
#include "../reader.hpp"

class ViewAngleReader : public Reader {
  public:
    ViewAngleReader(HANDLE csgo_process, uintptr_t client_module, uintptr_t engine_module) 
    : Reader(csgo_process, client_module, engine_module) {}

    ReaderResult get_value() {
      uintptr_t view_angle_address = follow_pointer_chain(this->csgo_process, this->engine_module + 0x58CFC4, { 0x4D90 });
      DWORD view_angle_value;
      ReadProcessMemory(csgo_process, (BYTE*) view_angle_address, &view_angle_value, sizeof(DWORD), 0);
      return { view_angle_address, view_angle_value };
    }

    Vec3 get_value_as_3d_vector() {
      uintptr_t view_angle_address = follow_pointer_chain(this->csgo_process, this->engine_module + 0x58CFC4, { 0x4D90 });
      Vec3 view_angle_value;
      ReadProcessMemory(csgo_process, (BYTE*) view_angle_address, &view_angle_value, sizeof(Vec3), 0);
      return view_angle_value;
    }
};