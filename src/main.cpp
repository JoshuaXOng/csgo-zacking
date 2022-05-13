#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <d3d9.h>
#include <wingdi.h>
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
#include "./zackers/aim-zacker.hpp"
#include "./zackers/overlay-zacker.hpp"

int wWinMain(HINSTANCE h_instance, HINSTANCE h_orev_instance, LPWSTR p_cmd_line, int n_cmd_show) {
  auto [csgo, client_dll, engine_dll] = get_csgo_client_and_engine_module();
  if (csgo == NULL || client_dll == 0 || engine_dll == 0) {
    std::cout << "Could not get CSGO, CSGO client and/or engine module" << "\n";
    return EXIT_FAILURE;
  }
 
  auto elr = new EntityListReader(csgo, client_dll, engine_dll);
  auto a = elr->get_ith_entity(2).address;
  auto evor = new EntityVecOriginReader(csgo, client_dll, engine_dll, a);

  AimZacker* aim_zacker = new AimZacker(csgo, client_dll, engine_dll);
  // OverlayZacker* overlay_zacker = new OverlayZacker(csgo, client_dll, engine_dll);
  while (true) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    auto aa = evor->get_value_as_3d_vector();
    std::cout << aa.x << "\n";
    std::cout << aa.y << "\n";

    Vec2 posi;
    aim_zacker->world_to_screen(aa, posi);
    // std::cout << posi.x << "\n";
    // std::cout << posi.y << "\n";

    // aim_zacker->look_at_entity(1);
  };

  // Vec2 drawable = { 300, 300 };
  // overlay_zacker->drawables.push_back(&drawable);

  // // std::cout << aim_zacker->entity_to_screen(1).x << "\n";

  // bool should_break;
  // SDL_Event event;
  // while(true) {
  //   while (SDL_PollEvent(&event) != 0) {
  //     if (event.type == SDL_QUIT) {
  //       should_break = true;
  //     }
  //   }
  //   if (should_break) break;

  //   // drawable = aim_zacker->entity_to_screen(1);
  //   aim_zacker->look_at_entity(3);
  //   overlay_zacker->draw_overlay();
  // }

  return EXIT_SUCCESS;
};
