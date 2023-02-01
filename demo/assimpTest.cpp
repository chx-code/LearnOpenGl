#include "Scene.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "input.h"

int main() {
    auto *scene = new Scene();
    Shader nanosultShader = Shader(shaderPath + "/vertexShader/normalVertexShader.vs",
                                   shaderPath + "/fragmentShader/diffTexFS.frag");

    auto* nanosult = new Model("/Users/cuihongxin/code/open_source_project/LearnOpenGl/assets/models/nanosuit.obj");

    scene->run([&](){
        glm::mat4 view = Scene::mCamera.getView();
        glm::mat4 projection = Scene::mCamera.getProjection();
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down

        nanosultShader.use();
        nanosultShader.setMat4("view", view);
        nanosultShader.setMat4("projection", projection);
        nanosultShader.setMat4("model", model);
        // spotLight
        nanosultShader.setLight("spotLight", Scene::mCameraSpotLight);

        nanosult->Draw(nanosultShader);
    });

    delete nanosult;
    delete scene;
    return 0;
}