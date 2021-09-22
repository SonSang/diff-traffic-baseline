#ifndef ROAD_CLASS_HPP
#define ROAD_CLASS_HPP

#include "surface.hpp"
#include "global_controls.hpp"
#include "camera.hpp"

namespace city_sight {

class csRoadClass
{
public:
   csSurface mySurf;
   int lanes;
   string roadclass;
   int points = 0;

   // Style parameters.
   float visibility;
   float width;
   float h0, s0, v0;
   float h1, s1, v1;

   // TODO move class specification here.

   float light0 = 0.1f;
   //    float sat0 = 0.9f;
   float sat0 = 0.0f;

   //    float light1 = 0.9f;
   //    float sat1 = 0.7f;
   float light1 = 0.75f;
   float sat1 = 0.0f;

   static string buildClass(string level, int lanes, float speedlimit)
   {
      string roadclass;

      int levelNum = atoi(level.c_str());

      if (levelNum > 2)
      {
         roadclass = "secondary";
      }
      else if (levelNum > 1)
      {
         roadclass = "primary";
      }
      else if (levelNum > 0)
      {
         roadclass = "arterial";
      }
      else
      {
         roadclass = "highway";
      }

      if (speedlimit > 10)
      {
         roadclass = "arterial";
      }
      if (speedlimit > 18)
      {
         roadclass = "highway";
      }



      if (roadclass == "arterial" && lanes == 1)
      {
         roadclass = "arterial ramp";
      }

      if (roadclass == "highway" && lanes == 1)
      {
         roadclass = "highway ramp";
      }

      return roadclass;
   }

   void setStyle()
   {
      float scaling = 1.0;

      {
         setHSV0(120, 0, light0);
         setHSV1(51, 0.1f, light1);

         width = 2 * scaling;

         visibility = 0;
      }
      if (roadclass == "primary")
      {
         setHSV0(130, sat0, light0);
         setHSV1(51, 0.333f * sat1, light1);

         width = 5 * scaling;

         visibility = 1;
      }
      if (roadclass == "arterial")
      {
         setHSV0(140, sat0, light0);
         setHSV1(51, 0.333f * sat1, light1);

         width = 8 * scaling;

         visibility = 1;
      }
      if (roadclass == "arterial ramp")
      {
         setHSV0(140, sat0, light0);
         setHSV1(51, 0.333f * sat1, light1);

         width = 5 * scaling;

         visibility = 0;
      }
      if (roadclass == "highway")
      {
         setHSV0(0, sat0, light0);
         setHSV1(51, sat1, light1);

         width = 10 * scaling;

         visibility = 1;
      }
      if (roadclass == "highway ramp")
      {
         setHSV0(150, sat0, light0);
         setHSV1(51, sat1, light1);

         width = 5 * scaling;

         visibility = 0;
      }
   }

   void setHSV0(float H, float S, float V)
   {
      h0 = H;
      s0 = S;
      v0 = V;

      // Default to a saturation map.
      h1 = h0;
      s1 = 0.1f;
      v1 = V;
   }

   void setHSV1(float H, float S, float V)
   {
      h1 = H;
      s1 = S;
      v1 = V;
   }

   void drawLayer0()
   {
      float size = width;

      mySurf.material.color.setHSV(h0, s0, v0);

      float whole;
      if (csGlobalControls::getInstance()->scaleRoads)
         whole = (1.0f  +  (1.0f - csCamera::getInstance()->get_zoom_factor())*size);
      else
         whole = size;

      // 1 is totally visible.
      float visVal = 1 - (std::min(csCamera::getInstance()->get_zoom_factor() * 2, (float)1) * (1 - visibility));
      mySurf.material.color.A = visVal;

      mySurf.material.color.A = csGlobalControls::getInstance()->roadAlpha;

      if (visVal < 0.05)
         return;

      glLineWidth(whole);
      mySurf.draw();


      // Draw 'joint points'
      //      glPointSize(whole * 0.5f); // TODO Point size not in ES
      mySurf.drawPoints();

   }

   void drawLayer1()
   {
      float size = width;

      mySurf.material.color.setHSV(h1, s1, v1);

      float whole = 1.0f + (1.0f - csCamera::getInstance()->get_zoom_factor()) * size;

      float inner;
      if (csGlobalControls::getInstance()->scaleRoads)
         inner = (whole / 2.0f);
      else
         inner = size / 2.0f;

      // 1 is totally visible.
      float visVal = 1
                     - (std::min(csCamera::getInstance()->get_zoom_factor() * 2, 1.0f)
                        * (1 - visibility));
      mySurf.material.color.A = visVal;

      mySurf.material.color.A = csGlobalControls::getInstance()->roadAlpha;

      if (visVal < 0.05)
         return;

      glLineWidth(inner);
      mySurf.draw();

      // Draw 'joint points'
      //glPointSize(inner * 0.5f); // TODO Point size not in ES
      mySurf.drawPoints();
   }
};

}  // namespace city_sight

#endif
