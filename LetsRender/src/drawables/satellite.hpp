#ifndef SATELLITE_HPP
#define SATELLITE_HPP

#include "billboard.hpp"

namespace city_sight {

class csSatelliteMap : public csDrawable
{
private:
   csBillboard map;

public:
   csBillboard& retrieve_image() {
      return map;
   }

   void init()
   {
      map.init();
   }

   void draw(float _t, float _dt)
   {
      map.draw();
   }

   void translate(Vector3 _vec)
   {
      return;
   }
};

}  // namespace city_sight

#endif
