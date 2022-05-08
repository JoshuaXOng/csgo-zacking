#include "../memory-utils/memory-utils.hpp"
#include "../reader.hpp"

class ShotsReader : Reader {
  public:
    ShotsReader(HANDLE csgo_process, uintptr_t client_module) 
    : Reader(csgo_process, client_module) {}

    ReaderResult get_value() {
      uintptr_t shots_address = follow_pointer_chain(this->csgo_process, this->client_module + 0xDB75DC, { 0x103E0 });
      DWORD shots_value;
      ReadProcessMemory(csgo_process, (BYTE*) shots_address, &shots_value, sizeof(DWORD), 0);
      return { shots_address, shots_value };
    }
};