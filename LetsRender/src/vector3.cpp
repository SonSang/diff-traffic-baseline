#include "vector3.hpp"

namespace city_sight {

Vector3 operator-(const Vector3& vec) {
   return Vector3(-vec.x, -vec.y, -vec.z);
}

}  // namespace city_sight
