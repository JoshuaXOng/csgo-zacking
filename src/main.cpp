#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <cstdint>
#include <Windows.h>
#include <memoryapi.h>
#include <chrono>
#include <thread>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include "../dependencies/hazedumper-master/csgo.hpp"
#include "./process-utils/process-utils.hpp"
#include "./memory-utils/memory-utils.hpp"
#include "./readers/health-reader.hpp"
#include "./readers/entity-list-reader.hpp"
#include "./readers/entity/entity-health-reader.hpp"
#include "./readers/entity/entity-vec-origin-reader.hpp"
#include "./readers/view-matrix-reader.hpp"
#include "./writers/view-angle-writer.hpp"
#include "./aim-zack/aim-zack.hpp"

struct Module {
  HANDLE process;
  uintptr_t client_module;
  uintptr_t engine_module;
};

Module get_csgo_client_and_engine_module() {
  DWORD csgo_id = get_process_id(L"csgo.exe");
  HANDLE csgo = OpenProcess(PROCESS_ALL_ACCESS, false, csgo_id);
  uintptr_t client_dll = get_module_base_address(csgo_id, L"client.dll");
  uintptr_t engine_dll = get_module_base_address(csgo_id, L"engine.dll");
  return { csgo, client_dll, engine_dll };
}

int wWinMain(HINSTANCE h_instance, HINSTANCE h_orev_instance, LPWSTR p_cmd_line, int n_cmd_show) {
  auto [csgo, client_dll, engine_dll] = get_csgo_client_and_engine_module();
  if (csgo == NULL || client_dll == 0 || engine_dll == 0) {
    std::cout << "Could not get CSGO client or engine module" << std::endl;
    return EXIT_FAILURE;
  }

  while (true) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    AimZack* aim_zack = new AimZack(csgo, client_dll, engine_dll);
    aim_zack->look_at_entity(1, AimZack::LAEType::geo);
  };

  return EXIT_SUCCESS;
};
