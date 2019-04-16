#include "Camera.h"



Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
{
	this->front = glm::vec3(0.0f, 0.0f, -1.0f);
	this->movementSpeed = 12.5f;
	this->mouseSensitivity = 0.1f;
	this->zoom = 45.0f;

	this->position = position;
	this->worldUp = up;
	this->yaw = yaw;
	this->pitch = pitch;
	updateCameraVectors();
}

Camera::~Camera()
{
}

void Camera::processKeyBoard(const CameraMovement direction, const float deltaTime)
{
	float velocity = movementSpeed * deltaTime;
	if (direction == FORWARD) position += front * velocity;
	if (direction == BACKWARD) position -= front * velocity;
	if (direction == LEFT) position -= right * velocity;
	if (direction == RIGHT) position += right * velocity;
}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(position, position + front, up);
}

void Camera::updateCameraVectors()
{
	//front = glm::normalize(front);
	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}
