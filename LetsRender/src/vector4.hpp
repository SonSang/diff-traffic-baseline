#ifndef VECTOR4_HPP
#define VECTOR4_HPP

namespace city_sight {

class Vector4 {
public:
   float x;
   float y;
   float z;
   float w;

   Vector4(){}

   Vector4(float _x, float _y, float _z, float _w) {
      x = _x;
      y = _y;
      z = _z;
      w = _w;
   }
};

}  // namespace city_sight

#endif

