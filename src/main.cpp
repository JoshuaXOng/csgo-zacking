#include <iostream>
#include <vector>
#include <cstdint>
#include <Windows.h>
#include <chrono>
#include <thread>
#include "./process-utils/process-utils.hpp"
#include "../dependencies/hazedumper-master/csgo.hpp"

int wWinMain(HINSTANCE h_instance, HINSTANCE h_orev_instance, LPWSTR p_cmd_line, int n_cmd_show) {
  DWORD process_id = get_process_id(L"csgo.exe");

  HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, false, process_id);
  if (process == NULL) {
    std::cout << "Could not open process." << std::endl;
    return EXIT_FAILURE;
  }

  uintptr_t module = get_module_base_address(process_id, L"client.dll");
  if (module == 0) {
    std::cout << "Could not get module." << std::endl;
    return EXIT_FAILURE;
  }

  DWORD container;
  while (true) {
    std::cout << "START" << std::endl;
    int count = 0;

    for (int i = 0; i < 10000000; ++i) {
      BOOL isReadSuccess = ReadProcessMemory(process, (BYTE*) module + i*4, &container, sizeof(DWORD), 0);
      if (!isReadSuccess) {
        std::cout << "Bad memory read occured." << std::endl;
        continue;
      }

      if (container == 1337) {
        std::cout << container << std::endl;
        count++;
      }
    }
    
    std::cout << "END" << std::endl;
    std::cout << count << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
  }

  return EXIT_SUCCESS;
};

