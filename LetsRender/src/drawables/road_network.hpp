#ifndef ROAD_NETWORK_HPP
#define ROAD_NETWORK_HPP

#include <map>

using std::map;

namespace city_sight {

// TODO These are dummy classes.
class Point{
public:
   double Longitude;
   double Latitude;
};
class Edge {
public:
   string Level;
   int Lanes;
   float Speed;
   vector<Point> Points;
};
class RoadNetwork {
public:
   std::vector<Edge> Edges;
};

class csRoadNetwork : csDrawable {
public:
   static RoadNetwork _roadnet;
   string filename = "BJ_Road_Network_2011.txt";

   map<string, csRoadClass> roadClasses;

   void loadFile()
   {
      // TODO
   }

   void createRoadClasses()
   {
      int namedRoads = 0;

      for (int i = 0; i < _roadnet.Edges.size(); i++)
      {
         string level = _roadnet.Edges[i].Level;
         int lanes = _roadnet.Edges[i].Lanes;
         float speed = (float)_roadnet.Edges[i].Speed;

         string roadclass = csRoadClass::buildClass(level, lanes, speed);

         if (roadclass != "secondary")
            namedRoads++;

         if (roadClasses.find(roadclass) == roadClasses.end())
         {
            roadClasses[roadclass] = csRoadClass();
            roadClasses[roadclass].roadclass = roadclass;
         }

         csRoadClass road = roadClasses[roadclass];

         road.setStyle();

         for (int j = 0; j < _roadnet.Edges[i].Points.size(); j++)
         {
            double x = _roadnet.Edges[i].Points[j].Longitude;
            double y = _roadnet.Edges[i].Points[j].Latitude;
            y = (csAutomagicalProjector::biasedProjectLat(y)
                 - csGlobalControls::getInstance()->projMinY);
            x = (csAutomagicalProjector::biasedProjectLon(x)
                 - csGlobalControls::getInstance()->projMinX);

            Vector3 point = Vector3((float)x, (float)y, 0.0f);

            road.mySurf.myGeometry.addVertex(point);

            if (j > 0)
               road.mySurf.myGeometry.addLine((uint)(road.points - 1), (uint)road.points);

            road.points++;
         }

         roadClasses[roadclass] = road;
      }

      for (auto entry : roadClasses)
      {
         entry.second.mySurf.init();
      }

      std::cout << "Roads: " + namedRoads;
   }

   void init()
   {
      loadFile();

      createRoadClasses();
   }

   void draw(float _t, float _dt)
   {
      if (csGlobalControls::getInstance()->showRoads == false)
         return;

      {
         roadClasses["secondary"].drawLayer0();
         roadClasses["primary"].drawLayer0();
         roadClasses["arterial"].drawLayer0();
         roadClasses["arterial ramp"].drawLayer0();
         roadClasses["highway ramp"].drawLayer0();

         roadClasses["secondary"].drawLayer1();
         roadClasses["primary"].drawLayer1();
         roadClasses["arterial ramp"].drawLayer1();
         roadClasses["highway ramp"].drawLayer1();
         roadClasses["arterial"].drawLayer1();
      }

      roadClasses["highway"].drawLayer0();
      roadClasses["highway"].drawLayer1();
   }

   void translate(Vector3 _vec)
   {
   }
};

}  // namespace city_sight

#endif
