#include "Scene.h"
#include "Shader.h"
#include "Texture.h"
#include "input.h"

int main() {
    Scene *window = new Scene();
    Shader lightingShader = Shader("/home/caros/chx/learnOpenGl/shader/vertexShader/normalVertexShader.vs", 
        "/home/caros/chx/learnOpenGl/shader/fragmentShader/lightFragmentShader.fs");
    Shader lightingShader2 = Shader("/home/caros/chx/learnOpenGl/shader/vertexShader/normalVertexShader.vs", 
        "/home/caros/chx/learnOpenGl/shader/fragmentShader/lightFragmentShader2.fs");
    Shader lampShader = Shader("/home/caros/chx/learnOpenGl/shader/vertexShader/normalVertexShader.vs", 
        "/home/caros/chx/learnOpenGl/shader/fragmentShader/lampFragmentShader.fs");
    
    Material material = Material(vec3(1.0f, 0.5f, 0.31f), vec3(1.0f, 0.5f, 0.31f), vec3(0.5f, 0.5f, 0.5f), 32.0f);
    Light light = Light(vec3(0.0f, 0.0f, 20.0f), vec3(0.2f, 0.2f, 0.2f), vec3(0.5f, 0.5f, 0.5f), vec3(1.0f, 1.0f, 1.0f));

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(normalVertices), normalVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    // 只需要绑定VBO不用再次设置VBO的数据，因为箱子的VBO数据中已经包含了正确的立方体顶点数据
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 设置灯立方体的顶点属性（对我们的灯来说仅仅只有位置数据）
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    window->run([&](){
        // 绘制箱子
        glBindVertexArray(VAO);
        // mat4 model = mat4(1.0f);
        glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
        glm::mat4 view = window->mCamera.getView();
        glm::mat4 projection = window->mCamera.getProjection();
        glm::vec3 lightColor;
        lightColor.x = sin(glfwGetTime() * 2.0f);
        lightColor.y = sin(glfwGetTime() * 0.7f);
        lightColor.z = sin(glfwGetTime() * 1.3f);

        light.diffuse = lightColor   * glm::vec3(0.5f); // 降低影响
        light.ambient = light.diffuse * glm::vec3(0.2f); // 很低的影响

        // lightingShader.use();
        // lightingShader.setMat4("model", model);
        // lightingShader.setMat4("view", view);
        // lightingShader.setMat4("projection", projection);
        // lightingShader.setVec3("lightPos", lightPos);
        // lightingShader.setVec3("viewPos", window->mCamera.getCameraPos());
        // lightingShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        // lightingShader.setVec3("lightColor", lightColor);

        lightingShader2.use();
        lightingShader2.setMat4("model", model);
        lightingShader2.setMat4("view", view);
        lightingShader2.setMat4("projection", projection);

        lightingShader2.setVec3("viewPos", window->mCamera.getCameraPos());
        lightingShader2.setMaterial("material", material);
        lightingShader2.setLight("light", light);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        // 绘制灯
        glBindVertexArray(lightVAO);
        model = glm::mat4(1.0f);
        model = glm::translate(model, light.position);
        model = glm::scale(model, glm::vec3(0.2f));
        lampShader.use();
        lampShader.setMat4("model", model);
        lampShader.setMat4("view", view);
        lampShader.setMat4("projection", projection);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    });

    glDeleteVertexArrays(1, &VAO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &VBO);

    return 0;
}