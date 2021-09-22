#ifndef CABSPOTTER_HPP
#define CABSPOTTER_HPP

#include <map>
#include <limits>
#include <fstream>
#include <sstream>
#include <iterator>

#include <proj_api.h>
#include <google/protobuf/text_format.h>
#include <libxml++/libxml++.h>

#include "stoch_graph/stoch_graph.hpp"
#include "stoch_graph/local_frame.hpp"

#include "drawable.hpp"
#include "sumo_road_class.hpp"
#include "surface.hpp"
#include "camera.hpp"
#include "drawable_road_net.pb.h"

using std::map;

namespace city_sight {

struct Point {
   double x;
   double y;

   Point (double _x, double _y) {
      x = _x;
      y = _y;
   }
};

class CabSpotter : public csDrawable {
private:
   string filename_ = "";
   vector<Point> points;

public:
   void set_filename(string filename) {
      filename_ = filename;
   }

   string get_filename() {
      return filename_;
   }

   void LoadFile() {
      std::ifstream fin;
      fin.open(filename_);

      string line;
      while(getline(fin, line)) {
         std::istringstream line_stream(line);
         std::istream_iterator<string> eos;
         std::istream_iterator<string> line_iterator(line_stream);

         string lat =  *line_iterator;
         line_iterator++;

         string lng = *line_iterator;
         line_iterator++;

         double x = atof(lng.c_str());
         double y = atof(lat.c_str());

         points.push_back(Point(x, y));
      }
   }

   void ProjectPoints() {
      if (LocalFrame::Exists()) {
         std::cout << "Projecting points.\n";
         LocalFrame* instance = LocalFrame::GetInstance();
         for (int i = 0; i < points.size(); i++) {
            double x, y;
            instance->LongLatToLocal(points[i].x, points[i].y, &x, &y);
            points[i].x = x;
            points[i].y = y;
         }
      }
      else
         std::cout << "No local frame define.  Points were not projected.\n";
   }

   void init()
   {
      std::cout << "Called init.\n";
      LoadFile();
      //      ProjectPoints();

      for (int i = 0; i < points.size(); i++) {
         Vector3 point;
         point = Vector3(points[i].x, points[i].y, 0.0f);
         surface.myGeometry.addPoint(point);
      }

      surface.init();
   }

   void draw(float _t, float _dt)
   {
      glPointSize(4);
      surface.material.color.setHSV(1, 1, 1);
      surface.material.color.A = 0.2;
      surface.draw();
   }

   void translate(Vector3 _vec)
   {
   }

private:
   csSurface surface;
};

}  // namespace city_sight

#endif
