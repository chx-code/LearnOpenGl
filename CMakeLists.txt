cmake_minimum_required(VERSION 2.8)

project(LearnOpenGl)

SET(CMAKE_BUILD_TYPE "Debug") 

SET(CMAKE_CXX_FLAGS "-g -Wall -std=c++0x")
SET(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -std=c++0x")

message(${CMAKE_SOURCE_DIR})

set(THIRD_PARTY_DIR ${CMAKE_SOURCE_DIR}/third_party)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/include/common)
include_directories(${CMAKE_SOURCE_DIR}/include/glad)
include_directories(${CMAKE_SOURCE_DIR}/include/glfw)
include_directories(${CMAKE_SOURCE_DIR}/include/glm)
include_directories(${THIRD_PARTY_DIR})

link_directories(${THIRD_PARTY_DIR})
link_directories(${THIRD_PARTY_DIR}/glfw)

aux_source_directory(${CMAKE_SOURCE_DIR}/src/common SOURCES_COMMON)


add_executable(helloTriangle demo/helloTriangle.cpp ${CMAKE_SOURCE_DIR}/src/glad.c)

target_link_libraries(helloTriangle glfw3)
target_link_libraries(helloTriangle dl)

add_executable(shaderTest demo/shaderTest.cpp 
    ${CMAKE_SOURCE_DIR}/src/glad.c 
    ${SOURCES_COMMON})
target_link_libraries(shaderTest glfw3)
target_link_libraries(shaderTest dl)

add_executable(textureTest demo/textureTest.cpp 
    ${CMAKE_SOURCE_DIR}/src/glad.c 
    ${SOURCES_COMMON})
target_link_libraries(textureTest glfw3)
target_link_libraries(textureTest dl)

add_executable(transformTest demo/transformTest.cpp 
    ${CMAKE_SOURCE_DIR}/src/glad.c 
    ${SOURCES_COMMON})
target_link_libraries(transformTest glfw3)
target_link_libraries(transformTest dl)

add_executable(coordinateSystemsTest demo/coordinateSystemsTest.cpp 
    ${CMAKE_SOURCE_DIR}/src/glad.c 
    ${SOURCES_COMMON})
target_link_libraries(coordinateSystemsTest glfw3)
target_link_libraries(coordinateSystemsTest dl)

add_executable(cameraTest demo/cameraTest.cpp 
    ${CMAKE_SOURCE_DIR}/src/glad.c 
    ${SOURCES_COMMON})
target_link_libraries(cameraTest glfw3)
target_link_libraries(cameraTest dl)

add_executable(lightTest demo/lightTest.cpp 
    ${CMAKE_SOURCE_DIR}/src/glad.c 
    ${SOURCES_COMMON})
target_link_libraries(lightTest glfw3)
target_link_libraries(lightTest dl)