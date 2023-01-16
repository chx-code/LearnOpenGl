#include "shader.h"
#include "texture.h"
#include "window.h"
#include "input.h"

int main() {
    Window mWindow = Window();
    Shader coordinateShader("/home/caros/chx/learnOpenGl/shader/vertexShader/coorainateVertexShader.vs", 
                        "/home/caros/chx/learnOpenGl/shader/fragmentShader/textureFragmentShader.fs");
    Texture mTexture1("/home/caros/chx/learnOpenGl/assets/texture/container.jpg", "jpg");
    Texture mTexture2("/home/caros/chx/learnOpenGl/assets/texture/awesomeface.png", "png");

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    
    coordinateShader.use(); // 不要忘记在设置uniform变量之前激活着色器程序！
    coordinateShader.setInt("texture1", 0);
    coordinateShader.setInt("texture2", 1);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTexture1.getTexture());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, mTexture2.getTexture());

    auto draw = [&]() -> void {
        // 矩阵变换
        glm::mat4 model = glm::rotate(glm::mat4(1.0f), (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        glm::mat4 view = mWindow.mCamera.getView();
        glm::mat4 projection = mWindow.mCamera.getProjection();
        
        glBindVertexArray(VAO);
        for(unsigned int i = 0; i < 10; i++) {
            model = glm::translate(glm::mat4(1.0f), cubePositions[i]);
            float angle = 20.0f * i;
            if (i % 3 == 0) {
                model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
            } else {
                model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            }

            glm::mat4 transform = projection * view * model;
            glUniformMatrix4fv(glGetUniformLocation(coordinateShader.ID, "transform"), 1, GL_FALSE, glm::value_ptr(transform));

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

    };

    mWindow.run(draw);

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    return 0;
}