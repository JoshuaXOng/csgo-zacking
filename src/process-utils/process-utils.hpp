#pragma once
#include <windows.h>
#include <TlHelp32.h>
#include <vector>

DWORD get_process_id(const wchar_t* process_name) {
  DWORD process_id = 0; 

  HANDLE processes_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
  if (processes_snapshot == INVALID_HANDLE_VALUE) {
    CloseHandle(processes_snapshot);
    return process_id;
  }

  PROCESSENTRY32 process;
  process.dwSize = sizeof(process);
  if (Process32First(processes_snapshot, &process)) {
    do {
      if (!_wcsicmp(process.szExeFile, process_name)) {
        process_id = process.th32ProcessID;
        break;
      }
    } while (Process32Next(processes_snapshot, &process));
  }
  
  CloseHandle(processes_snapshot);
  return process_id;
}

uintptr_t get_module_base_address(DWORD process_id, const wchar_t* module_name) {
  uintptr_t module_base_address = 0;

  HANDLE processes_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, process_id);
  if (processes_snapshot == INVALID_HANDLE_VALUE) {
    CloseHandle(processes_snapshot);
    return module_base_address;
  }

  MODULEENTRY32 module;
  module.dwSize = sizeof(module);
  if (Module32First(processes_snapshot, &module)) {
    do {
      if (!_wcsicmp(module.szModule, module_name)) {
        module_base_address = (uintptr_t) module.modBaseAddr;
        break;
      }
    } while (Module32Next(processes_snapshot, &module));
  }

  CloseHandle(processes_snapshot);
  return module_base_address;
}

uintptr_t follow_mallocd_chain(HANDLE process, uintptr_t base_address, std::vector<unsigned int> offsets) {
  uintptr_t address = base_address;
  for (unsigned int i = 0; i < offsets.size(); ++i) {
    ReadProcessMemory(process, (BYTE*) address, &address, sizeof(address), 0);
    address += offsets[i];
  }
  return address;
}