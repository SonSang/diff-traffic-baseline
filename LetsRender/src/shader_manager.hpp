#ifndef SHADER_MANAGER_HPP
#define SHADER_MANAGER_HPP

#include <vector>

#include "shaders.hpp"

using std::vector;

namespace city_sight {

class csShaderManager {
public:
   static vector<csShaders> shaders;

   static void load()
   {
      shaders.clear();

      csShaders texShader;
      texShader.useTex = true;
      texShader.init();
      shaders.push_back(texShader);

      csShaders colorShader;
      colorShader.useTex = false;
      colorShader.init();
      shaders.push_back(colorShader);
   }

   static csShaders getTexShader()
   {
      return shaders[0];
   }

   static csShaders getColorShader()
   {
      return shaders[1];
   }
};

}  // namespace city_sight

#endif
