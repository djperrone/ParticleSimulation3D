#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

namespace Novaura {


    enum class CameraMovement
    {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    class PerspectiveCamera
    {
    public:
        PerspectiveCamera();
        PerspectiveCamera(glm::vec3 position, glm::vec3 up, float yaw, float pitch);
        PerspectiveCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

        glm::mat4 GetViewMatrix();
        void ProcessKeyBoard(CameraMovement direction, float deltaTime);
        void ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch = true);
        void ProcessMouseScroll(float yOffset);
    public:
        glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 Front = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 Right;
        glm::vec3 WorldUp = Up;
        // euler Angles
        float Yaw = -90.0f;
        float Pitch = 0.0f;
        // PerspectiveCamera options
        float MovementSpeed = 4.0f;
        float MouseSensitivity = 0.1f;
        float Zoom = 45.0f;


    private:
        void UpdateCameraVectors();

    private:


    };
}
