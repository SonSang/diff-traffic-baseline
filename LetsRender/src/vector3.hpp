#ifndef VECTOR3_HPP
#define VECTOR3_HPP

#include <cmath>

namespace city_sight {

class Vector3 {
public:
   float x;
   float y;
   float z;

   Vector3(){}

   Vector3(float array[3]) {
      x = array[0];
      y = array[1];
      z = array[2];
   }

   Vector3(float _x, float _y, float _z) {
      x = _x;
      y = _y;
      z = _z;
   }

   Vector3(const Vector3& copy) {
      x = copy.x;
      y = copy.y;
      z = copy.z;
   }

   float Length() {
      return sqrt(pow(x,2) + pow(y,2) + pow(z,2));
   }

   static Vector3 Normalize(Vector3 input) {
      float scale = 1.0f / input.Length();
      input.x *= scale;
      input.y *= scale;
      input.z *= scale;

      return input;
   }

   static Vector3 Cross (Vector3 left, Vector3 right) {
      Vector3 result;

      result = Vector3(left.y * right.z - left.z * right.y,
                       left.z * right.x - left.x * right.z,
                       left.x * right.y - left.y * right.x);

      return result;
   }

   Vector3 operator-(const Vector3& right) {
      Vector3 left = *this;
      left.x -= right.x;
      left.y -= right.y;
      left.z -= right.z;
      return left;
   }
};

Vector3 operator-(const Vector3& vec);

}  // namespace city_sight

#endif

