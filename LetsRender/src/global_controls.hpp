#ifndef GLOBAL_CONTROLS_HPP
#define GLOBAL_CONTROLS_HPP

#include <cstdlib>

namespace city_sight {

class csGlobalControls  {
public:
   csGlobalControls() {
      showRegions = true;
      showRoads = true;
      showMap = true;
      showAlerts = false;
      scaleRoads = false;

      roadAlpha = 1.0f;
      alertScale = 1.0f;
   }

   static csGlobalControls* instance;

   static csGlobalControls* getInstance() {
      if (instance == NULL)
      {
         instance = new csGlobalControls();
      }

      return instance;
   }

   static void Delete() {
      if (instance != NULL) {
         delete instance;
         instance = NULL;
      }
   }

   // TODO Make private.
   bool showRegions;
   bool showRoads;
   bool showMap;
   bool showAlerts;
   bool scaleRoads;

   float roadAlpha;
   float alertScale;

   float width;
   float height;

   double projMinX;
   double projMinY;
};



}  // namespace city_sight

#endif
