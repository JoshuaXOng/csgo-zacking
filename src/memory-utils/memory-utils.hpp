#pragma once
#include <windows.h>
#include <memoryapi.h>
#include <errhandlingapi.h>
#include <TlHelp32.h>
#include <iostream>
#include <sstream>
#include <string>
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

std::string get_number_as_hex(uintptr_t number) {
  std::ostringstream hex_number;
  hex_number << "0x" << std::setfill('0') << std::setw(8) << std::hex << number;
  return hex_number.str();
}

void get_process_size(LPCVOID process_pointer, PMEMORY_BASIC_INFORMATION& process_info, DWORD& gps_error) {
  if (!VirtualQuery(process_pointer, process_info, sizeof(PMEMORY_BASIC_INFORMATION))) 
    GetLastError();
}