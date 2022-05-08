#pragma once
#include "../../memory-utils/memory-utils.hpp"
#include "../../reader.hpp"

class EntityIsDormantReader : Reader {
  public:
    EntityIsDormantReader(HANDLE csgo_process, uintptr_t client_module, uintptr_t engine_module, uintptr_t entity_address) 
    : Reader(csgo_process, client_module, engine_module) {
      this->entity_address = entity_address;
    }

    ReaderResult get_value() {
      uintptr_t is_dormant_address = follow_pointer_chain(this->csgo_process, entity_address, { 0xED });
      DWORD is_dormant_value;
      ReadProcessMemory(csgo_process, (BYTE*) is_dormant_address, &is_dormant_value, sizeof(DWORD), 0);
      return { is_dormant_address, is_dormant_value };
    }
    private:
      uintptr_t entity_address;
};