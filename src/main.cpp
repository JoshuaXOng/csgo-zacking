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

  HealthReader* health_reader = new HealthReader(csgo, client_dll, engine_dll);

  EntityListReader* entity_list_reader = new EntityListReader(csgo, client_dll, engine_dll);
  auto [idk_entity_address, idk_entity_value] = entity_list_reader->get_ith_entity(0);

  EntityHealthReader* idk_entity_health_reader = new EntityHealthReader(csgo, client_dll, engine_dll, idk_entity_address);
  EntityVecOriginReader* idk_entity_vec_origin_reader = new EntityVecOriginReader(csgo, client_dll, engine_dll, idk_entity_address);
  
  ViewAngleWriter* view_angle_writer = new ViewAngleWriter(csgo, client_dll, engine_dll);

  DWORD value_container;
  while (true) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    // std::cout << "At" << " " << get_number_as_hex(health_reader->get_value().address) << ": " << health_reader->get_value().value << std::endl;

    // std::cout << idk_entity_health_reader->get_value().value << std::endl;
    // std::cout << idk_entity_vec_origin_reader->get_value().value << std::endl;
    // std::cout << idk_entity_vec_origin_reader->get_value_as_3d_vector().x << std::endl;
    // std::cout << idk_entity_vec_origin_reader->get_value_as_3d_vector().y << std::endl;
    // std::cout << idk_entity_vec_origin_reader->get_value_as_3d_vector().z << std::endl;

    // Vec3 a;
    // ReadProcessMemory(csgo, (BYTE*) follow_pointer_chain(csgo, engine_dll + 0x58CFC4, { 0x4D90 }), &a, sizeof(Vec3), 0);
    // std::cout << a.x << std::endl;
    // std::cout << a.y << std::endl;
    // std::cout << a.z << std::endl;
    
    // Vec3 b = { (rand() % 176) - 90, (rand() % 360) - 180, 0 };
    // view_angle_writer->set_value(reinterpret_cast<DWORD*>(&b));
    // bool result = WriteProcessMemory(csgo, (BYTE*) follow_pointer_chain(csgo, engine_dll + 0x58CFC4, { 0x4D90 }), &b, sizeof(Vec3), 0);
    // std::cout << result << std::endl;
    AimZack* aim_zack = new AimZack(csgo, client_dll, engine_dll);
    aim_zack->look_at_entity(1);
  };

  return EXIT_SUCCESS;
};
