#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "gl_include.hpp"
#include "surface.hpp"
#include "log_config.hpp"

namespace city_sight {

class Triangle : public csDrawable {
public:
   GLuint gProgram;
   GLuint gvPositionHandle;
   csSurface surface;

   void init() {
      surface.myGeometry.addVertex(Vector3(0.0f,
                                           1.0f,
                                           0.0f));
      surface.myGeometry.addVertex(Vector3(1.0f,
                                           0.0f,
                                           0.0f));
      surface.myGeometry.addVertex(Vector3(0.0f,
                                           0.0f,
                                           0.0f));
      surface.myGeometry.addTri();
      surface.init();

      LOGI("Created triangle geometry.");
   }

   void draw(float _t, float _dt) {
      surface.draw();
   }

   void translate(Vector3 _vec)
   {
   }
};

}  // namespace city_sight

#endif
