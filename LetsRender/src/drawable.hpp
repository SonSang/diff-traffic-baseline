#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include "vector3.hpp"

namespace city_sight {

// Define things.
class csDrawable {
public:
   virtual void draw(float _dt, float _t) = 0;
   virtual void init() = 0;
   virtual void translate(Vector3 _trans) = 0;
};

}  // namespace city_sight

#endif
