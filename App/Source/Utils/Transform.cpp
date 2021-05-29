#include "pch.h"
#include "Transform.h"
#include "Radian.h"

Transform::Transform() :
	m_Position(0.0f),
	m_Scale(1.0f),
	m_EulerRotation(0.0f),
	m_Quaternion(glm::identity<glm::quat>()),
	m_Transform(glm::identity<glm::mat4>())
{
}

glm::vec3& Transform::GetPosition()
{
	return m_Position;
}

const glm::vec3& Transform::GetPosition() const
{
	return m_Position;
}

void Transform::SetPosition(float x, float y, float z)
{
	m_Position = glm::vec3(x, y, z);
	RecalculateTransform();
}

void Transform::SetPosition(const glm::vec3& position)
{
	m_Position = position;
	RecalculateTransform();
}

void Transform::Move(float x, float y, float z)
{
	m_Position += glm::vec3(x, y, z);
	RecalculateTransform();
}

void Transform::Move(const glm::vec3& amount)
{
	m_Position += amount;
	RecalculateTransform();
}

void Transform::MoveX(float amount)
{
	m_Position.x += amount;
	RecalculateTransform();
}

void Transform::MoveY(float amount)
{
	m_Position.y += amount;
	RecalculateTransform();
}

void Transform::MoveZ(float amount)
{
	m_Position.z += amount;
	RecalculateTransform();
}

glm::vec3& Transform::GetScale()
{
	return m_Scale;
}

const glm::vec3& Transform::GetScale() const
{
	return m_Scale;
}

void Transform::SetScale(float x, float y, float z)
{
	m_Scale = glm::vec3(x, y, z);
	RecalculateTransform();
}

void Transform::SetScale(const glm::vec3& scale)
{
	m_Scale = scale;
	RecalculateTransform();
}

void Transform::Scale(float x, float y, float z)
{
	m_Scale += glm::vec3(x, y, z);
	RecalculateTransform();
}

void Transform::Scale(const glm::vec3& amount)
{
	m_Scale += amount;
	RecalculateTransform();
}

void Transform::ScaleX(float amount)
{
	m_Scale.x += amount;
	RecalculateTransform();
}

void Transform::ScaleY(float amount)
{
	m_Scale.y += amount;
	RecalculateTransform();
}

void Transform::ScaleZ(float amount)
{
	m_Scale.z += amount;
	RecalculateTransform();
}

glm::vec3& Transform::GetRotation()
{
	return m_EulerRotation;
}

const glm::vec3& Transform::GetRotation() const
{
	return m_EulerRotation;
}

void Transform::SetRotation(const Degree& angleX, const Degree& angleY, const Degree& angleZ)
{
	m_EulerRotation = { angleX, angleY, angleZ };

	glm::vec3 temp = {
		angleX.ToRadians(),
		angleY.ToRadians(),
		angleZ.ToRadians()
	};

	m_Quaternion = glm::quat(temp);
	RecalculateTransform();
}

void Transform::SetRotation(const glm::vec3& degrees)
{
	m_EulerRotation = degrees;
	glm::vec3 temp = {
		glm::radians(m_EulerRotation.x),
		glm::radians(m_EulerRotation.y),
		glm::radians(m_EulerRotation.z)
	};
	m_Quaternion = glm::quat(temp);
	RecalculateTransform();
}

void Transform::SetRotation(const glm::vec3& axisOfRotation, const Degree& angle)
{
	auto axis = glm::normalize(axisOfRotation);
	m_Quaternion = glm::angleAxis(glm::radians<float>(angle), axis);;
	auto toEuler = glm::eulerAngles(m_Quaternion);
	m_EulerRotation = {
		glm::degrees(toEuler.x),
		glm::degrees(toEuler.y),
		glm::degrees(toEuler.z)
	};
	RecalculateTransform();
}

void Transform::Rotate(const Degree& angleX, const Degree& angleY, const Degree& angleZ)
{
	m_EulerRotation = { angleX, angleY, angleZ };

	glm::quat temp(glm::vec3(
		angleX.ToRadians(),
		angleY.ToRadians(),
		angleZ.ToRadians()));

	m_Quaternion *= temp;
	RecalculateTransform();
}

void Transform::Rotate(const glm::vec3& axisOfRotation, const Degree& angle)
{
	auto axis = glm::normalize(axisOfRotation);
	auto temp = glm::angleAxis(glm::radians<float>(angle), axis);
	m_Quaternion *= temp;
	auto toEuler = glm::eulerAngles(m_Quaternion);
	m_EulerRotation = {
		glm::degrees(toEuler.x),
		glm::degrees(toEuler.y),
		glm::degrees(toEuler.z)
	};
	RecalculateTransform();
}

void Transform::RotateX(const Degree& amount)
{
	m_EulerRotation.x = m_EulerRotation.x + amount;

	glm::quat temp(glm::vec3(
		amount.ToRadians(),
		0,
		0));

	m_Quaternion *= temp;
	RecalculateTransform();
}

void Transform::RotateY(const Degree& amount)
{
	m_EulerRotation.y = m_EulerRotation.y + amount;

	glm::quat temp(glm::vec3(
		0,
		amount.ToRadians(),
		0));

	m_Quaternion *= temp;
	RecalculateTransform();
}

void Transform::RotateZ(const Degree& amount)
{
	m_EulerRotation.z = m_EulerRotation.z + amount;

	glm::quat temp(glm::vec3(
		0,
		0,
		amount.ToRadians()));

	m_Quaternion *= temp;
	RecalculateTransform();
}

glm::mat4& Transform::GetTransform()
{
	return m_Transform;
}

const glm::mat4& Transform::GetTransform() const
{
	return m_Transform;
}

void Transform::RecalculateTransform()
{
	auto translateMatrix = glm::translate(glm::mat4(1.0f), m_Position);
	auto rotationMatrix = glm::mat4_cast(m_Quaternion);
	auto scaleMatrix = glm::scale(glm::mat4(1.0f), m_Scale);
	m_Transform = translateMatrix * rotationMatrix * scaleMatrix;
}