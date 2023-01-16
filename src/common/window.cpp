#include "window.h"
glm::vec3 calculCameraFront(double xpos, double ypos);
float calculCameraFov(double xoffset, double yoffset);

Camera Window::mCamera = Camera();

Window::Window() {
    // glfw: initialize and configure
    // ------------------------------

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    mWindow = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (mWindow == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(mWindow);
    // 设置鼠标监听
    glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // 创建回调函数
    auto mouse_callback = [](GLFWwindow* window, double xpos, double ypos) {
        mCamera.setCameraFront(calculCameraFront(xpos, ypos));
    };
    auto framebuffer_size_callback = [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    };
    auto scroll_callback = [](GLFWwindow* window, double xoffset, double yoffset) {
        mCamera.setCameraFov(calculCameraFov(xoffset, yoffset));
    };

    // 设置回调函数
    glfwSetFramebufferSizeCallback(mWindow, framebuffer_size_callback);
    glfwSetCursorPosCallback(mWindow, mouse_callback);
    glfwSetScrollCallback(mWindow, scroll_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
    glEnable(GL_DEPTH_TEST);
}

Window::~Window() {
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
}

int Window::getWidth() {
    return SCR_WIDTH;
}
int Window::getHeight() {
    return SCR_HEIGHT;
}

void Window::run(const std::function<void()> &fp) {
    while (!glfwWindowShouldClose(mWindow)) {
        // 记录时间
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        cameraSpeed = 2.5f * deltaTime;

        // input
        // -----
        processInput(mWindow);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        fp();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void Window::processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    // mCamera.setCameraFront(calculCameraFront(mousePos.x, mousePos.y));
    glm::vec3 cameraPos = mCamera.getCameraPos();
    glm::vec3 cameraFront = mCamera.getCameraFront();
    glm::vec3 cameraUp = mCamera.getCameraUp();

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    
    mCamera.updateCamera(cameraPos, cameraFront, cameraUp);
}

glm::vec3 calculCameraFront(double xpos, double ypos)
{
    static bool firstMouse = true;
    static double lastX=400.0f, lastY=300.0, yaw=-90.0f, pitch=0.0;
    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 45.0f)
        pitch = 45.0f;
    if(pitch < -45.0f)
        pitch = -45.0f;

    glm::vec3 front = glm::vec3();
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    glm::vec3 cameraFront = glm::normalize(front);
    return cameraFront;
}

float calculCameraFov(double xoffset, double yoffset)
{
    float fov = Window::mCamera.getCameraFov();
    if(fov >= 1.0f && fov <= 45.0f)
        fov -= yoffset;
    if(fov <= 1.0f)
        fov = 1.0f;
    if(fov >= 45.0f)
        fov = 45.0f;
    
    return fov;
}