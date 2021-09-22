#ifndef SURFACE_HPP
#define SURFACE_HPP

#include "vector2.hpp"
#include "vector4.hpp"
#include "geometry.hpp"
#include "paramval.hpp"
#include "material.hpp"
#include "camera.hpp"

#include "drawable_road_net.pb.h"
#include "log_config.hpp"
#include "check_gl_error.hpp"

namespace city_sight {

class csSurface {
public:
   // TODO Move to private.
   // TODO Remove deprecated parameters.
   csGeometry myGeometry;
   csParamVal myMap;
   csMaterial material;
   int regionSize;
   float param;
   float negator;
   uint vertVBO;
   uint indxVBO;
   uint array_buffer_size_;

   csSurface() {
      regionSize = 0;
      param = 0;
      negator = -1.0f;
      array_buffer_size_ = 0;
   }

   void update() {
      glBindBuffer(GL_ARRAY_BUFFER, vertVBO);
      glBufferSubData(GL_ARRAY_BUFFER,
                      0,
                      array_buffer_size_,
                      &myGeometry.vertices[0]);
      checkGlError("glBufferSubData");
      LOGI("Modified geometry. %f\n", myGeometry.vertices[0].position.x);
   }

   void init()   {
      // TODO(Wilkie) This should happen in geometry.
      glGenBuffers(1, &vertVBO);
      checkGlError("glGenBuffers");
      glBindBuffer(GL_ARRAY_BUFFER, vertVBO);
      checkGlError("glBindBuffer");

      array_buffer_size_ = (myGeometry.numVertices * 5 * sizeof(float));
      glBufferData(GL_ARRAY_BUFFER,
                   (myGeometry.numVertices * 5 * sizeof(float)),
                   &myGeometry.vertices[0],
                   GL_DYNAMIC_DRAW);
      checkGlError("glBufferData");

      glGenBuffers(1, &indxVBO);
      checkGlError("glGenBuffers");
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indxVBO);
      checkGlError("glbindBuffers");
      glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                   (myGeometry.numIndices * sizeof(uint)),
                   &myGeometry.indices[0],
                   GL_DYNAMIC_DRAW);
      checkGlError("glBufferData");

      // LOGI("Surface init with %d vertices", myGeometry.numVertices);
      // LOGI("              and %d indices", myGeometry.numIndices);
   }

   void destroy() {
      glDeleteBuffers(1, &vertVBO);
      checkGlError("glDeleteBuffers");
      glDeleteBuffers(1, &indxVBO);
      checkGlError("glDeleteBuffers");

      LOGI("Destroyed a surface.\n");

      myGeometry.Clear();
   }

   // A drawing function that will only draw points for debugging purposes.
   void drawPoints()
   {
      if (material.shader.active)
      {
         material.shader.enable();
         material.shader.setUniform("color",
                                    Vector4(material.color.R,
                                            material.color.G,
                                            material.color.B,
                                            material.color.A));

         // TODO
         // if (material.texture.active == true)
         // {
         //    material.shader.setUniform("texture", material.texture.textureID);
         // }
      }

      glBindBuffer(GL_ARRAY_BUFFER, this->vertVBO);
      checkGlError("glBindBuffer");

      int pLoc = glGetAttribLocation(this->material.shader.gpuProgramID,
                                     "position");
      checkGlError("glGetAttribLocation");

      glVertexAttribPointer(pLoc,
                            3,
                            GL_FLOAT,
                            GL_FALSE,
                            5 * sizeof(float),
                            (const GLvoid*) (2 * sizeof(float)));
      checkGlError("glVertexAttribPointer");
      glEnableVertexAttribArray(pLoc);
      checkGlError("glEnableVertexAttribArray");

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indxVBO);
      checkGlError("glBindBuffer");
      glDrawElements(GL_POINTS,
                     (int)myGeometry.numIndices,
                     GL_UNSIGNED_INT,
                     0);
      checkGlError("glDrawElements");

      glDisableVertexAttribArray(pLoc);
      checkGlError("glDisableVertexAttribArray");
   }

   void draw() {
      if (material.shader.active) {
         material.shader.enable();
         material.shader.setUniform("color",
                                    Vector4(material.color.R,
                                            material.color.G,
                                            material.color.B,
                                            material.color.A));

         // TODO textures not working yet. Need image magick or substitute.
         if (material.texture.active == true) {
            material.shader.setUniform("texture", material.texture.textureID);
            glBindTexture(GL_TEXTURE_2D, material.texture.textureID);
         }
      }

      material.shader.setUniform("transform",
                                 csCamera::getInstance()->getProjectionView());

      glBindBuffer(GL_ARRAY_BUFFER, this->vertVBO);
      checkGlError("glBindBuffer");

      int pLoc = glGetAttribLocation(this->material.shader.gpuProgramID,
                                     "position");
      checkGlError("glGetAttribLocation");

      glVertexAttribPointer(pLoc,
                            3,
                            GL_FLOAT,
                            GL_FALSE,
                            5 * sizeof(float),
                            (const GLvoid*)(2 * sizeof(float)));
      checkGlError("glVertexAttribPointer");

      int texLoc = glGetAttribLocation(this->material.shader.gpuProgramID,
                                       "textureCoord");
      checkGlError("glGetAttribLocation");

      glVertexAttribPointer(texLoc,
                            2,
                            GL_FLOAT,
                            false,
                            5 * sizeof(float),
                            0);
      checkGlError("glVertexAttribPointer");

      glEnableVertexAttribArray(pLoc);
      checkGlError("glEnableVertexAttribArraypLoc");
      glEnableVertexAttribArray(texLoc);
      checkGlError("glEnableVertexAttribArraytexLoc");


      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indxVBO);
      checkGlError("glBindBuffer");

      if (myGeometry.drawMode == csGeometry::mode::Tris) {
         glDrawElements(GL_TRIANGLES,
                        (int)myGeometry.numIndices,
                        GL_UNSIGNED_INT,
                        0);
         checkGlError("glDrawElements");
      }
      else if (myGeometry.drawMode == csGeometry::mode::Points) {
         glDrawElements(GL_POINTS,
                        (int)myGeometry.numIndices,
                        GL_UNSIGNED_INT,
                        0);
         checkGlError("glDrawElements");
      }
      else if (myGeometry.drawMode == csGeometry::mode::Lines) {
         glDrawElements(GL_LINES,
                        (int)myGeometry.numIndices,
                        GL_UNSIGNED_INT,
                        0);
         checkGlError("glDrawElements");
      }
      else if (myGeometry.drawMode == csGeometry::mode::Quads) {
         glDrawElements(GL_QUADS,
                        (int)myGeometry.numIndices,
                        GL_UNSIGNED_INT,
                        0);
         checkGlError("glDrawElements");
      }

      glDisableVertexAttribArray(pLoc);
      glDisableVertexAttribArray(texLoc);
   }

   void test()
   {
      std::cout << "surf here.\n";
   }

   static void CreateFromProto(const SurfaceMessage& message,
                               csSurface* toReturn,
                               double x_offset = 0,
                               double y_offset = 0) {
      LOGI("Create From proto\n");
      toReturn->myGeometry.numVertices = message.geometry().numvertices();
      toReturn->myGeometry.numIndices = message.geometry().numindices();

      // TODO not general.
      toReturn->myGeometry.drawMode = city_sight::csGeometry::mode::Lines;

      toReturn->myGeometry.vertices.clear();
      for (uint i = 0; i < toReturn->myGeometry.numVertices; i++) {
         ptVertex vertex;

         vertex.position.x = message.geometry().vertices(i).x() + x_offset;
         vertex.position.y = message.geometry().vertices(i).y() + y_offset;
         vertex.position.z = message.geometry().vertices(i).z();

         toReturn->myGeometry.vertices.push_back(vertex);
      }

      toReturn->myGeometry.indices.clear();
      for (uint i = 0; i < toReturn->myGeometry.numIndices; i++) {
         toReturn->myGeometry.indices.push_back(message.geometry().indices(i));
      }
   }
};

}  // namespace city_sight

#endif
