#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

class Camera
{
private:
    /* data */
    glm::vec3 mCameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
    glm::vec3 mCameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 mCameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
    float mCameraFov = 45.0f;
    float mCameraAspect = 1.3333f;
    float mCameraNear = 0.1f;
    float mCameraFar  = 100.0f;

    glm::mat4 mView        = glm::lookAt(mCameraPos, mCameraPos + mCameraFront, mCameraUp);
    glm::mat4 mProjection  = glm::perspective(glm::radians(mCameraFov), mCameraAspect, mCameraNear, mCameraFar);
public:
    Camera();
    Camera(glm::vec3 CameraPos, glm::vec3 CameraFront, glm::vec3 CameraUp);
    ~Camera();

    void setCameraPos(glm::vec3 CameraPos);
    void setCameraPos(float x, float y, float z);
    void setCameraFront(glm::vec3 CameraPos);
    void setCameraFront(float x, float y, float z);
    void setCameraUp(glm::vec3 CameraPos);
    void setCameraUp(float x, float y, float z);
    void setCameraFov(float Fov);
    void setCameraAspect(float Aspect);
    void setCameraNear(float Near);
    void setCameraFar(float Far);

    glm::vec3 getCameraPos() const { return mCameraPos; }
    glm::vec3 getCameraFront() const { return mCameraFront; }
    glm::vec3 getCameraUp() const { return mCameraUp; }
    float getCameraFov() const { return mCameraFov; }
    float getCameraAspect() const { return mCameraAspect; }
    float getCameraNear() const { return mCameraNear; }
    float getCameraFar() const { return mCameraFar; }
    glm::mat4 getView() const { return mView; }
    glm::mat4 getProjection() const { return mProjection; }

    void updateCamera(glm::vec3 CameraPos, glm::vec3 mCameraFront, glm::vec3 mCameraUp);
};
