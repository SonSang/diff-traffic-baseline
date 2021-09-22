#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <cassert>
#include <cstring>

#ifdef ANDROID
#include <jni.h>
#else
#include <Magick++.h>
#endif

// TODO Many of these headers require other includes and only compile as they
// are listed in this order.
#include "gl_include.hpp"
#include "vector2.hpp"
#include "vector3.hpp"
#include "vector4.hpp"
#include "matrix4.hpp"
#include "drawable.hpp"
#include "shaders.hpp"
#include "shader_manager.hpp"
#include "global_controls.hpp"
#include "automagical_projector.hpp"
#include "camera.hpp"
#include "geometry.hpp"
#include "paramval.hpp"
#include "color.hpp"
#include "render.hpp"
#include "triangle.hpp"
#include "proto_renderer.hpp"
#include "route_renderer.hpp"
#include "sumo_road_network.hpp"
#include "cabspotter.hpp"
#include "satellite.hpp"
#include "log_config.hpp"
#include "current_position.hpp"
#include "check_gl_error.hpp"
#include "zip_file_manager.hpp"
#include "location.hpp"
#include "route.pb.h"
#include "zpr.h"
#include "mouse_navigation.hpp"

// Used for debugging openGL calls.
static void printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("GL %s = %s\n", name, v);
}

using std::string;
using std::vector;
using std::map;
using city_sight::city_global::csDrawables;
using city_sight::RouteRenderer;
using city_sight::Vector2;

namespace city_sight {


void defViewport() {

   csCamera::getInstance()->InitializeView();
   csCamera::getInstance()->setProj();
   csCamera::getInstance()->setView();
}

}  // namespace city_sight


bool initialized = false;

// Declare a global 'drawable'.
city_sight::ProtoRenderer road_renderer;
city_sight::RouteRenderer* route_renderer = NULL;
city_sight::CurrentPosition* current_position = NULL;
city_sight::Triangle* triangle = NULL;
city_sight::SumoRoadNetwork* road_network = NULL;
city_sight::CabSpotter* cab_spotter = NULL;
city_sight::CabSpotter* cab_spotter2 = NULL;


string cabspotter_filename,
   sumo_road_net_filename,
   cabspotter_route_filename,
   lane_velocities_filename;

signed char* byte_array_of_route = 0;

ReadConfigFile() {
   xmlpp::DomParser parser;
   parser.parse_file("config.xml");

   //Walk the tree:
   const xmlpp::Node* pNode = parser.get_document()->get_root_node();

   xmlpp::Node::NodeList list = pNode->get_children();

   for(xmlpp::Node::NodeList::iterator iter = list.begin();
       iter != list.end(); ++iter) {

      const xmlpp::Node* node = *iter;

      const Glib::ustring nodename = node->get_name();

      if (nodename == "cabspotter") {
         const xmlpp::Element* nodeElement =
         dynamic_cast<const xmlpp::Element*>(node);

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

               if (attribute->get_name() == "filename") {
                  cabspotter_filename = attribute->get_value();
               }

               if (attribute->get_name() == "route_file") {
                  cabspotter_route_filename = attribute->get_value();
               }
            }
         }
      }

      if (nodename == "sumoroadnetwork") {

         const xmlpp::Element* nodeElement =
         dynamic_cast<const xmlpp::Element*>(node);

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

               if (attribute->get_name() == "filename") {
                  sumo_road_net_filename = attribute->get_value();
               }
               if (attribute->get_name() == "lane_velocities") {
                  lane_velocities_filename = attribute->get_value();
               }
            }
         }
      }
   }
}

// Function called by Java on every draw call.
void Draw()
{
   // Clear the color buffer
   glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT);

   // Calls the draw function on every 'Drawable'.
   for (uint i = 0; i < city_sight::city_global::csDrawables.size(); i++) {
      city_sight::city_global::csDrawables[i]->draw(0, 0);
   }

   glutSwapBuffers();
}

void SetAPK(const char* apk_location) {
   // Initializes the file manager.
   bool opened_zip_file = ZipFileManager::GetInstance()->OpenZip(apk_location);
   if (!opened_zip_file) {
      LOGE("Cannot open file.\n");
   } else {
      LOGI("Opened zip file.\n");
   }
}

void SetViewport(int w, int h) {
   LOGV("In SetViewport\n");

   // Initializes GL viewport.
    glViewport(0, 0, w, h);
    checkGlError("glViewport");
    city_sight::csGlobalControls::getInstance()->width = w;
    city_sight::csGlobalControls::getInstance()->height = h;
    city_sight::defViewport();
}

// Setup call by Java to initialize the renderer.
// TODO Work out multiple call issues.
// APK likely needs to be set first.
bool Setup() {
    printGLString("Version", GL_VERSION);
    printGLString("Vendor", GL_VENDOR);
    printGLString("Renderer", GL_RENDERER);
    printGLString("Extensions", GL_EXTENSIONS);

    // Compile shaders and create program.
    city_sight::csShaderManager::load();
    LOGI("Shader manager loaded.");

    // Add all 'Drawables'.
    // NOTE Must have scope beyond this function call.  Use either static or
    // new.  Most declarations made before the shader maneger is initialized
    // will fail.
    city_sight::city_global::csDrawables.clear();

    // TODO TEMP SAT MAP
    city_sight::csSatelliteMap* satellite_map =
       new city_sight::csSatelliteMap();
    satellite_map->retrieve_image().set_filename("../Data/NASA_Manhattan_bw.jpg");
    csDrawables.push_back(satellite_map);

    // Set up road network. (TODO)
    if (sumo_road_net_filename != "") {
       road_network = new city_sight::SumoRoadNetwork();
       road_network->set_filerootname(sumo_road_net_filename);

       csDrawables.push_back(road_network);
    }

    if (cabspotter_filename != "") {
       cab_spotter = new city_sight::CabSpotter();
       cab_spotter->set_filename(cabspotter_filename);
       csDrawables.push_back(cab_spotter);
    }


    for (int i = 0; i < city_sight::city_global::csDrawables.size(); i++) {
       city_sight::city_global::csDrawables[i]->init();
    }

    // For output to app
    road_network->writeProto();

    if (cabspotter_route_filename != "")
       road_network->DrawRoute(cabspotter_route_filename);

    if (lane_velocities_filename != "")
       road_network->ColorLaneVelocities(lane_velocities_filename);


    // TODO Set the dimensions of the billboard first and let init go as normal.
    Vector2 center;
    float x_length, y_length;
    road_network->GetCenterAndDimensions(&center, &x_length, &y_length);

    satellite_map->retrieve_image().SetCenterAndDimensions(center,
                                                           x_length,
                                                           y_length);

    city_sight::csCamera::GetInstance()->set_zoom_factor(1);
    city_sight::csCamera::GetInstance()->setProj();

    initialized = true;

    LOGI("Finished renderer initialization.");
    return true;
}

int main(int argc, char** argv) {
   ReadConfigFile();

   // Initializes Magick.
   // TODO Should be done by library.
   Magick::InitializeMagick(*argv);

   // Initializes glut.
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
   glutInitWindowSize(800, 800);
   glutInitWindowPosition(100, 100);
   glutCreateWindow("Hello world");
   glutMouseFunc(zprMouse);
   glutMotionFunc(zprMotion);
   glutDisplayFunc(Draw);
   GLint GlewInitResult = glewInit();
	if (GLEW_OK != GlewInitResult)
	{
		printf("ERROR: %s\n",glewGetErrorString(GlewInitResult));
		exit(1);
	}
   std::cout << "GL version: " << glGetString(GL_VERSION) << std::endl;

   // Depth test disabled for 2D rendering.
   glEnable(GL_MULTISAMPLE);
   glEnable(GL_LINE_SMOOTH);
   glEnable(GL_ALPHA_TEST);
   glShadeModel(GL_SMOOTH);
   glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
   glClearDepth(1.0f);
   //   glEnable(GL_DEPTH_TEST);
   //   glDepthFunc(GL_LEQUAL);
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
   glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   SetViewport(800, 800);

   Setup();

   glutMainLoop();
}


#ifdef ANDROID
// TODO JNI definitions left in for now as may eventually be used.
// TODO Generate interfaces automatically with SWIG.
extern "C" {
   JNIEXPORT void JNICALL Java_com_gamma_trafficrouting_map_GL2JNILib_init(
      JNIEnv * env,
      jobject obj);

   JNIEXPORT void JNICALL Java_com_gamma_trafficrouting_map_GL2JNILib_SetView(
      JNIEnv * env,
      jobject obj,
      jint width,
      jint height);

    JNIEXPORT void JNICALL Java_com_gamma_trafficrouting_map_GL2JNILib_step(
      JNIEnv * env,
      jobject obj);

   JNIEXPORT void JNICALL Java_com_gamma_trafficrouting_map_GL2JNILib_setlocation(
      JNIEnv * env,
      jobject obj,
      jfloat longitude,
      jfloat latitude);

    JNIEXPORT void JNICALL Java_com_gamma_trafficrouting_map_GL2JNILib_passroute(
      JNIEnv *env,
      jobject obj,
      jbyteArray route);

    JNIEXPORT void JNICALL Java_com_gamma_trafficrouting_map_GL2JNILib_SetAPK(
      JNIEnv *env,
      jobject obj,
      jstring apk_location);

   JNIEXPORT void JNICALL
   Java_com_gamma_trafficrouting_map_GL2JNILib_CenterOnCurrentPosition(
      JNIEnv * env,
      jobject obj);

   JNIEXPORT void JNICALL Java_com_gamma_trafficrouting_map_GL2JNILib_Delete(
      JNIEnv * env,
      jobject obj);
};

JNIEXPORT void JNICALL Java_com_gamma_trafficrouting_map_GL2JNILib_init(
   JNIEnv * env,
   jobject obj)
{
   Setup();
}

JNIEXPORT void JNICALL Java_com_gamma_trafficrouting_map_GL2JNILib_SetView(
   JNIEnv * env,
   jobject obj,
   jint width,
   jint height) {
   LOGV("SetViewport\n");
   SetViewport(width, height);
}

JNIEXPORT void JNICALL Java_com_gamma_trafficrouting_map_GL2JNILib_step(
   JNIEnv * env,
   jobject obj)
{
   Draw();
}

JNIEXPORT void JNICALL Java_com_gamma_trafficrouting_map_GL2JNILib_setlocation(
   JNIEnv * env,
   jobject obj,
   jfloat longitude,
   jfloat latitude)
{
   city_sight::Location::GetInstance()->SetLocation(longitude, latitude);
}

JNIEXPORT void JNICALL
Java_com_gamma_trafficrouting_map_GL2JNILib_CenterOnCurrentPosition(
   JNIEnv * env,
   jobject obj)
{
   city_sight::csCamera::GetInstance()->CenterOnCurrentPosition();
}

JNIEXPORT void JNICALL Java_com_gamma_trafficrouting_map_GL2JNILib_passroute(
   JNIEnv *env,
   jobject obj,
   jbyteArray route)
{
   // TODO This is probably a memory leak. May need to be free'd after Setup.
   // Gets the location of the apk to allow the C++ code to unzip and access
   // files.
   jboolean is_a_copy;
   const char* apk_location_ =
   env->GetStringUTFChars(apk_location, &is_a_copy) ;

   SetAPK(apk_location_);
}

JNIEXPORT void JNICALL Java_com_gamma_trafficrouting_map_GL2JNILib_Delete(
  JNIEnv *env,
  jobject obj) {
   LOGE("Called Delete on systems.\n");
   city_sight::csCamera::Delete();
   city_sight::Location::Delete();
}
#endif
