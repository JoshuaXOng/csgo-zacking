#pragma once
#include "../../memory-utils/memory-utils.hpp"
#include "../../reader.hpp"

class EntityHealthReader : public Reader {
  public:
    EntityHealthReader(HANDLE csgo_process, uintptr_t client_module, uintptr_t engine_module, uintptr_t entity_address) 
    : Reader(csgo_process, client_module, engine_module) {
      this->entity_address = entity_address;
    }

    ReaderResult get_value() {
      uintptr_t health_address = follow_pointer_chain(this->csgo_process, entity_address, { 0x100 });
      DWORD health_value;
      ReadProcessMemory(csgo_process, (BYTE*) health_address, &health_value, sizeof(DWORD), 0);
      return { health_address, health_value };
    }
    private:
      uintptr_t entity_address;
};