#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "color.hpp"
#include "texture.hpp"
#include "shaders.hpp"
#include "shader_manager.hpp"

namespace city_sight {

class csMaterial {
public:
   csColor color;
   csTexture texture;
   csShaders shader;

   csMaterial()
   {
      shader = csShaderManager::getColorShader();
   }

   void initTexture(string _filename)
   {
      texture.active = true;
      texture.filename = _filename;
      shader = csShaderManager::getTexShader();
      texture._init();
   }

   void initTexture(Magick::Image image)
   {
      texture.active = true;
      shader = csShaderManager::getTexShader();
      texture._initFromImage(image);
   }
};

}  // namespace city_sight

#endif
