#include "Scene.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "input.h"

int main() {
    auto *scene = new Scene();
    Shader nanosultShader = Shader(shaderPath + "/vertexShader/normalVertexShader.vs",
                                   shaderPath + "/fragmentShader/diffTexFS.frag");
    Shader baseShader = Shader(shaderPath + "/vertexShader/normalVertexShader.vs",
                                   shaderPath + "/fragmentShader/baseFragmentShader.fs");

    auto* nanosult = new Model("/Users/cuihongxin/code/open_source_project/LearnOpenGl/assets/models/nanosuit.obj");

    scene->run([&](){

        nanosultShader.use();
        nanosultShader.setMat4("view", Scene::mCamera.getView());
        nanosultShader.setMat4("projection", Scene::mCamera.getProjection());
        nanosult->setScale(vec3(0.99f));
        nanosultShader.setMat4("model", nanosult->getModelMatrix());
        // spotLight
        nanosultShader.setLight("spotLight", Scene::mCameraSpotLight);

        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(0xFF);
        nanosult->Draw(nanosultShader);

        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilMask(0x00);
        glDisable(GL_DEPTH_TEST);
        baseShader.use();
        baseShader.setMat4("view", Scene::mCamera.getView());
        baseShader.setMat4("projection", Scene::mCamera.getProjection());
        nanosult->setScale(vec3(1.0f));
        baseShader.setMat4("model", nanosult->getModelMatrix());
        nanosult->Draw(baseShader);
        glStencilMask(0xFF);
        glEnable(GL_DEPTH_TEST);
    });

    delete nanosult;
    delete scene;
    return 0;
}