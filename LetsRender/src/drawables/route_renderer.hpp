#ifndef ROUTE_RENDERER_HPP
#define ROUTE_RENDERER_HPP

#include <fstream>
#include <map>
#include <zlib.h>
#include <limits>


#include "proj_api.h"
#include "google/protobuf/text_format.h"

#include "gl_include.hpp"
#include "surface.hpp"
#include "log_config.hpp"
#include "route.pb.h"
#include "road.hpp"
#include "location.hpp"
#include "zip_file_manager.hpp"


namespace city_sight {

class RouteRenderer : public csDrawable {
public:
   RouteRenderer() {
      array_loaded_ = false;
      initted_ = false;
   }

   ~RouteRenderer() {

   }

   void LoadFromArray(signed char* byte_array, int length) {
      route_proto_.ParseFromArray(byte_array, length);
      array_loaded_ = true;
   }

   void init() {
      if (array_loaded_) {
         initted_ = true;

         int num_vertices = 0;

         // Used for calculating the bounding box and center of the route.
         Vector2 center;
         center.x = 0;
         center.y = 0;

         float max_x, max_y, min_x, min_y;
         max_x = max_y = std::numeric_limits<float>::min();
         min_x = min_y = std::numeric_limits<float>::max();
         float x_length, y_length;

         for (auto path_element : route_proto_.path_element()) {
            const TrafficRouting::RoadMessage& road = path_element.road();

            for (int i = 0; i < road.geometry_size(); i++) {
               const TrafficRouting::PointMessage& point = road.geometry(i);

               Vector3 position;

               position.x = point.x();
               position.y = point.y();
               position.z = 0;

               // Used to calculate the bounding box dimensions.
               if (position.x > max_x)
                  max_x = position.x;
               if (position.y > max_y)
                  max_y = position.y;
               if (position.x < min_x)
                  min_x = position.x;
               if (position.y < min_y)
                  min_y = position.y;

               surface_.myGeometry.addVertex(position);

               num_vertices++;

               // Adds the vertices to define a line segment.
               if (num_vertices > 1) {
                  surface_.myGeometry.addLine(num_vertices - 2,
                                              num_vertices - 1);
               }
            }
         }

         surface_.init();
         LOGE("INIT ROUTE WITH %i VERTICES", num_vertices);

         // TODO Call this elsewhere.
         // Sets the camera to view whole route.
         center.x = ((max_x - min_x) * 0.5) + min_x;
         center.y = ((max_y - min_y) * 0.5) + min_y;

         x_length = max_x - min_x;
         y_length = max_y - min_y;

         csCamera::GetInstance()->CenterOnRoute(center, x_length, y_length);
      }
      else
         LOGE("Tried to init a route without data.\n");
   }

   void draw(float _t, float _dt) {
      if (initted_) {

         surface_.material.color.setHSV(200, 1, 1);
         glLineWidth(5);
         surface_.draw();

      } else if (array_loaded_) {
         init();
         draw(_t, _dt);
      }
   }

   void translate(Vector3 _vec) {
   }

private:
   TrafficRouting::Route route_proto_;
   bool array_loaded_;
   bool initted_;
   csSurface surface_;
};

}  // namespace city_sight

#endif
