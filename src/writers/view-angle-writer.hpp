#pragma once
#include "iostream"
#include "../types.hpp"
#include "../memory-utils/memory-utils.hpp"
#include "../writer.hpp"

class ViewAngleWriter : public Writer {
  public:
    ViewAngleWriter(HANDLE csgo_process, uintptr_t client_module, uintptr_t engine_module) 
    : Writer(csgo_process, client_module, engine_module) {}

    void set_value(DWORD* view_vector) {
      WriteProcessMemory(this->csgo_process, (BYTE*) follow_pointer_chain(this->csgo_process, this->engine_module + 0x58CFC4, { 0x4D90 }), reinterpret_cast<Vec3*>(view_vector), sizeof(Vec3), 0);
    }
};