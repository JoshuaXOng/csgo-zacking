#pragma once
#include <Windows.h>

class Entity {
  public:
    Entity(void* entity_pointer) {
      this->entity_pointer = reinterpret_cast<unsigned char*>(entity_pointer);
    } 

    int get_health() {
      return this->entity_pointer[0x100];
    }

    bool get_is_dormant() {
      return this->entity_pointer[0xED];
    }
  private:
    unsigned char* entity_pointer;
};

class EntityList {
  public:
    Entity entities[64];
};