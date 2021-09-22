#ifndef SUMO_ROAD_NETWORK_HPP
#define SUMO_ROAD_NETWORK_HPP

#include <map>
#include <limits>
#include <string>
#include <fstream>

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
using std::string;
using std::ifstream;

namespace city_sight {

class SumoRoadNetwork : public csDrawable {
private:
   string filerootname_ = "";
   stoch_graph graph_;
   sumo::network sumo_network;
public:
   // TODO Make this private.
   map<string, csSumoRoadClass> roadClasses;

   vector<csSumoRoadClass> other_roads_;

   // The filename should contain the path and root name of the road network
   // files. The files are assumed to be a collection of sumo road network files
   // with nodes, edges, and connections.
   void set_filerootname(string filerootname) {
      filerootname_ = filerootname;
   }

   string get_filerootname() {
      return filerootname_;
   }

   stoch_graph& retrieve_graph() {
      return graph_;
   }


   void ColorLaneVelocities(string filename) {
      xmlpp::DomParser parser;
      parser.parse_file(filename);

      //Walk the tree:
      const xmlpp::Node* pNode = parser.get_document()->get_root_node();

      xmlpp::Node::NodeList list = pNode->get_children();
      for(xmlpp::Node::NodeList::iterator iter = list.begin(); iter != list.end(); ++iter)
      {
         ReadInterval(*iter, "speed");
      }
   }

   void ColorLaneFlows(string filename) {
      xmlpp::DomParser parser;
      parser.parse_file(filename);

      //Walk the tree:
      const xmlpp::Node* pNode = parser.get_document()->get_root_node();

      xmlpp::Node::NodeList list = pNode->get_children();
      for(xmlpp::Node::NodeList::iterator iter = list.begin(); iter != list.end(); ++iter)
      {
         ReadInterval(*iter, "density");
      }
   }

   void ReadInterval(const xmlpp::Node* node, string attribute_name) {
      const Glib::ustring nodename = node->get_name();

      // Ignore node elements.
      if (nodename == "interval") {
         const xmlpp::Element* nodeElement =
         dynamic_cast<const xmlpp::Element*>(node);

         if(nodeElement) {
            float begin_time, end_time;

            // Gets the attributes
            const xmlpp::Element::AttributeList& attributes =
            nodeElement->get_attributes();

            for(auto iter = attributes.begin();
                iter != attributes.end();
                ++iter) {

               const xmlpp::Attribute* attribute = *iter;
               const Glib::ustring namespace_prefix =
               attribute->get_namespace_prefix();

               if (attribute->get_name() == "begin") {
                  begin_time = atof(attribute->get_value().c_str());
               }
               if (attribute->get_name() == "end") {
                  end_time = atof(attribute->get_value().c_str());
               }
            }

            // Finished with this element.

            // TODO These times can change
            if ((begin_time < 500) and (end_time > 500)) {

               // Reads the children.
               xmlpp::Node::NodeList list = node->get_children();
               for(xmlpp::Node::NodeList::iterator iter = list.begin();
                   iter != list.end();
                   ++iter)
               {
                  ReadEdge(*iter, attribute_name);
               }
            }
         }
      }
   }

   void ReadEdge(const xmlpp::Node* node, string attribute_name) {
      const Glib::ustring nodename = node->get_name();

      // Ignore node elements.
      if (nodename == "edge") {
         const xmlpp::Element* nodeElement =
         dynamic_cast<const xmlpp::Element*>(node);

         if(nodeElement) {

            string id;

            // Gets the attributes
            const xmlpp::Element::AttributeList& attributes =
            nodeElement->get_attributes();

            for(auto iter = attributes.begin();
                iter != attributes.end();
                ++iter) {

               const xmlpp::Attribute* attribute = *iter;
               const Glib::ustring namespace_prefix =
               attribute->get_namespace_prefix();

               if (attribute->get_name() == "id") {
                  id = attribute->get_value();
               }
            }

            // Finished with this element.
            float value_total = 0;

            int size = 0;

            // Reads the children.
            xmlpp::Node::NodeList list = node->get_children();
            for(xmlpp::Node::NodeList::iterator iter = list.begin();
                iter != list.end();
                ++iter)
            {
               float value = ReadLane(*iter, attribute_name);
               if (value > -1) {
                  value_total += value;
                  size++;
               }
            }

            value_total /= size;

            if (attribute_name == "density")
               ColorLane(id, 0, std::min((value_total / 100.0f), 1.0f), 1);
            // if (attribute_name == "speed")
            //    ColorLane(id, 120, std::min((value_total / 30.0f), 1.0f), 1);
            if (attribute_name == "speed")
               ColorLane(id, (std::min((value_total / 13.0f), 1.0f)) * 120, 1.0f, 1);

         }
      }
   }

   float ReadLane(const xmlpp::Node* node, string attribute_name) {
      const Glib::ustring nodename = node->get_name();

      // Ignore node elements.
      if (nodename == "lane") {
         const xmlpp::Element* nodeElement =
         dynamic_cast<const xmlpp::Element*>(node);

         float value;

         if(nodeElement) {

            // Gets the attributes
            const xmlpp::Element::AttributeList& attributes =
            nodeElement->get_attributes();

            for(auto iter = attributes.begin();
                iter != attributes.end();
                ++iter) {

               const xmlpp::Attribute* attribute = *iter;
               const Glib::ustring namespace_prefix =
               attribute->get_namespace_prefix();

               if (attribute->get_name() == attribute_name) {
                  value = atof(attribute->get_value().c_str());
               }
            }

            // Finished with this element.
            return value;
         }
         else
            return -1;
      }
      else
         return -1;
   }

   void ColorLane(string lane_id, float h, float s, float v) {

      // Check if its there.  If not, print an error and return.
      if (sumo_network.edges.find(lane_id) == sumo_network.edges.end()) {
         std::cout << "ERROR: " << lane_id << " not found in sumo network.\n";
         return;
      }

      // Gets the edge from the sumo network.
      const sumo::edge& edge = sumo_network.edges[lane_id];

      // Calculates the road class type based on the edge type.
      string roadclass = csSumoRoadClass::buildClass(edge.type->id);

      // Creates a road class specifically for this road.
      other_roads_.resize(other_roads_.size() + 1);
      csSumoRoadClass& road = other_roads_.back();

      // This sets the style elements of the road.
      road.roadclass = roadclass;
      road.setStyle();

      // Creates the geometry of the road.
      if (edge.shape.size() == 0) {
         sumo::node from, to;

         from = *edge.from;
         to = *edge.to;

         Vector3 point1 = Vector3((float)from.xy[0],
                                  (float)from.xy[1],
                                  0.0f);
         road.mySurf.myGeometry.addVertex(point1);

         Vector3 point = Vector3((float)to.xy[0],
                                 (float)to.xy[1],
                                 0.0f);
         road.mySurf.myGeometry.addVertex(point);

         road.points++;

         road.mySurf.myGeometry.addLine((uint) road.points - 1,
                                        (uint) road.points);

         road.points ++;

      } else {
         for (int j = 0; j < edge.shape.size(); j++) {
            Vector3 point = Vector3((float)edge.shape[j][0],
                                    (float)edge.shape[j][1],
                                    0.0f);

            road.mySurf.myGeometry.addVertex(point);

            if (j > 0)
               road.mySurf.myGeometry.addLine((uint)(road.points - 1),
                                              (uint)road.points);

            road.points++;
         }
      }

      // Sets the road color.  The background is always black.
      road.setHSV0(0, 0, 0);
      road.setHSV1(h, s, v);

      road.mySurf.init();
   }

   void GetCenterAndDimensions(Vector2* center,
                               float* x_length,
                               float* y_length) {
      float x_length_, y_length_;
      Vector2 center_;

      float min_x, max_x;
      float min_y, max_y;

      min_x = min_y = std::numeric_limits<float>::max();
      max_x = max_y = std::numeric_limits<float>::min();

      for (auto edge : sumo_network.edges) {
         const sumo::edge& edge_i = edge.second;

         if (edge_i.shape.size() == 0) {
            sumo::node from, to;

            from = *edge_i.from;
            to = *edge_i.to;

            if (from.xy[0] > max_x)
               max_x = from.xy[0];
            if (from.xy[0] < min_x)
               min_x = from.xy[0];

            if (from.xy[1] > max_y)
               max_y = from.xy[1];
            if (from.xy[1] < min_y)
               min_y = from.xy[1];

            if (to.xy[0] > max_x)
               max_x = to.xy[0];
            if (to.xy[0] < min_x)
               min_x = to.xy[0];

            if (to.xy[1] > max_y)
               max_y = to.xy[1];
            if (to.xy[1] < min_y)
               min_y = to.xy[1];

         } else {
            for (int j = 0; j < edge_i.shape.size(); j++) {

               if (edge_i.shape[j][0] > max_x)
                  max_x = edge_i.shape[j][0];
               if (edge_i.shape[j][0] < min_x)
                  min_x = edge_i.shape[j][0];

               if (edge_i.shape[j][1] > max_y)
                  max_y = edge_i.shape[j][1];
               if (edge_i.shape[j][1] < min_y)
                  min_y = edge_i.shape[j][1];
            }
         }
      }

      // Now that the range of the data has been determined, this calculates its
      // center point.
      center_.x = ((max_x - min_x) * 0.5) + min_x;
      center_.y = ((max_y - min_y) * 0.5) + min_y;

      x_length_ = max_x - min_x;
      y_length_ = max_y - min_y;

      // Sets the output values.
      (*center) = center_;
      (*y_length) = y_length_;
      (*x_length) = x_length_;
   }

   void loadFile() {
      string nodes_file = filerootname_ + ".nod.xml";
      string edges_file = filerootname_ + ".edg.xml";
      string edge_type_file = filerootname_ + ".typ.xml";
      string connections_file = filerootname_ + ".con.xml";

      // TODO get filenames from one place only.
      sumo_network = sumo::load_xml_network(nodes_file.c_str(),
                                            edge_type_file.c_str(),
                                            edges_file.c_str(),
                                            connections_file.c_str());

      sumo_util::id_maps id_maps;
      graph_.load_graph_from_sumo(filerootname_,
                                  sumo_network,
                                  &id_maps);

   }

   // This class writes out a created road network to a protobuf.
   void writeProto() {
      SumoRoadNetworkMessage message;

      for (auto roadClassMapElem : roadClasses) {
         LocalFrame* instance = LocalFrame::GetInstance();
         message.set_offset_x(instance->get_x_offset());
         message.set_offset_y(instance->get_y_offset());

         RoadClassTupleMessage* tuple = message.add_tuples();

         tuple->set_road_class_name(roadClassMapElem.first);

         RoadClassMessage* road_class = tuple->mutable_road_class();

         road_class->set_h0(roadClassMapElem.second.h0);
         road_class->set_s0(roadClassMapElem.second.s0);
         road_class->set_v0(roadClassMapElem.second.v0);

         road_class->set_h1(roadClassMapElem.second.h1);
         road_class->set_s1(roadClassMapElem.second.s1);
         road_class->set_v1(roadClassMapElem.second.v1);

         road_class->set_road_class(roadClassMapElem.second.roadclass);

         SurfaceMessage* surface = road_class->mutable_surface();

         GeometryMessage* geometry_message = surface->mutable_geometry();

         csGeometry& geometry = roadClassMapElem.second.mySurf.myGeometry;

         geometry_message->set_numvertices(geometry.numVertices);
         geometry_message->set_numindices(geometry.numIndices);
         // TODO Make this generic.
         geometry_message->set_drawmode(GeometryMessage::Lines);

         for (int i = 0; i < geometry.numVertices; i++) {
            VertexMessage* vertex = geometry_message->add_vertices();
            vertex->set_x(geometry.vertices[i].position.x);
            vertex->set_y(geometry.vertices[i].position.y);
            vertex->set_z(geometry.vertices[i].position.z);
         }

         for (int i = 0; i < geometry.numIndices; i++) {
            geometry_message->add_indices(geometry.indices[i]);
         }
      }

      string serialized_message;
      google::protobuf::TextFormat::PrintToString(message, &serialized_message);

      std::ofstream fout("road_net_proto.txt");
      fout << serialized_message;

      // Output a binary version of the protobuf.
      using std::ios;
      std::fstream out("road_net.pb", ios::out | ios::binary | ios::trunc);
      message.SerializeToOstream(&out);
      out.close();
   }

   void DrawRoute(string filename) {
      ifstream fin;
      fin.open(filename);

      std::cout << "Route file is " << filename << std::endl;;

      vector<string> route_ids;

      string line;
      while (getline(fin, line)) {
         route_ids.push_back(line);
      }

      std::cout << "Route size is " << route_ids.size() << std::endl;
      std::cout << "first " << route_ids[0] << std::endl;
      std::cout << "last " << route_ids.back() << std::endl;

      for (int i = 0; i < route_ids.size(); i++) {
         ColorLane(route_ids[i], 120, 1, 1);
      }
   }

   void createRoadClasses() {
      // Initialize class map.
      for (string class_name : csSumoRoadClass::get_class_names()) {
            roadClasses[class_name] = csSumoRoadClass();
            roadClasses[class_name].roadclass = class_name;
            roadClasses[class_name].setStyle();
      }

      for (auto edge : sumo_network.edges) {
         string roadclass = csSumoRoadClass::buildClass(edge.second.type->id);

         if (roadClasses.find(roadclass) == roadClasses.end()) {
            std::cout << "WARNING: Road class not found: " << roadclass
                      << " for " << edge.second.type->id << std::endl;
         }

         csSumoRoadClass& road = roadClasses[roadclass];

         sumo::edge& edge_i = edge.second;

         // This offset was used to zero a road.  This is now done by the
         // android renderer.
         float offset = 0;

         if (edge_i.shape.size() == 0) {
            sumo::node from, to;

            from = *edge_i.from;
            to = *edge_i.to;

            Vector3 point1 = Vector3((float)from.xy[0] - offset,
                                     (float)from.xy[1] - offset,
                                     0.0f);
            road.mySurf.myGeometry.addVertex(point1);

            Vector3 point = Vector3((float)to.xy[0] - offset,
                                    (float)to.xy[1] - offset,
                                    0.0f);
            road.mySurf.myGeometry.addVertex(point);

            road.points++;

            road.mySurf.myGeometry.addLine((uint) road.points - 1,
                                           (uint) road.points);

            road.points ++;
         } else {
            for (int j = 0; j < edge_i.shape.size(); j++) {
               Vector3 point = Vector3((float)edge_i.shape[j][0] - offset,
                                       (float)edge_i.shape[j][1] - offset
                                       , 0.0f);
               road.mySurf.myGeometry.addVertex(point);

               if (j > 0)
                  road.mySurf.myGeometry.addLine((uint)(road.points - 1),
                                                 (uint)road.points);

               road.points++;
            }
         }
      }

      for (auto& entry : roadClasses)
      {
         std::cout << "Initializing " << entry.first << std::endl;
         entry.second.mySurf.init();
      }
   }

   void init()
   {
      loadFile();

      createRoadClasses();

      Vector2 center;
      float x_length, y_length;
      GetCenterAndDimensions(&center, &x_length, &y_length);

      std::cout << "\nmap center is " << center.x << " " << center.y
                << " lengths are " << x_length << " " << y_length
                << std::endl;

      csCamera::GetInstance()->CenterOnRoute(center, x_length, y_length);
   }

   void draw(float _t, float _dt)
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

      roadClasses["highway"].drawLayer0();
      roadClasses["highway"].drawLayer1();

      for (int i = 0; i < other_roads_.size(); i++) {
         other_roads_[i].drawLayer0();
      }
      for (int i = 0; i < other_roads_.size(); i++) {
         other_roads_[i].drawLayer1();
      }
   }

   void translate(Vector3 _vec)
   {
   }
};

}  // namespace city_sight

#endif
