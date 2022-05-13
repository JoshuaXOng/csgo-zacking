#pragma once
#include <Windows.h>
#include <math.h>
#include "../process-utils/process-utils.hpp"
#include "../reader.hpp"
#include "../readers/entity-list-reader.hpp"
#include "../readers/view-angle-reader.hpp"
#include "../readers/window-dim-reader.hpp"
#include "../readers/view-matrix-reader.hpp"
#include "../readers/entity/entity-vec-origin-reader.hpp"
#include "../writers/view-angle-writer.hpp"

#define PI 3.14159265

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

class AimZacker {
  public: 
    AimZacker(HANDLE csgo_process, uintptr_t client_module, uintptr_t engine_module) {
      this->csgo_process = csgo_process;
      this->client_module = client_module;
      this->engine_module = engine_module;

      this->window_dim_reader = new WindowDimReader(csgo_process, client_module, engine_module);

      this->entity_list_reader = new EntityListReader(csgo_process, client_module, engine_module);
      this->view_matrix_reader = new ViewMatrixReader(csgo_process, client_module, engine_module);

      auto [entity_address, _] = this->entity_list_reader->get_ith_entity(0);
      this->vec_origin_reader = new EntityVecOriginReader(this->csgo_process, this->client_module, this->engine_module, entity_address);
      this->view_angle_reader = new ViewAngleReader(this->csgo_process, this->client_module, this->engine_module);
      this->view_angle_writer = new ViewAngleWriter(this->csgo_process, this->client_module, this->engine_module);
    }

    ~AimZacker() {
      free(this->window_dim_reader);
      free(this->entity_list_reader);
      free(this->view_matrix_reader);
      free(this->vec_origin_reader);
      free(this->view_angle_reader);
      free(this->view_angle_writer);
    }

    enum LAEType { geo, engine };
    void look_at_entity(int i) {
      geo_look_at_entity(i);
    }

    bool world_to_screen(Vec3 world_position, Vec2& screen_position) {
      ViewMatrix view_matrix = this->view_matrix_reader->get_value_as_matrix();
      
      float x = view_matrix.elements[0] * world_position.x + view_matrix.elements[1] * world_position.y + view_matrix.elements[2] * world_position.z + view_matrix.elements[3];
      float y = view_matrix.elements[4] * world_position.x + view_matrix.elements[5] * world_position.y + view_matrix.elements[6] * world_position.z + view_matrix.elements[7];
      
      float w = view_matrix.elements[12] * world_position.x + view_matrix.elements[13] * world_position.y + view_matrix.elements[14] * world_position.z + view_matrix.elements[15];
      if (w < 0.01f)
        return false;

      x /= w; y /= w;
      auto window_width = this->window_dim_reader->get_value_as_matrix().x;
      auto window_height = this->window_dim_reader->get_value_as_matrix().y;
      screen_position = {
        (window_width / 2 * x) + (x + window_width / 2),
        -(window_height / 2 * y) + (y + window_height / 2)
      };
      return true;
    }

    Vec2 entity_to_screen(int i) {
      auto [ith_entity_address, _] = this->entity_list_reader->get_ith_entity(i);
      std::unique_ptr<EntityVecOriginReader> ith_entity_vo_reader(new EntityVecOriginReader(this->csgo_process, this->client_module, this->engine_module, ith_entity_address));
      Vec3 ith_vec_origin = ith_entity_vo_reader->get_value_as_3d_vector();

      Vec2 ith_screen_position;
      world_to_screen(ith_vec_origin, ith_screen_position);

      return ith_screen_position;
    }
  private:
    HANDLE csgo_process;
    uintptr_t client_module;
    uintptr_t engine_module;

    WindowDimReader* window_dim_reader;

    EntityListReader* entity_list_reader;
    ViewMatrixReader* view_matrix_reader;

    EntityVecOriginReader* vec_origin_reader;
    ViewAngleReader* view_angle_reader;
    ViewAngleWriter* view_angle_writer;

    void geo_look_at_entity(int i) {
      auto [ith_entity_address, _] = this->entity_list_reader->get_ith_entity(i);
      std::unique_ptr<EntityVecOriginReader> ith_entity_vo_reader(new EntityVecOriginReader(this->csgo_process, this->client_module, this->engine_module, ith_entity_address));

      Vec3 self_vec_origin = this->vec_origin_reader->get_value_as_3d_vector();
      Vec3 ith_vec_origin = ith_entity_vo_reader->get_value_as_3d_vector();

      auto x_delta = ith_vec_origin.x - self_vec_origin.x;
      auto y_delta = ith_vec_origin.y - self_vec_origin.y;
      auto z_delta = ith_vec_origin.z - self_vec_origin.z;

      Vec3 desired_view_vector; 
      if (x_delta >= 0 && y_delta >= 0) 
        desired_view_vector = { -atan(z_delta / y_delta) * 180 / (float) PI, 90 - (atan(x_delta / y_delta) * 180 / (float) PI), 0 };
      if (x_delta >= 0 && y_delta < 0) 
        desired_view_vector = { -atan(z_delta / y_delta) * 180 / (float) PI, (atan(y_delta / x_delta) * 180 / (float) PI), 0 };
      if (x_delta < 0 && y_delta >= 0) 
        desired_view_vector = { -atan(z_delta / y_delta) * 180 / (float) PI, -180 + (atan(y_delta / x_delta) * 180 / (float) PI), 0 };
      if (x_delta < 0 && y_delta < 0)
        desired_view_vector = { -atan(z_delta / y_delta) * 180 / (float) PI, -90 - (atan(x_delta / y_delta) * 180 / (float) PI), 0 };

      this->view_angle_writer->set_value(reinterpret_cast<DWORD*>(&desired_view_vector));
    }
};
