#pragma once
#include "../memory-utils/memory-utils.hpp"
#include "../reader.hpp"

class HealthReader : public Reader {
  public:
    HealthReader(HANDLE csgo_process, uintptr_t client_module, uintptr_t engine_module) 
    : Reader(csgo_process, client_module, engine_module) {}

    ReaderResult get_value() {
      uintptr_t health_address = follow_pointer_chain(this->csgo_process, this->client_module + 0xDB75DC, { 0x100 });
      DWORD health_value;
      ReadProcessMemory(csgo_process, (BYTE*) health_address, &health_value, sizeof(DWORD), 0);
      return { health_address, health_value };
    }
};