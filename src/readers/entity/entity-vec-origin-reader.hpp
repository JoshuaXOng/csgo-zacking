#pragma once
#include "../../memory-utils/memory-utils.hpp"
#include "../../reader.hpp"

struct Vec3 {
  float x;
  float y;
  float z;
};

class EntityVecOriginReader : Reader {
  public:
    EntityVecOriginReader(HANDLE csgo_process, uintptr_t client_module, uintptr_t entity_address) 
    : Reader(csgo_process, client_module) {
      this->entity_address = entity_address;
    }

    ReaderResult get_value() {
      uintptr_t vec_origin_address = follow_pointer_chain(this->csgo_process, entity_address, { 0x138 });
      DWORD vec_origin_value;
      ReadProcessMemory(csgo_process, (BYTE*) vec_origin_address, &vec_origin_value, sizeof(DWORD), 0);
      return { vec_origin_address, vec_origin_value };
    }

    Vec3 get_value_as_3d_vector() {
      uintptr_t vec_origin_address = follow_pointer_chain(this->csgo_process, entity_address, { 0x138 });
      Vec3 vec_origin_value;
      ReadProcessMemory(csgo_process, (BYTE*) vec_origin_address, &vec_origin_value, sizeof(Vec3), 0);
      return vec_origin_value;
    }
    private:
      uintptr_t entity_address;
};