#include <Camera.h>

Camera::Camera() {

}

Camera::Camera(glm::vec3 CameraPos, glm::vec3 CameraFront, glm::vec3 CameraUp)
{
    mCameraPos = CameraPos;
    mCameraFront = CameraFront;
    mCameraUp = CameraUp;

    update();
}

void Camera::setCameraPos(glm::vec3 CameraPos)
{
    mCameraPos = CameraPos;
    update();
}

void Camera::setCameraPos(float x, float y, float z)
{
    mCameraPos = glm::vec3(x, y, z);
    update();
}

void Camera::setCameraFront(glm::vec3 CameraFront)
{
    mCameraFront = CameraFront;
    update();
}

void Camera::setCameraFront(float x, float y, float z)
{
    mCameraFront = glm::vec3(x, y, z);
    update();
}

void Camera::setCameraUp(glm::vec3 CameraUp)
{
    mCameraUp = CameraUp;
    update();
}

void Camera::setCameraUp(float x, float y, float z)
{
    mCameraUp = glm::vec3(x, y, z);
    update();
}

void Camera::setCameraFov(float Fov)
{
    mCameraFov = Fov;
    update();
}

void Camera::setCameraAspect(float Aspect)
{
    mCameraAspect = Aspect;
    update();
}

void Camera::setCameraNear(float Near)
{
    mCameraNear = Near;
    update();
}

void Camera::setCameraFar(float Far)
{
    mCameraFar = Far;
    update();
}

void Camera::updateCamera(glm::vec3 CameraPos, glm::vec3 CameraFront, glm::vec3 CameraUp)
{
    mCameraPos = CameraPos;
    mCameraFront = CameraFront;
    mCameraUp = CameraUp;
    update();
}

void Camera::update() {
    mView        = glm::lookAt(mCameraPos, mCameraPos + mCameraFront, mCameraUp);
    mProjection  = glm::perspective(glm::radians(mCameraFov), mCameraAspect, mCameraNear, mCameraFar);
}