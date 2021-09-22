#ifndef VECTOR2_HPP
#define VECTOR2_HPP

namespace city_sight {

class Vector2 {
public:
   float x;
   float y;

   Vector2(){}

   Vector2(float _x, float _y) {
      x = _x;
      y = _y;
   }

};

}  // namespace city_sight

#endif
