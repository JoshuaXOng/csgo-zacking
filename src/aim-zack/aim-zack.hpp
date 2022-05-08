#pragma once
#include <Windows.h>
#include <math.h>
#include "../reader.hpp"
#include "../readers/entity-list-reader.hpp"
#include "../readers/view-angle-reader.hpp"
#include "../readers/entity/entity-vec-origin-reader.hpp"
#include "../writers/view-angle-writer.hpp"

#define PI 3.14159265

class AimZack {
  public: 
    AimZack(HANDLE csgo_process, uintptr_t client_module, uintptr_t engine_module) {
      this->csgo_process = csgo_process;
      this->client_module = client_module;
      this->engine_module = engine_module;

      this->entity_list_reader = new EntityListReader(csgo_process, client_module, engine_module);
    }

    void look_at_entity(int i) {
      auto [self_entity_address, _] = this->entity_list_reader->get_ith_entity(0);
      EntityVecOriginReader* self_entity_vo_reader = new EntityVecOriginReader(this->csgo_process, this->client_module, this->engine_module, self_entity_address);
      Vec3 self_vec_origin = self_entity_vo_reader->get_value_as_3d_vector();

      auto [ith_entity_address, __] = this->entity_list_reader->get_ith_entity(i);
      EntityVecOriginReader* ith_entity_vo_reader = new EntityVecOriginReader(this->csgo_process, this->client_module, this->engine_module, ith_entity_address);
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

      ViewAngleReader* var = new ViewAngleReader(this->csgo_process, this->client_module, this->engine_module);
      // std::cout << var->get_value_as_3d_vector().x << std::endl;
      // std::cout << var->get_value_as_3d_vector().y << std::endl;
      // std::cout << var->get_value_as_3d_vector().z << std::endl;
      free(var);

      ViewAngleWriter* self_view_angle_writer = new ViewAngleWriter(this->csgo_process, this->client_module, this->engine_module);
      self_view_angle_writer->set_value(reinterpret_cast<DWORD*>(&desired_view_vector));

      free(self_entity_vo_reader);
      free(ith_entity_vo_reader);
      free(self_view_angle_writer);
    }
  private:
    HANDLE csgo_process;
    uintptr_t client_module;
    uintptr_t engine_module;

    EntityListReader* entity_list_reader;
};
