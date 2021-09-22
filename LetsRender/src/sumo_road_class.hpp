#ifndef SUMO_ROAD_CLASS_HPP
#define SUMO_ROAD_CLASS_HPP

#include "surface.hpp"
#include "global_controls.hpp"
#include "camera.hpp"

namespace city_sight {

class csSumoRoadClass
{
private:
   vector<string> class_names_ = {"secondary",
                                  "primary",
                                  "arterial",
                                  "arterial_ramp",
                                  "highway ramp",
                                  "highway"};
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

   float light0 = 0.0f;
   float sat0 = 1.0f;

   float light1 = 1.0f;
   float sat1 = 1.0f;

   static vector<string> get_class_names() {
      csSumoRoadClass dummy_class;
      return dummy_class.class_names_;
   }

   static string buildClass(string type)
   {
      string roadclass = "none";

      if ((type == "highway.residential")
          or
          (type == "highway.secondary")
          or
          (type == "highway.secondary_link")
          or
          (type == "highway.tertiary")
          or
          (type == "highway.unclassified")
          or
          (type == "highway.road")
          or
          (type == "highway.service")
          ) {
         roadclass = "secondary";
      }
      else if ((type == "highway.primary")
               or
               (type == "highway.primary_link")){
         roadclass = "primary";
      }
      else if ((type == "highway.trunk")) {
         roadclass = "arterial";
      }
      else if ((type == "highway.motorway")) {
         roadclass = "highway";
      }
      else if ((type == "highway.trunk_ramp")) {
         roadclass = "arterial ramp";
      }
      else if ((type == "highway.motorway_link")) {
         roadclass = "highway ramp";
      }

      return roadclass;
   }

   void setStyle()
   {
      float scaling = 1.0;

      // Defaults to secondary
      setHSV0(120, 0, light0);
      setHSV1(51, 0.1f, light1);

      width = 4 * scaling;

      visibility = 0;

      // TODO REMOVE FOR YELLOW ROADS
      float sat0 = 0;
      float sat1 = 0;

      float hue = 61;

      if (roadclass == "primary")
      {
         setHSV0(hue, sat0, light0);
         setHSV1(hue, sat1, light1);

         width = 5 * scaling;

         visibility = 1;
      }
      if (roadclass == "arterial")
      {
         setHSV0(hue, sat0, light0);
         setHSV1(hue, sat1, light1);

         width = 8 * scaling;

         visibility = 1;
      }
      if (roadclass == "arterial ramp")
      {
         setHSV0(hue, sat0, light0);
         setHSV1(hue, sat1, light1);

         width = 5 * scaling;

         visibility = 0;
      }
      if (roadclass == "highway")
      {
         setHSV0(hue, sat0, light0);
         setHSV1(hue, sat1, light1);

         width = 10 * scaling;

         visibility = 1;
      }
      if (roadclass == "highway ramp")
      {
         setHSV0(hue, sat0, light0);
         setHSV1(hue, sat1, light1);

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
      //      mySurf.material.color.A = visVal;

      mySurf.material.color.A = csGlobalControls::getInstance()->roadAlpha;

      // if (visVal < 0.05)
      //    return;

      glLineWidth(whole);
      glPointSize(whole - 1);
      mySurf.draw();

      // Draw 'joint points'
      // TODO Point size is not in ES.  Need new solution.
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
      //      mySurf.material.color.A = visVal;

      mySurf.material.color.A = csGlobalControls::getInstance()->roadAlpha;

      // if (visVal < 0.05)
      //    return;

      glPointSize(inner - 1);
      glLineWidth(inner);
      mySurf.draw();

      // Draw 'joint points'
      // TODO Point size is not in ES.  Need new solution.
      mySurf.drawPoints();
   }
};

}  // namespace city_sight

#endif
