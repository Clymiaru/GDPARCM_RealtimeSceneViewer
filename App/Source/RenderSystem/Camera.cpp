#include "pch.h"
#include "Camera.h"

Camera::Camera(const float fov,
               const float aspectRatio) :
	m_ProjectionMatrix(1.0f),
    m_ViewMatrix(1.0f),
    m_ViewProjectionMatrix(1.0f)
{
	m_ProjectionMatrix = glm::perspective(fov, aspectRatio, m_Near, m_Far);
	RecalculateViewMatrix();
}

const glm::mat4& Camera::GetProjectionMatrix() const
{
	return m_ProjectionMatrix;
}

const glm::mat4& Camera::GetViewMatrix() const
{
	return m_ViewMatrix;
}

const glm::mat4& Camera::GetViewProjectionMatrix() const
{
	return m_ViewProjectionMatrix;
}

glm::vec3& Camera::GetPosition()
{
	return m_ModelMatrix.GetPosition();
}

const glm::vec3& Camera::GetPosition() const
{
	return m_ModelMatrix.GetPosition();
}

void Camera::SetPosition(const float x,
                         const float y,
                         const float z)
{
	m_ModelMatrix.SetPosition(x, y, z);
	RecalculateViewMatrix();
}

void Camera::SetPosition(const glm::vec3& position)
{
	m_ModelMatrix.SetPosition(position);
	RecalculateViewMatrix();
}

void Camera::SetRotation(const Degree& angleX, const Degree& angleY, const Degree& angleZ)
{
	m_Yaw = angleY;
	m_Pitch = angleX;
	m_Roll = angleZ;
	RecalculateViewMatrix();
}

void Camera::RecalculateViewMatrix()
{
	glm::vec3 position = GetPosition();
	position *= -1.0f;
	m_ViewMatrix = glm::translate(glm::mat4(1.0f), position);
	m_ViewMatrix = glm::rotate(m_ViewMatrix, m_Yaw, {0.0f, 1.0f, 0.0f});
	m_ViewMatrix = glm::rotate(m_ViewMatrix, m_Pitch, {1.0f, 0.0f, 0.0f});
	m_ViewMatrix = glm::rotate(m_ViewMatrix, m_Roll, {0.0f, 0.0f, 1.0f});
	m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
}