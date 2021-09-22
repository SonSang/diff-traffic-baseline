#ifndef PROTO_RENDERER_HPP
#define PROTO_RENDERER_HPP

#include <fstream>
#include <map>
#include <zlib.h>

#include "proj_api.h"
#include "google/protobuf/text_format.h"

#include "gl_include.hpp"
#include "surface.hpp"
#include "log_config.hpp"
#include "drawable_road_net.pb.h"
#include "road_network.pb.h"
#include "road.hpp"
#include "location.hpp"
#include "zip_file_manager.hpp"

namespace city_sight {

class RoadClass {
private:
   vector<string> class_names_;

public:
   // Style parameters.
   float h0, s0, v0;
   float h1, s1, v1;
   csSurface surface;
   string class_name;

   RoadClass() {
      class_names_ = {"secondary",
                      "primary",
                      "arterial",
                      "arterial_ramp",
                      "highway ramp",
                      "highway"};
   }

   static vector<string> get_class_names() {
      RoadClass dummy_class;
      return dummy_class.class_names_;
   }

   void drawLayer0() {
      if (surface.myGeometry.numVertices == 0)
         return;

      surface.material.color.setHSV(h0, s0, v0);

      glLineWidth(4);
      surface.draw();
   }

   void drawLayer1() {
      if (surface.myGeometry.numVertices == 0)
         return;

      surface.material.color.setHSV(h1, s1, v1);

      glLineWidth(2);
      surface.draw();
   }
};

class ProtoRenderer : public csDrawable {
public:
   // TODO This is not generic... Should be 'proto' renderer.
   std::map<string, RoadClass> road_classes;

   // TODO Temporary
   vector<Road> road_database;

   SumoRoadNetworkMessage message;
   RoadNetworkMessage database;

   ~ProtoRenderer() {
      LOGE("ProtoRenderer Destroyed.\n");
   }


   void init() {
      LOGE("ProtoRenderer Init.\n");

      // These are used to store the text of the proto during the hacky #include
      // loading.
      string road_net_proto;
      string road_database_proto;

      // Reads the protobuf file.
      int size_read;
      char* file_contents =
      ZipFileManager::GetInstance()->ReadFile("../assets/road_net.pb", size_read);
      LOGI("Opened the file.  The files size was %i.", size_read);

      message.ParseFromArray(file_contents, size_read);

      LOGI("Parsed proto.");

      for (auto tuple : message.tuples()) {
         RoadClass road_class;
         road_class.h0 = tuple.road_class().h0();
         road_class.s0 = tuple.road_class().s0();
         road_class.v0 = tuple.road_class().v0();

         road_class.h1 = tuple.road_class().h1();
         road_class.s1 = tuple.road_class().s1();
         road_class.v1 = tuple.road_class().v1();

         std::string road_class_name = tuple.road_class().road_class();
         road_class.class_name = road_class_name;

         SurfaceMessage surface_message = tuple.road_class().surface();

         csSurface::CreateFromProto(surface_message,
                                    &road_class.surface);

         road_classes[road_class_name] = road_class;

         road_classes[road_class_name].surface.init();
      }

      // TODO This should be stored in the proto and read.
      // Add network specific offset to the Location manager.
      double offset[] = {-672139.48,-3972908.10};
      Location::GetInstance()->ClearOffset();
      Location::GetInstance()->AddLocalCoordOffset(offset[0], offset[1]);
   }

   void draw(float _t, float _dt) {
      road_classes["secondary"].drawLayer0();
      road_classes["primary"].drawLayer0();
      road_classes["arterial"].drawLayer0();
      road_classes["arterial ramp"].drawLayer0();
      road_classes["highway ramp"].drawLayer0();

      road_classes["secondary"].drawLayer1();
      road_classes["primary"].drawLayer1();
      road_classes["arterial ramp"].drawLayer1();
      road_classes["highway ramp"].drawLayer1();
      road_classes["arterial"].drawLayer1();


      road_classes["highway"].drawLayer0();
      road_classes["highway"].drawLayer1();
   }

   void translate(Vector3 _vec) {
   }
};

}  // namespace city_sight

#endif
