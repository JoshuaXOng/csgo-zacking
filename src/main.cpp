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
#include "./readers/entity-list-reader.hpp"
#include "./readers/entity/entity-health-reader.hpp"
#include "./readers/entity/entity-vec-origin-reader.hpp"

struct Module {
  HANDLE process;
  uintptr_t module;
};

Module get_csgo_client_module() {
  DWORD csgo_id = get_process_id(L"csgo.exe");
  HANDLE csgo = OpenProcess(PROCESS_ALL_ACCESS, false, csgo_id);
  uintptr_t client_dll = get_module_base_address(csgo_id, L"client.dll");
  return { csgo, client_dll };
}

int wWinMain(HINSTANCE h_instance, HINSTANCE h_orev_instance, LPWSTR p_cmd_line, int n_cmd_show) {
  auto [csgo, client_dll] = get_csgo_client_module();
  if (csgo == NULL || client_dll == 0) {
    std::cout << "Could not get CSGO client module" << std::endl;
    return EXIT_FAILURE;
  }

  HealthReader* health_reader = new HealthReader(csgo, client_dll);

  EntityListReader* entity_list_reader = new EntityListReader(csgo, client_dll);
  auto [idk_entity_address, idk_entity_value] = entity_list_reader->get_ith_entity(0);

  EntityHealthReader* idk_entity_health_reader = new EntityHealthReader(csgo, client_dll, idk_entity_address);
  EntityVecOriginReader* idk_entity_vec_origin_reader = new EntityVecOriginReader(csgo, client_dll, idk_entity_address);
  
  DWORD value_container;
  while (true) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    std::cout << "At" << " " << get_number_as_hex(health_reader->get_value().address) << ": " << health_reader->get_value().value << std::endl;

    std::cout << idk_entity_health_reader->get_value().value << std::endl;
    // std::cout << idk_entity_vec_origin_reader->get_value().value << std::endl;
    std::cout << idk_entity_vec_origin_reader->get_value_as_3d_vector().x << std::endl;
    std::cout << idk_entity_vec_origin_reader->get_value_as_3d_vector().y << std::endl;
    std::cout << idk_entity_vec_origin_reader->get_value_as_3d_vector().z << std::endl;
  };

  return EXIT_SUCCESS;
};
