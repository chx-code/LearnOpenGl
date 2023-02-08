#include "Scene.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "input.h"

int main() {
    auto *scene = new Scene();
    Scene::mCamera.setCameraPos(vec3(0,5,10));
    Shader nanosultShader = Shader(shaderPath + "/vertexShader/normalVertexShader.vs",
                                   shaderPath + "/fragmentShader/diffTexFS.frag");
    Shader nanosuitReflectionShader = Shader(shaderPath + "/vertexShader/normalVertexShader.vs",
                                   shaderPath + "/fragmentShader/unlitTex.frag");
    Shader reflectShader = Shader(shaderPath + "/vertexShader/normalVertexShader.vs",
                                   shaderPath + "/fragmentShader/reflect.frag");
    Shader refractShader = Shader(shaderPath + "/vertexShader/normalVertexShader.vs",
                                   shaderPath + "/fragmentShader/refract.frag");
    Shader baseShader = Shader(shaderPath + "/vertexShader/normalVertexShader.vs",
                                   shaderPath + "/fragmentShader/baseFragmentShader.fs");
    Shader groundShader = Shader(shaderPath + "/vertexShader/normalVertexShader.vs",
                               shaderPath + "/fragmentShader/ground.frag");

    auto* nanosult = new Model("/Users/cuihongxin/code/open_source_project/LearnOpenGl/assets/models/nanosuit_reflection/nanosuit.obj");
    auto * ground = new Model("/Users/cuihongxin/code/open_source_project/LearnOpenGl/assets/models/ground.obj");

    scene->run([&](){

        nanosultShader.use();
        nanosultShader.setMat4("view", Scene::mCamera.getView());
        nanosultShader.setMat4("projection", Scene::mCamera.getProjection());
        nanosult->setScale(vec3(0.99f));
        nanosultShader.setMat4("model", nanosult->getModelMatrix());
        // spotLight
        nanosultShader.setLight("spotLight", Scene::mCameraSpotLight);

        reflectShader.use();
        reflectShader.setMat4("view", Scene::mCamera.getView());
        reflectShader.setMat4("projection", Scene::mCamera.getProjection());
        reflectShader.setMat4("model", nanosult->getModelMatrix());
        reflectShader.setInt("skybox", 0);
        reflectShader.setVec3("cameraPos", Scene::mCamera.getCameraPos());

        refractShader.use();
        refractShader.setMat4("view", Scene::mCamera.getView());
        refractShader.setMat4("projection", Scene::mCamera.getProjection());
        refractShader.setMat4("model", nanosult->getModelMatrix());
        refractShader.setInt("skybox", 0);
        refractShader.setVec3("cameraPos", Scene::mCamera.getCameraPos());

        nanosuitReflectionShader.use();
        nanosuitReflectionShader.setMat4("view", Scene::mCamera.getView());
        nanosuitReflectionShader.setMat4("projection", Scene::mCamera.getProjection());
        nanosuitReflectionShader.setMat4("model", nanosult->getModelMatrix());
        nanosuitReflectionShader.setInt("skybox", 0);
        nanosuitReflectionShader.setVec3("cameraPos", Scene::mCamera.getCameraPos());

        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(0xFF);
        nanosult->Draw(nanosuitReflectionShader);

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

        groundShader.use();
        groundShader.setMat4("view", Scene::mCamera.getView());
        groundShader.setMat4("projection", Scene::mCamera.getProjection());
        groundShader.setMat4("model", ground->getModelMatrix());
        ground->Draw(groundShader);
    });

    delete nanosult;
    delete scene;
    return 0;
}