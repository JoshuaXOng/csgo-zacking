#pragma once
#include "../memory-utils/memory-utils.hpp"
#include "../reader.hpp"

class EntityListReader : public Reader {
  public:
    EntityListReader(HANDLE csgo_process, uintptr_t client_module, uintptr_t engine_module) 
    : Reader(csgo_process, client_module, engine_module) {}

    ReaderResult get_value() {
      uintptr_t head_address = follow_pointer_chain(this->csgo_process, this->client_module + 0x4DD346C, {});
      DWORD head_value;
      ReadProcessMemory(csgo_process, (BYTE*) head_address, &head_value, sizeof(DWORD), 0);
      return { head_address, head_value };
    }

    ReaderResult get_ith_entity(int i) {
      uintptr_t entity_address = follow_pointer_chain(this->csgo_process, this->client_module + 0x4DD346C + 0x10 * i, {});
      DWORD entity_value;
      ReadProcessMemory(csgo_process, (BYTE*) entity_address, &entity_value, sizeof(DWORD), 0);
      return { entity_address, entity_value };
    }
};