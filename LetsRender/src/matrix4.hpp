#ifndef MATRIX4_HPP
#define MATRIX4_HPP

#include <cassert>
#include <iostream>
#include "vector4.hpp"

namespace city_sight {

const double kPi = 3.14159265;

class Matrix4 {
public:
   float vals[16];

   Matrix4() {
      *this = Identity();
   }

   Matrix4(float 	m00, float 	m01, float 	m02, float 	m03,
           float 	m10, float 	m11, float 	m12, float 	m13,
           float 	m20, float 	m21, float 	m22, float 	m23,
           float 	m30, float 	m31, float 	m32, float 	m33) {

      vals[0] = m00;
      vals[1] = m01;
      vals[2] = m02;
      vals[3] = m03;
      vals[4] = m10;
      vals[5] = m11;
      vals[6] = m12;
      vals[7] = m13;
      vals[8] = m20;
      vals[9] = m21;
      vals[10] = m22;
      vals[11] = m23;
      vals[12] = m30;
      vals[13] = m31;
      vals[14] = m32;
      vals[15] = m33;
   }

   Matrix4 operator*(const Matrix4& right) {
      return Matrix4(vals[0] * right.vals[0] + vals[1] * right.vals[4]
                     + vals[2] * right.vals[8] + vals[3] * right.vals[12],
                     vals[0] * right.vals[1] + vals[1] * right.vals[5]
                     + vals[2] * right.vals[9] + vals[3] * right.vals[13],
                     vals[0] * right.vals[2] + vals[1] * right.vals[6]
                     + vals[2] * right.vals[10] + vals[3] * right.vals[14],
                     vals[0] * right.vals[3] + vals[1] * right.vals[7]
                     + vals[2] * right.vals[11] + vals[3] * right.vals[15],
                     vals[4] * right.vals[0] + vals[5] * right.vals[4]
                     + vals[6] * right.vals[8] + vals[7] * right.vals[12],
                     vals[4] * right.vals[1] + vals[5] * right.vals[5]
                     + vals[6] * right.vals[9] + vals[7] * right.vals[13],
                     vals[4] * right.vals[2] + vals[5] * right.vals[6]
                     + vals[6] * right.vals[10] + vals[7] * right.vals[14],
                     vals[4] * right.vals[3] + vals[5] * right.vals[7]
                     + vals[6] * right.vals[11] + vals[7] * right.vals[15],
                     vals[8] * right.vals[0] + vals[9] * right.vals[4]
                     + vals[10] * right.vals[8] + vals[11] * right.vals[12],
                     vals[8] * right.vals[1] + vals[9] * right.vals[5]
                     + vals[10] * right.vals[9] + vals[11] * right.vals[13],
                     vals[8] * right.vals[2] + vals[9] * right.vals[6]
                     + vals[10] * right.vals[10] + vals[11] * right.vals[14],
                     vals[8] * right.vals[3] + vals[9] * right.vals[7]
                     + vals[10] * right.vals[11] + vals[11] * right.vals[15],
                     vals[12] * right.vals[0] + vals[13] * right.vals[4]
                     + vals[14] * right.vals[8] + vals[15] * right.vals[12],
                     vals[12] * right.vals[1] + vals[13] * right.vals[5]
                     + vals[14] * right.vals[9] + vals[15] * right.vals[13],
                     vals[12] * right.vals[2] + vals[13] * right.vals[6]
                     + vals[14] * right.vals[10] + vals[15] * right.vals[14],
                     vals[12] * right.vals[3] + vals[13] * right.vals[7]
                     + vals[14] * right.vals[11] + vals[15] * right.vals[15]);
      }

   Vector4 operator*(const Vector4& vec) {
      return Vector4(vals[0] * vec.x + vals[1] * vec.y + vals[2] * vec.z + vals[3] * vec.w,
                     vals[4] * vec.x + vals[5] * vec.y + vals[6] * vec.z + vals[7] * vec.w,
                     vals[8] * vec.x + vals[9] * vec.y + vals[10] * vec.z + vals[11] * vec.w,
                     vals[12] * vec.x + vals[13] * vec.y + vals[14] * vec.z + vals[15] * vec.w);
   }

   static Matrix4 Identity() {
      return Matrix4(1, 0, 0, 0,
                     0, 1, 0, 0,
                     0, 0, 1, 0,
                     0, 0, 0, 1);
   }

   Matrix4 Transpose() {
      return Matrix4(vals[0], vals[4], vals[8], vals[12],
                     vals[1], vals[5], vals[9], vals[13],
                     vals[2], vals[6], vals[10], vals[14],
                     vals[3], vals[7], vals[11], vals[15]);
   }

   static Matrix4 CreatePerspectiveFieldOfView(float 	fovy,
                                               float 	aspect,
                                               float 	zNear,
                                               float 	zFar) {
      if (fovy <= 0 || fovy > kPi)
         assert(0);
      if (aspect <= 0)
         assert(0);
      if (zNear <= 0)
         assert(0);
      if (zFar <= 0)
         assert(0);
      if (zNear >= zFar)
         assert(0);

      float top = zNear * (float) tan(0.5f * fovy);
      float bottom = -top;
      float right = bottom * aspect;
      float left = top * aspect;

      float x = (2.0f * zNear) / (right - left);
      float y = (2.0f * zNear) / (top - bottom);
      float a = (right + left) / (right - left);
      float b = (top + bottom) / (top - bottom);
      float c = -(zFar + zNear) / (zFar - zNear);
      float d = -(2.0f * zFar * zNear) / (zFar - zNear);

      return Matrix4(x, 0, 0, 0,
                     0, y, 0, 0,
                     a, b, c, -1,
                     0, 0, d, 0);
   }

   static Matrix4 CreateOrthographicFieldOfView(float right,
                                                float left,
                                                float top,
                                                float bottom,
                                                float near,
                                                float far) {


      return Matrix4((2.0f / (right - left)), 0, 0, -((right + left)/(right - left)),
                     0, (2.0f / (top - bottom)), 0, -((top + bottom)/(top - bottom)),
                     0, 0, (2.0f / (far - near)), -((far + near)/(far - near)),
                     0, 0, 0, 1);

   }


   static Matrix4 CreateTranslation(Vector3 trans) {
      return Matrix4(1, 0, 0, 0,
                     0, 1, 0, 0,
                     0, 0, 1, 0,
                     trans.x, trans.y, trans.z, 1);
   }

   static Matrix4 LookAt(Vector3 position,
                         Vector3 focusCenter,
                         Vector3 up) {
      Vector3 z = Vector3::Normalize(position - focusCenter);
      Vector3 x = Vector3::Normalize(Vector3::Cross(up, z));
      Vector3 y = Vector3::Normalize(Vector3::Cross(z, x));

      Matrix4 rot = Matrix4(x.x, y.x, z.x, 0.0f,
                            x.y, y.y, z.y, 0.0f,
                            x.z, y.z, z.z, 0.0f,
                            0.0f, 0.0f, 0.0f, 1.0f);

      Matrix4 trans = Matrix4::CreateTranslation(-position);

      return trans * rot;
   }

   void print() {
      for (int i = 0; i < 16; i++) {
         std::cout << vals[i] << " ";
         if ((i + 1) % 4 == 0)
            std::cout << std::endl;
      }
   }
};

}  // namespace city_sight

#endif
