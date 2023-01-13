cmake_minimum_required(VERSION 2.8)

project(LearnOpenGl)

SET(CMAKE_CXX_FLAGS "-g -Wall -std=c++0x")

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


add_executable(helloTriangle demo/helloTriangle.cpp ${CMAKE_SOURCE_DIR}/src/glad.c)

target_link_libraries(helloTriangle glfw3)
target_link_libraries(helloTriangle dl)

add_executable(shaderTest demo/shaderTest.cpp ${CMAKE_SOURCE_DIR}/src/glad.c ${CMAKE_SOURCE_DIR}/src/common/shader.cpp)
target_link_libraries(shaderTest glfw3)
target_link_libraries(shaderTest dl)

add_executable(textureTest demo/textureTest.cpp ${CMAKE_SOURCE_DIR}/src/glad.c ${CMAKE_SOURCE_DIR}/src/common/shader.cpp)
target_link_libraries(textureTest glfw3)
target_link_libraries(textureTest dl)

add_executable(transformTest demo/transformTest.cpp ${CMAKE_SOURCE_DIR}/src/glad.c ${CMAKE_SOURCE_DIR}/src/common/shader.cpp)
target_link_libraries(transformTest glfw3)
target_link_libraries(transformTest dl)