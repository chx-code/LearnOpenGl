#include "Scene.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "input.h"

int main() {
    auto *scene = new Scene();
    Scene::mCamera.setCameraPos(vec3(0,5,10));
    Shader nanoShader = Shader(shaderPath + "/vertexShader/normalVertexShader.vs",
                                   shaderPath + "/fragmentShader/diffTexFS.frag");
    Shader groundShader = Shader(shaderPath + "/vertexShader/normalVertexShader.vs",
                                 shaderPath + "/fragmentShader/ground.frag");

    auto* nano = new Model("/Users/cuihongxin/code/open_source_project/LearnOpenGl/assets/models/nanosuit.obj");
    auto * ground = new Model("/Users/cuihongxin/code/open_source_project/LearnOpenGl/assets/models/ground.obj");

    unsigned int fbo;
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    // 之后所有的渲染操作将会渲染到当前绑定帧缓冲的附件中。由于我们的帧缓冲不是默认帧缓冲，渲染指令将不会对窗口的视觉输出有任何影响。出于这个原因，渲染到一个不同的帧缓冲被叫做离屏渲染(Off-screen Rendering)。要保证所有的渲染操作在主窗口中有视觉效果，我们需要再次激活默认帧缓冲，将它绑定到0。
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // 纹理附件，将渲染到该纹理中
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // 将它附加到帧缓冲上
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

    unsigned int rbo;
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1600, 1200);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
        cout << "GL_FRAMEBUFFER_COMPLETE SUCCESSFUL" << endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    scene->run([&](){
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 我们现在不使用模板缓冲
        glEnable(GL_DEPTH_TEST);
//        DrawScene();

// 第二处理阶段
        glBindFramebuffer(GL_FRAMEBUFFER, 0); // 返回默认
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        nanoShader.use();
        nanoShader.setMat4("view", Scene::mCamera.getView());
        nanoShader.setMat4("projection", Scene::mCamera.getProjection());
        nano->setPosition(vec3(0, 0, 0));
        nanoShader.setMat4("model", nano->getModelMatrix());
        // spotLight
        nanoShader.setLight("spotLight", Scene::mCameraSpotLight);
        nano->Draw(nanoShader);

        nano->setPosition(vec3(5.0, 0, 0));
        nanoShader.setMat4("model", nano->getModelMatrix());
        nano->Draw(nanoShader);

        groundShader.use();
        groundShader.setMat4("view", Scene::mCamera.getView());
        groundShader.setMat4("projection", Scene::mCamera.getProjection());
        groundShader.setMat4("model", ground->getModelMatrix());
        ground->Draw(groundShader);
    });

    glDeleteFramebuffers(1, &fbo);
    delete nano;
    delete ground;
    delete scene;
    return 0;
}