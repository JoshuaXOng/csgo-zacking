#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <d3d9.h>
#include <wingdi.h>
#include <iostream>
#include <sstream>
#include <Windows.h>
#include <math.h>
#include "../process-utils/process-utils.hpp"
#include "../reader.hpp"
#include "../readers/entity-list-reader.hpp"
#include "../readers/view-angle-reader.hpp"
#include "../readers/window-dim-reader.hpp"
#include "../readers/window-location-reader.hpp"
#include "../readers/view-matrix-reader.hpp"
#include "../readers/entity/entity-vec-origin-reader.hpp"
#include "../writers/view-angle-writer.hpp"

#define RGB(r,g,b) ((COLORREF)(((BYTE)(r)|((WORD)((BYTE)(g))<<8))|(((DWORD)(BYTE)(b))<<16)))

bool make_window_overlay(SDL_Window* sdl_window, COLORREF ignore_color) {
  SDL_SysWMinfo window_info;
  SDL_VERSION(&window_info.version); 
  SDL_GetWindowWMInfo(sdl_window, &window_info);
  
  HWND window = window_info.info.win.window;
  SetWindowLong(window, GWL_EXSTYLE, GetWindowLong(window, GWL_EXSTYLE) | WS_EX_LAYERED);

  return SetLayeredWindowAttributes(window, ignore_color, 0, LWA_COLORKEY);
}

class OverlayZacker {
  public: 
    std::vector<Vec2*> drawables = {};

    OverlayZacker(HANDLE csgo_process, uintptr_t client_module, uintptr_t engine_module) {
      this->window_dim_reader.reset(new WindowDimReader(csgo_process, client_module, engine_module));
      this->window_location_reader.reset(new WindowLocationReader(csgo_process, client_module, engine_module));

      auto dimensions = this->window_dim_reader->get_value_as_matrix();
      auto location = this->window_location_reader->get_value_as_matrix();
      this->overlay = SDL_CreateWindow("Overlay Zacker", location.x + 1, location.y + 25 + 1, dimensions.x, dimensions.y, SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_BORDERLESS); // SDL_WINDOW_BORDERLESS
      make_window_overlay(this->overlay, RGB(255, 0, 255));
      this->renderer = SDL_CreateRenderer(this->overlay, -1, SDL_RENDERER_ACCELERATED);
    }
      
    ~OverlayZacker() {
      SDL_DestroyWindow(this->overlay);
      SDL_Quit();
    }

    void draw_overlay() {
      fit_overlay();

      SDL_SetRenderDrawColor(this->renderer, 255, 0, 255, 255);
      SDL_RenderClear(this->renderer);

      for (auto drawable : this->drawables) {
        draw_square_at(*drawable);
      }

      SDL_RenderPresent(this->renderer);
    }

    void draw_square_at(Vec2 coords) {
      SDL_Rect rect1 = { (int) coords.x, (int) coords.y, 20, 20 };
      SDL_SetRenderDrawColor(this->renderer, 0, 0, 255, 255);
      SDL_RenderFillRect(this->renderer, &rect1);
    }

    void fit_overlay() {
      auto location = this->window_location_reader->get_value_as_matrix();
      SDL_SetWindowPosition(this->overlay, location.x + 1, location.y + 25 + 1);
    }
  private:
    std::unique_ptr<WindowDimReader> window_dim_reader;
    std::unique_ptr<WindowLocationReader> window_location_reader;

    SDL_Window* overlay;
    SDL_Renderer* renderer;
};
