#ifndef SHADERS_HPP
#define SHADERS_HPP

#include <string>
#include <cstring>
#include <iostream>

#include "gl_include.hpp"
#include "log_config.hpp"
#include "vector3.hpp"
#include "vector4.hpp"
#include "matrix4.hpp"
#include "check_gl_error.hpp"

using std::string;

namespace city_sight {

class csShaders {
private:
   int vertexShaderID;
   int fragShaderID;

public:
   // TODO Make these private.
   int gpuProgramID;
   bool active;
   bool useTex;

   csShaders() {
      active = false;
      useTex = false;
   }

   string vertexShaderSRC =
   R"(
      uniform mat4 transform;

		attribute vec2 textureCoord;
		attribute vec3 position;

		varying vec2 texcoord;

		void main()
		{
			gl_Position = transform * (vec4(position, 1));

			texcoord = textureCoord;
		};)";

   string fragShaderSRC =
   R"(
      uniform vec4 color;
		uniform sampler2D texture;
		uniform float texAmount;

		varying vec2 texcoord;

		void main()
		{
			gl_FragColor = texture2D(texture, texcoord);
		};)";

   string vertexShaderNoTexSRC =
   R"(
		attribute vec3 position;

      uniform mat4 transform;

		void main()
		{
		   gl_Position = transform * (vec4(position, 1));
		};)";

   string fragShaderNoTexSRC =
   R"(
      precision mediump float;
      uniform vec4 color;
		void main()
		{
			gl_FragColor = color;
		})";

   void enable()
   {
      glUseProgram(gpuProgramID);
      checkGlError("glUseProgram");
   }

   void disable()
   {
      glUseProgram(0);
   }

   void setUniform(string name, float val)
   {
      int id = glGetUniformLocation(gpuProgramID, name.c_str());
      checkGlError("glGetUniformLocation");
      glUniform1f(id, val);
      checkGlError("glGetUniform1");
   }

   void setUniform(string name, Vector3 val)
   {
      int id = glGetUniformLocation(gpuProgramID, name.c_str());
      checkGlError("glGetUniformLocation");
      glUniform3f(id, val.x, val.y, val.z);
      checkGlError("glGetUniform3f");
   }

   void setUniform(string name, Vector4 val)
   {
      int id = glGetUniformLocation(gpuProgramID, name.c_str());
      checkGlError("glGetUniformLocation");
      glUniform4f(id, val.x, val.y, val.z, val.w);
      checkGlError("glGetUniform4");
   }

   void setUniform(string name, const Matrix4& val)
   {
      int id = glGetUniformLocation(gpuProgramID, name.c_str());
      checkGlError("glGetUniformLocatiaon");
      glUniformMatrix4fv(id, 1, GL_FALSE, (float*) &val);
      checkGlError("glUniformMatrix4fv");
   }

   void init()
   {
      active = true;

      vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
      checkGlError("glCreateShaderVert");
      fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
      checkGlError("glCreateShaderFrag");

      string vertexSRC;
      string fragSRC;
      if (useTex)
      {
         vertexSRC = vertexShaderSRC;
         fragSRC = fragShaderSRC;
      }
      else
      {
         vertexSRC = vertexShaderNoTexSRC;
         fragSRC = fragShaderNoTexSRC;
      }

      const GLchar* vertex_source[1];
      vertex_source[0] = vertexSRC.c_str();
      GLint vertex_lengths[1];
      vertex_lengths[0] = strlen(vertexSRC.c_str());
      glShaderSource(vertexShaderID, 1, vertex_source, NULL);
      checkGlError("glShaderSource");

      glCompileShader(vertexShaderID);
      checkGlError("glCompileShader");

      int status;
      glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &status);
      if (status == 0)
         LOGE("Vertex shader did not compile.\n");
      else
         LOGI("Vertex shader compiled.\n");

       const GLchar* fragment_source[1];
       fragment_source[0] = fragSRC.c_str();
       GLint fragment_lengths[1];
       fragment_lengths[0] = strlen(fragSRC.c_str());
       glShaderSource(fragShaderID, 1, fragment_source, NULL);
       checkGlError("glShaderSource");

       glCompileShader(fragShaderID);
       checkGlError("glCompileShader");
       glGetShaderiv(fragShaderID, GL_COMPILE_STATUS, &status);
       if (status == 0)
          LOGE("Frag shader did not compile.\n");
       else
          LOGI("Frag shader compiled.\n");

      gpuProgramID = glCreateProgram();
      checkGlError("glCreateProgram");
      glAttachShader(gpuProgramID, vertexShaderID);
      checkGlError("glAttachShader");
      glAttachShader(gpuProgramID, fragShaderID);
      checkGlError("glAttachShader");

      glLinkProgram(gpuProgramID);
      checkGlError("glLinkProgram");

      glGetProgramiv(gpuProgramID, GL_LINK_STATUS, &status);
      if (status == 0)
         std::cerr << "Program did not link.\n";
      else
         std::cerr << "Program linked.\n";
   }
};

}  // namespace city_sight

#endif
