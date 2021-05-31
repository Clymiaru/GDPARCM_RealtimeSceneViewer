#pragma once

#include "Utils/Transform.h"

class Camera
{
public:
	Camera(float fov, float aspectRatio);

	const glm::mat4& GetProjectionMatrix() const;
	const glm::mat4& GetViewMatrix() const;
	const glm::mat4& GetViewProjectionMatrix()const;

	glm::vec3& GetPosition();
	const glm::vec3& GetPosition() const;

	void SetPosition(float x, float y, float z);
	void SetPosition(const glm::vec3& position);

	void SetRotation(const Degree& angleX,
					 const Degree& angleY,
					 const Degree& angleZ);

private:
	glm::mat4 m_ProjectionMatrix;
	glm::mat4 m_ViewMatrix;
	Transform m_ModelMatrix;

	glm::mat4 m_ViewProjectionMatrix;

	float m_Near = 0.01f;
	float m_Far = 1000.0f;

	float m_Yaw = 0.0f;
	float m_Pitch = 0.0f;
	float m_Roll = 0.0f;

	void RecalculateViewMatrix();
};


