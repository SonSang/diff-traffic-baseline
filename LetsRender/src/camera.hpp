#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <cstdlib>
#include <cassert>

#include "vector2.hpp"
#include "vector3.hpp"
#include "global_controls.hpp"
#include "matrix4.hpp"
#include "log_config.hpp"
#include "location.hpp"

namespace city_sight {

class csCamera {
private:
   static csCamera* instance;

   Vector3 position;
   Vector3 focusCenter;
   Vector3 up;
   float zoomFactor;

   Matrix4 projection;
   Matrix4 view;
   float fovy;
   float aspect;

public:
   csCamera() {}

   static void Delete() {
      if (instance != NULL) {
         delete instance;
         instance = NULL;
      }
   }

   void set_zoom_factor(float zoom) {
      zoomFactor = zoom;
   }

   float get_zoom_factor() {
      return zoomFactor;
   }

   void set_position(Vector3 pos) {
      position = pos;
   }

   void  set_focus_center(Vector3 pos) {
      focusCenter = pos;
   }

   void Translate(float x, float y, float z) {
      set_position(Vector3(position.x + x,
                           position.y + y,
                           position.z + z));

      set_focus_center(Vector3(position.x + x,
                               position.y + y,
                               0.0f));

      view = Matrix4::LookAt(position, focusCenter, up);
   }

   // TODO Remove getInstance().  Keep this function.
   static csCamera* GetInstance()  {
      return getInstance();
   }

   static csCamera* getInstance()  {
      if (instance == NULL) {
         instance = new csCamera();
         instance->position = {0, 0, -5000};
         instance->focusCenter = {0, 0, 0};
         instance->up = Vector3(0, 1, 0);

         instance->zoomFactor = 1.0f;
      }

      return instance;
   }

   void InitializeView() {
      bool perspective = true;

      position = {0, 0, 10};
      focusCenter = {0, 0, -1};
      up = Vector3(0, 1, 0);

      if (perspective) {
         position = {0, 0, -10000};
         focusCenter = {0, 0, 0};
         up = Vector3(0, 1, 0);
      }
   }

   void setProj()
   {
      float width = csGlobalControls::getInstance()->width;
      float height = csGlobalControls::getInstance()->height;

      aspect = width / height;

      bool perspective = true;

      // Set up projection
      projection = Matrix4::Identity();

      if (perspective) {

         fovy = (float)((kPi) / 4.0f) * zoomFactor;

         projection = Matrix4::CreatePerspectiveFieldOfView(fovy,
                                                            aspect,
                                                            100.0f,
                                                            25000.0f);
      } else {
         projection = Matrix4::CreateOrthographicFieldOfView(-100,
                                                             100,
                                                             100,
                                                             -100,
                                                             9000,
                                                             11000);
      }
   }

   void setView()
   {
      view = Matrix4::LookAt(position, focusCenter, up);
   }

   Matrix4 getProjectionView() {
      return view * projection;
   }

   void CenterOnCurrentPosition() {
      double center[2];
      center[0] = Location::GetInstance()->GetOffsetCenterX();
      center[1] = Location::GetInstance()->GetOffsetCenterY();

      csCamera::getInstance()->set_position(Vector3(center[0],
                                                    center[1],
                                                    -1000));

      csCamera::getInstance()->set_focus_center(Vector3(center[0],
                                                        center[1],
                                                        0.0f));
      csCamera::getInstance()->setView();

   }

   void CenterOnRoute(Vector2 center, float x_length, float y_length) {
      // Creates space around the route.
      y_length *= 1.2;
      x_length *= 1.2;

      // Calculates needed height for y-direction.
      float y_height = (y_length / 2.0) / tan(fovy * 0.5);

      float x_height = (x_length / 2.0) / tan((fovy * 0.5 * aspect));

      // TODO Factors and offsets for Sioux Falls
      //      float height = std::max(y_height, x_height);
      float height = std::max(y_height, x_height) / 1.5;

      std::cout << height << " is the height\n";

      // csCamera::getInstance()->set_position(Vector3(center.x - 1300,
      //                                               center.y + 600,
      //                                               -height));

      // csCamera::getInstance()->set_focus_center(Vector3(center.x - 1300,
      //                                                   center.y + 600,
      //                                                   0.0f));

      csCamera::getInstance()->set_position(Vector3(center.x,
                                                    center.y,
                                                    -height));

      csCamera::getInstance()->set_focus_center(Vector3(center.x,
                                                        center.y,
                                                        0.0f));

      csCamera::getInstance()->setView();
   }
};

}  // namespace city_sight

#endif
