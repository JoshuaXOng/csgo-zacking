#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cstdint>
#include <Windows.h>
#include <chrono>
#include <thread>
#include "./process-utils/process-utils.hpp"
#include "./memory-utils/memory-utils.hpp"
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
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    uintptr_t health_address = follow_pointer_chain(process, module + 0xDB75DC, { 0x100 });
    std::ostringstream printing_health_address;
    printing_health_address << "0x" << std::setfill('0') << std::setw(8) << std::hex << health_address;
    std::cout << "At" << " " << printing_health_address.str() << ": " << std::endl;

    BOOL isReadSuccess = ReadProcessMemory(process, (BYTE*) health_address, &container, sizeof(DWORD), 0);
    if (!isReadSuccess) {
      std::cout << "Bad memory read occured." << std::endl;
      continue;
    }

    std::cout << "The value is: " << container << std::endl;
  }

  return EXIT_SUCCESS;
};

