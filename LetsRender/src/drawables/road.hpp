#ifndef ROAD_HPP
#define ROAD_HPP

#include <string>

#include "drawable.hpp"
#include "surface.hpp"
#include "vector2.hpp"

namespace city_sight {

class Road : public csDrawable {
public:
   // The type of road as described by the osm-via-sumo data.
   std::string road_type;

   // The class of the road as assigned by the renderer.
   std::string road_class;

   // The number of lanes.
   int lane_count;

   // The total road length.
   float length;

   // The points comprising the road.
   vector<Vector2> shape;

   // The surface for rendering.
   csSurface road;

   void init() {
   }

   virtual void translate(Vector3 _trans) {
   }

   void draw(float _dt, float _t) {
   }
};

} // namespace city_sight

#endif
