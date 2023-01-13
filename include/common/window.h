#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <iostream>
#include <functional>

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

class Window
{
private:
    GLFWwindow* mWindow;
    
public:
    int up = 0;
    int down = 0;

    Window(/* args */);
    ~Window();

    int getWidth();
    int getHeight();

    void run(const std::function<void()> &fp);
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void processInput(GLFWwindow *window);
};

