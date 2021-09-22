// Unit tests for drawing road networks from sumo input.
#include "sumo_road_network.hpp"

#include "render.hpp"

#include <gtest/gtest.h>

// TEST(StochRoadUnitTests, TestLoadFile) {
//    city_sight::SumoRoadNetwork road_network;
//    road_network.set_filerootname("./Data/manhattan");
//    road_network.loadFile();


//    stoch_graph& graph = road_network.retrieve_graph();
//    int sum = 0;
//    for (int i = 0; i < graph.edges.size(); i++) {
//       EXPECT_GT(graph.edges[i].get_len(), 0);

//       sum += graph.edges[i].neighbors_size();

//    }

//    EXPECT_EQ(graph.edges[3972].get_den_to_vel().get_v_max(), 44);
// }

// static bool once = false;
// void SetupOpenGL() {
//    if (once == false) {
//       int argc = 0;
//       char** argv;
//       glutInit(&argc, argv);
//       glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
//       glutInitWindowSize(500, 500);
//       glutInitWindowPosition(100, 100);
//       glutCreateWindow("Hello world");
//       glutDisplayFunc(city_sight::Render);
//       GLint GlewInitResult = glewInit();
//       if (GLEW_OK != GlewInitResult)
//       {
//          printf("ERROR: %s\n",glewGetErrorString(GlewInitResult));
//          exit(1);
//       }
//       std::cout << "GL version: " << glGetString(GL_VERSION) << std::endl;

//       once = true;
//    }
// }

// TEST(StochRoadUnitTests, TestCreateReadClasses) {
//    // Initializes graphics.
//    SetupOpenGL();

//    city_sight::csShaderManager::load();

//    // Loads the network file.
//    city_sight::SumoRoadNetwork road_network;
//    road_network.set_filerootname("./Data/manhattan");
//    road_network.loadFile();
//    road_network.createRoadClasses();
// }

// TEST(StochRoadUnitTests, TestInputLocation) {
//    // Initializes graphics.
//    SetupOpenGL();

//    city_sight::csShaderManager::load();

//    // Loads the network file.
//    city_sight::SumoRoadNetwork road_network;
//    road_network.set_filerootname("./Data/manhattan");
//    road_network.loadFile();
//    road_network.createRoadClasses();

//    road_network.set_location();
// }

int main(int argc, char** argv) {
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
