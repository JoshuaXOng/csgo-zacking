#pragma once
#include "../memory-utils/memory-utils.hpp"
#include "../reader.hpp"

class EntityListReader : Reader {
  public:
    EntityListReader(HANDLE csgo_process, uintptr_t client_module) 
    : Reader(csgo_process, client_module) {}

    ReaderResult get_value() {
      uintptr_t head_address = follow_pointer_chain(this->csgo_process, this->client_module + 0x4DD347C, {});
      DWORD head_value;
      ReadProcessMemory(csgo_process, (BYTE*) head_address, &head_value, sizeof(DWORD), 0);
      return { head_address, head_value };
    }

    ReaderResult get_ith_entity(int i) {
      uintptr_t entity_address = follow_pointer_chain(this->csgo_process, this->client_module + 0x4DD347C + 0x10 * i, {});
      DWORD entity_value;
      ReadProcessMemory(csgo_process, (BYTE*) entity_address, &entity_value, sizeof(DWORD), 0);
      return { entity_address, entity_value };
    }
};