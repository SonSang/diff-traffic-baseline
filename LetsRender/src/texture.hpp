#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <Magick++.h>

#include "gl_include.hpp"

namespace city_sight {

class csTexture {
public:
   uint textureID;
   bool active = false;
   string filename = "hexellence.png";
   bool initialized = false;

   int width = 0;
   int height = 0;

   void _initFromImage(Magick::Image image)
   {
      if (initialized == false)
      {
         active = true;

         glGenTextures(1, &textureID);
         glBindTexture(GL_TEXTURE_2D, textureID);

         width = image.columns();
         height = image.rows();

         InitImageInOpenGL(image);

         initialized = true;
      }
   }

   void _init()
   {
      if (initialized == false)
      {
         active = true;

         glGenTextures(1, &textureID);
         glBindTexture(GL_TEXTURE_2D, textureID);

         Magick::Image image;
         image.read(filename);

         width = image.columns();
         height = image.rows();

         InitImageInOpenGL(image);

         initialized = true;
      }
   }

   void InitImageInOpenGL(Magick::Image& image)
   {
      glTexParameteri(GL_TEXTURE_2D,
                     GL_TEXTURE_MIN_FILTER,
                     GL_LINEAR);

      glTexParameteri(GL_TEXTURE_2D,
                     GL_TEXTURE_MAG_FILTER,
                     GL_LINEAR);

      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

      Magick::Blob blob;
      image.write(&blob, "RGBA");

      glTexImage2D(GL_TEXTURE_2D,
                   0,
                   GL_RGBA,
                   image.columns(),
                   image.rows(),
                   0,
                   GL_RGBA,
                   GL_UNSIGNED_BYTE,
                   blob.data());

      std::cout << "Texture initialized with " << image.columns() << " "
                << image.rows() << std::endl;
   }
};

}  // namespace city_sight

#endif
