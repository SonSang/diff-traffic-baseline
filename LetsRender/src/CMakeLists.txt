# Notice the "recycling" of CMAKE_C_FLAGS.
# This is necessary to pck up android flags.
# TODO Will -lm actually work on android?
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -lm -fpermissive -fPIC -Wfatal-errors -g -ggdb -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -lm -fpermissive -fPIC -Wfatal-errors -O3")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

include_directories(/usr/include/ImageMagick/)
include_directories(/usr/include/glibmm-2.4/)
include_directories(/usr/lib/x86_64-linux-gnu/glibmm-2.4/include/)
include_directories(/usr/include/glib-2.0/)
include_directories(/usr/lib/x86_64-linux-gnu/glib-2.0/include/)
include_directories(/usr/include/libxml++-2.6/)
include_directories(/usr/lib/libxml++-2.6/include/)

# Add src libraries
include_directories(drawables)

# add_subdirectory(libsrc/protobuf)
# include_directories(libsrc/protobuf/src)

# add_subdirectory(libsrc/proj-4.8.0)
# include_directories(libsrc/proj-4.8.0/src)

add_subdirectory(libsrc/zlib)
include_directories(libsrc/zlib)

# If using android, add log
# set(LIBRARY_DEPS GLESv2 log)

set(MY_SRCS
  shader_manager.cpp
  global_controls.cpp
  camera.cpp
  vector3.cpp
  city_sight.cpp
  shaders.cpp
  location.cpp
  zip_file_manager.cpp
  zpr.c)

set(PROTOS
  drawable_road_net.pb.cc
  road_network.pb.cc
  route.pb.cc)

set(EXTERNAL
  /usr/lib/libproj.so
  /usr/lib/x86_64-linux-gnu/libglibmm-2.4.so
  /usr/lib/libxml++-2.6.so
  /usr/lib/x86_64-linux-gnu/libboost_iostreams.so
  /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
  /usr/lib/x86_64-linux-gnu/libboost_system.so
  /usr/lib/x86_64-linux-gnu/libprotobuf.so
  /usr/lib/x86_64-linux-gnu/libGL.so
  /usr/lib/x86_64-linux-gnu/libGLEW.so
  /usr/lib/x86_64-linux-gnu/libGLU.so
  /usr/lib/x86_64-linux-gnu/libglut.so
  /usr/lib/x86_64-linux-gnu/libglib-2.0.so
  /usr/lib/x86_64-linux-gnu/libcairo.so
  /usr/lib/x86_64-linux-gnu/libMagick++.so
  )

set(LOCAL
  /usr/local/lib/libroadie.so
  /usr/local/lib/libstoch_graph.so
 )

find_package (Threads)

add_executable(CitySight ${MY_SRCS} ${PROTOS})

# Link to android libraries.
target_link_libraries(CitySight ${LIBRARY_DEPS} ${CMAKE_THREAD_LIBS_INIT})

# Link to libsrc libraries.
target_link_libraries(CitySight ${LOCAL} ${EXTERNAL} zlib)

# Enables c++11.
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR CMAKE_COMPILER_IS_GNUCXX)
    include(CheckCXXCompilerFlag)
    check_cxx_compiler_flag(--std=c++11 SUPPORTS_STD_CXX11)
    check_cxx_compiler_flag(--std=c++0x SUPPORTS_STD_CXX01)
    if(SUPPORTS_STD_CXX11)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --std=c++11")
    elseif(SUPPORTS_STD_CXX01)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++0x")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --std=c++0x")
    else()
        message(ERROR "Compiler does not support --std=c++11 or --std=c++0x.")
    endif()
endif()
