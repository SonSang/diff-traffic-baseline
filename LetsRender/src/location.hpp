#ifndef LOCATION_HPP
#define LOCATION_HPP

#include "proj_api.h"
#include "log_config.hpp"

namespace city_sight {

// This static class holds the current location for the system. It also holds
// offset information used
class Location {
private:
   double x;
   double y;
   double z;

   double offset_x;
   double offset_y;
   Location() {
      x = 0;
      y = 0;
      z = 0;

      offset_x = 0;
      offset_y = 0;
   }
   static Location* instance;

public:
   static Location* GetInstance() {
      if (instance == NULL) {
         instance = new Location();
      }

      return instance;
   }

   static void Delete() {
      if (instance != NULL) {
         delete instance;
         instance = NULL;
      }
   }


   void SetLocation(double lng, double lat) {
      double center[2];
      center[0] = lng;
      center[1] = lat;

      double deg_to_rad = M_PI / 180.0;

      // Project location using road network parameters.
      // TODO These configurations should be read out of the sumo .nod.xml file.
      projPJ pj_merc, pj_latlong;
      pj_merc = pj_init_plus("+proj=utm +zone=17 +ellps=WGS84 +datum=WGS84 +units=m +no_defs");
      pj_latlong = pj_init_plus("+proj=latlong +ellps=WGS84 +datum=WGS84");

      center[0] *= deg_to_rad;
      center[1] *= deg_to_rad;

      pj_transform(pj_latlong,
                   pj_merc,
                   1,
                   1,
                   &center[0],
                   &center[1],
                   NULL);

      x = center[0];
      y = center[1];
   }

   void AddLocalCoordOffset(double offset_x_, double offset_y_) {
      offset_x += offset_x_;
      offset_y += offset_y_;
   }

   void ClearOffset() {
      offset_x = 0;
      offset_y = 0;
   }

   double GetLocalCoordXOffset() {
      return offset_x;
   }

   double GetLocalCoordYOffset() {
      return offset_y;
   }

   double GetOffsetCenterX() {
      return x + offset_x;
   }

   double GetOffsetCenterY() {
      return y + offset_y;
   }

};

} // namespace city_sight

#endif
