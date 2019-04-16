#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <iostream>

class Camera
{
public:
	enum CameraMovement { FORWARD, BACKWARD, LEFT, RIGHT };

	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 16.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f);
	~Camera();

	void processKeyBoard(const CameraMovement direction, const float deltaTime);
	glm::mat4 getViewMatrix() const;

private:
	// Camera Attributes
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;
	// Euler Angles
	float yaw;
	float pitch;
	// Camera options
	float movementSpeed;
	float mouseSensitivity;
	float zoom;

	// Calculates the front vector from the Camera's (updated) Euler Angles
	void updateCameraVectors();
};

