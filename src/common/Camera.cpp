#include <Camera.h>

Camera::Camera(/* args */)
{
}

Camera::Camera(glm::vec3 CameraPos, glm::vec3 CameraFront, glm::vec3 CameraUp)
{
    mCameraPos = CameraPos;
    mCameraFront = CameraFront;
    mCameraUp = CameraUp;

    mView = glm::lookAt(mCameraPos, mCameraPos + mCameraFront, mCameraUp);
}

Camera::~Camera()
{
}

void Camera::setCameraPos(glm::vec3 CameraPos)
{
    mCameraPos = CameraPos;
    mView = glm::lookAt(mCameraPos, mCameraPos + mCameraFront, mCameraUp);
}

void Camera::setCameraPos(float x, float y, float z)
{
    mCameraPos = glm::vec3(x, y, z);
    mView = glm::lookAt(mCameraPos, mCameraPos + mCameraFront, mCameraUp);
}

void Camera::setCameraFront(glm::vec3 CameraFront)
{
    mCameraFront = CameraFront;
    mView = glm::lookAt(mCameraPos, mCameraPos + mCameraFront, mCameraUp);
}

void Camera::setCameraFront(float x, float y, float z)
{
    mCameraFront = glm::vec3(x, y, z);
    mView = glm::lookAt(mCameraPos, mCameraPos + mCameraFront, mCameraUp);
}

void Camera::setCameraUp(glm::vec3 CameraUp)
{
    mCameraUp = CameraUp;
    mView = glm::lookAt(mCameraPos, mCameraPos + mCameraFront, mCameraUp);
}

void Camera::setCameraUp(float x, float y, float z)
{
    mCameraUp = glm::vec3(x, y, z);
    mView = glm::lookAt(mCameraPos, mCameraPos + mCameraFront, mCameraUp);
}

void Camera::setCameraFov(float Fov)
{
    mCameraFov = Fov;
}

void Camera::setCameraAspect(float Aspect)
{
    mCameraAspect = Aspect;
}

void Camera::setCameraNear(float Near)
{
    mCameraNear = Near;
}

void Camera::setCameraFar(float Far)
{
    mCameraFar = Far;
}

void Camera::updateCamera(glm::vec3 CameraPos, glm::vec3 mCameraFront, glm::vec3 mCameraUp)
{
    mCameraPos = CameraPos;
    mCameraFront = mCameraFront;
    mCameraUp = mCameraUp;
    mView = glm::lookAt(mCameraPos, mCameraPos + mCameraFront, mCameraUp);
}
