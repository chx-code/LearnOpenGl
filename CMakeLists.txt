cmake_minimum_required(VERSION 2.8)

project(LearnOpenGl)

SET(CMAKE_BUILD_TYPE "Debug") 

# -fvisibility 设置符号可见性
SET(CMAKE_CXX_FLAGS "-g -Wall -std=c++0x")
SET(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -std=c++0x -fvisibility=hidden")

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

message(${CMAKE_SOURCE_DIR})

set(THIRD_PARTY_DIR ${CMAKE_SOURCE_DIR}/third_party)

# 源码引用三方库
add_subdirectory(${THIRD_PARTY_DIR}/glfw-3.3.8/)
add_subdirectory(${THIRD_PARTY_DIR}/assimp/)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${THIRD_PARTY_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/include/common)
include_directories(${CMAKE_SOURCE_DIR}/include/glad)
include_directories(${CMAKE_SOURCE_DIR}/include/glfw)
include_directories(${CMAKE_SOURCE_DIR}/include/glm)
include_directories(${THIRD_PARTY_DIR}/assimp/include/)

link_directories(${THIRD_PARTY_DIR})

# common cpp
aux_source_directory(${CMAKE_SOURCE_DIR}/src/common SOURCES_COMMON)

add_executable(helloTriangle demo/helloTriangle.cpp
        ${CMAKE_SOURCE_DIR}/src/glad.c)
target_link_libraries(helloTriangle glfw)
target_link_libraries(helloTriangle dl)

add_executable(shaderTest demo/shaderTest.cpp
    ${CMAKE_SOURCE_DIR}/src/glad.c
    ${SOURCES_COMMON})
target_link_libraries(shaderTest glfw)
target_link_libraries(shaderTest dl)

add_executable(textureTest demo/textureTest.cpp
    ${CMAKE_SOURCE_DIR}/src/glad.c
    ${SOURCES_COMMON})
target_link_libraries(textureTest glfw)
target_link_libraries(textureTest dl)

add_executable(transformTest demo/transformTest.cpp
    ${CMAKE_SOURCE_DIR}/src/glad.c
    ${SOURCES_COMMON})
target_link_libraries(transformTest glfw)
target_link_libraries(transformTest dl)

add_executable(coordinateSystemsTest demo/coordinateSystemsTest.cpp
    ${CMAKE_SOURCE_DIR}/src/glad.c
    ${SOURCES_COMMON})
target_link_libraries(coordinateSystemsTest glfw)
target_link_libraries(coordinateSystemsTest dl)

add_executable(cameraTest demo/cameraTest.cpp
    ${CMAKE_SOURCE_DIR}/src/glad.c
    ${SOURCES_COMMON})
target_link_libraries(cameraTest glfw)
target_link_libraries(cameraTest dl)

add_executable(lightTest demo/lightTest.cpp
    ${CMAKE_SOURCE_DIR}/src/glad.c
    ${SOURCES_COMMON})
target_link_libraries(lightTest glfw)
target_link_libraries(lightTest dl)

add_executable(lightTexTest demo/lightTexTest.cpp
        ${CMAKE_SOURCE_DIR}/src/glad.c
        ${SOURCES_COMMON})
target_link_libraries(lightTexTest glfw)
target_link_libraries(lightTexTest dl)

add_executable(lightCasterTest demo/lightCasterTest.cpp
        ${CMAKE_SOURCE_DIR}/src/glad.c
        ${SOURCES_COMMON})
target_link_libraries(lightCasterTest glfw)
target_link_libraries(lightCasterTest dl)

add_executable(mulLightTest demo/mulLightTest.cpp
        ${CMAKE_SOURCE_DIR}/src/glad.c
        ${SOURCES_COMMON})
target_link_libraries(mulLightTest glfw)
target_link_libraries(mulLightTest dl)
target_link_libraries(mulLightTest assimp)

add_executable(assimpTest demo/assimpTest.cpp
        ${CMAKE_SOURCE_DIR}/src/glad.c
        ${SOURCES_COMMON})
target_link_libraries(assimpTest glfw)
target_link_libraries(assimpTest dl)
target_link_libraries(assimpTest assimp)

add_executable(framebufferTest demo/framebufferTest.cpp
        ${CMAKE_SOURCE_DIR}/src/glad.c
        ${SOURCES_COMMON})
target_link_libraries(framebufferTest glfw)
target_link_libraries(framebufferTest dl)
target_link_libraries(framebufferTest assimp)