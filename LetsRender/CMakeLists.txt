message("Protobuf autogeneration STARTED")

file(GLOB proto_packages "./src/*.proto")
execute_process(COMMAND protoc -I=${CMAKE_SOURCE_DIR}/src/ --cpp_out=${CMAKE_SOURCE_DIR}/src/ ${proto_packages})

file(GLOB proto_packages2 "${CMAKE_SOURCE_DIR}/src/drawables/*.proto")
execute_process(COMMAND protoc -I=${CMAKE_SOURCE_DIR}/src/drawables/ --cpp_out=${CMAKE_SOURCE_DIR}/src/drawables/ ${proto_packages2})

message("Done generating protobufs.")

cmake_minimum_required(VERSION 2.8)

project(LetsRender)

add_subdirectory(src)

# Turns on the debugging information.
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -ggdb -O0")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

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
