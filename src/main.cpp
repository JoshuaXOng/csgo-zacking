#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cstdint>
#include <Windows.h>
#include <chrono>
#include <thread>
#include "../dependencies/hazedumper-master/csgo.hpp"
#include "./process-utils/process-utils.hpp"
#include "./memory-utils/memory-utils.hpp"
#include "./readers/health-reader.hpp"

struct Module {
  HANDLE process;
  uintptr_t module;
};

Module getCsgoClientModule() {
  DWORD process_id = get_process_id(L"csgo.exe");
  HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, false, process_id);
  uintptr_t module = get_module_base_address(process_id, L"client.dll");
  return { process, module };
}

int wWinMain(HINSTANCE h_instance, HINSTANCE h_orev_instance, LPWSTR p_cmd_line, int n_cmd_show) {
  auto [process, module] = getCsgoClientModule();
  if (process == NULL || module == 0) {
    std::cout << "Could not get CSGO client module" << std::endl;
    return EXIT_FAILURE;
  }

  DWORD value_container;
  while (true) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    HealthReader* health_reader = new HealthReader(process, module);
    std::ostringstream printing_health_address;
    printing_health_address << "0x" << std::setfill('0') << std::setw(8) << std::hex << health_reader->get_value().address;
    std::cout << "At" << " " << printing_health_address.str() << ": " << health_reader->get_value().value << std::endl;
  }

  return EXIT_SUCCESS;
};
