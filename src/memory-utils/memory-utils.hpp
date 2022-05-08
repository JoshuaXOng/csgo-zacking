#pragma once
#include <windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cstdint>
#include <chrono>
#include <thread>

uintptr_t follow_pointer_chain(HANDLE process, uintptr_t base_address, std::vector<unsigned int> offsets) {
  uintptr_t address = base_address;
  for (unsigned int i = 0; i < offsets.size(); ++i) {
    ReadProcessMemory(process, (BYTE*) address, &address, 4, 0);
    address += offsets[i];
  }
  return address;
}