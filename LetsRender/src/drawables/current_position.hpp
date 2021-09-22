#ifndef CURRENT_POSITION_HPP
#define CURRENT_POSITION_HPP

#include "gl_include.hpp"
#include "surface.hpp"
#include "log_config.hpp"

namespace city_sight {

class CurrentPosition : public csDrawable {
public:

   CurrentPosition() {
      x_pos_ = 0;
      y_pos_ = 0;
      size_ = 300;
      initted_ = false;
   }

   void DefineGeometry() {
      // Deletes old geometry.
      surface.myGeometry.Clear();

      Vector3 p0, p1, p2, p3;

      float width = 30;
      float length = 50;
      float length1 = length * 0.75;
      float length2 = length - length1;

      p0 = Vector3(x_pos_,
                   y_pos_,
                   0.0f);

      p1 = Vector3(x_pos_ + length1,
                   y_pos_,
                   0.0f);

      p2 = Vector3(x_pos_ - length2,
                   y_pos_ + (width * 0.5),
                   0.0f);

      p3 = Vector3(x_pos_ - length2,
                   y_pos_ - (width * 0.5),
                   0.0f);

      surface.myGeometry.addVertex(p0);
      surface.myGeometry.addVertex(p1);
      surface.myGeometry.addVertex(p2);
      surface.myGeometry.addVertex(p3);

      surface.myGeometry.addTri(0, 1, 2);
      surface.myGeometry.addTri(0, 3, 1);
      surface.myGeometry.addTri(0, 2, 3);

   }

   void SetPosition(float x, float y) {
      LOGI("SetPosition called on current_position\n");

      x_pos_ = x;
      y_pos_ = y;

      DefineGeometry();

      surface.update();
   }

   void init() {
      if (initted_) {
         surface.destroy();
      }

      initted_ = true;

      LOGI("x_pos here is %f", x_pos_);

      DefineGeometry();

      surface.init();
   }

   void draw(float _t, float _dt) {
      float x = city_sight::Location::GetInstance()->GetOffsetCenterX();
      float y = city_sight::Location::GetInstance()->GetOffsetCenterY();

      if (((std::abs(x - x_pos_) > 2) or (std::abs(y - y_pos_) > 2))
          and (initted_))
         SetPosition(x, y);

      surface.draw();
   }

   void translate(Vector3 _vec)
   {
   }

private:
   csSurface surface;
   float x_pos_;
   float y_pos_;
   float size_;
   bool initted_;
};

}  // namespace city_sight

#endif
