#pragma once
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <functional>

#include "common/Camera.h"
#include "common/SpotLight.h"

using namespace glm;
using namespace std;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

struct SceneConfig {
    bool objectOutlining;
};

class Scene
{
private:
    GLFWwindow* mWindow;

    float deltaTime = 0.0f; // 当前帧与上一帧的时间差
    float lastFrame = 0.0f; // 上一帧的时间
    float cameraSpeed = 0.0f; // 摄像机移动速度

    void initGlfw();
    void initSceneConfig();

    void processInput(GLFWwindow *window);
    void updateCameraSpotLight();
public:
    static Camera mCamera;
    static SpotLight mCameraSpotLight;

    SceneConfig mSceneConfig;

    Scene(/* args */);
    ~Scene();

    int getWidth();
    int getHeight();

    void run(const std::function<void()> &fp);
};