#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <functional>

#include "common/camera.h"

using namespace glm;
using namespace std;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

class Window
{
private:
    GLFWwindow* mWindow;
    float deltaTime = 0.0f; // 当前帧与上一帧的时间差
    float lastFrame = 0.0f; // 上一帧的时间
    float cameraSpeed = 0.0f; // 摄像机移动速度

    // c++中由于函数调用时隐式增加了this指针，所以在callback调用时导致参数个数不一致而出错。
    // 成员函数作为回调，可以采用static的方式传递。因为static没有使用this。
    // static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    void processInput(GLFWwindow *window);
    void framebuffer_size_callback2(GLFWwindow* window, int width, int height) {};
public:
    static Camera mCamera;

    Window(/* args */);
    ~Window();

    int getWidth();
    int getHeight();

    void run(const std::function<void()> &fp);
};