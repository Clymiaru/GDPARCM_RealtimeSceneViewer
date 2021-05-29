#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include "Utils/Degree.h"

class Transform
{
public:
	Transform();

	glm::vec3& GetPosition();
	const glm::vec3& GetPosition() const;

	void SetPosition(float x,
					 float y,
					 float z);
	void SetPosition(const glm::vec3& position);

	void Move(float x,
			  float y,
			  float z);
	void Move(const glm::vec3& amount);
	void MoveX(float amount);
	void MoveY(float amount);
	void MoveZ(float amount);

	glm::vec3& GetScale();
	const glm::vec3& GetScale() const;
	void SetScale(float x,
				  float y,
				  float z);
	void SetScale(const glm::vec3& scale);

	void Scale(float x,
			   float y,
			   float z);
	void Scale(const glm::vec3& amount);
	void ScaleX(float amount);
	void ScaleY(float amount);
	void ScaleZ(float amount);

	glm::vec3& GetRotation();
	const glm::vec3& GetRotation() const;
	void SetRotation(const Degree& angleX,
					 const Degree& angleY,
					 const Degree& angleZ);
	void SetRotation(const glm::vec3& degrees);
	void SetRotation(const glm::vec3& axisOfRotation, const Degree& angle);

	void Rotate(const Degree& angleX,
				const Degree& angleY,
				const Degree& angleZ);
	void Rotate(const glm::vec3& axisOfRotation,
				const Degree& angle);
	void RotateX(const Degree& amount);
	void RotateY(const Degree& amount);
	void RotateZ(const Degree& amount);

	glm::mat4& GetTransform();
	const glm::mat4& GetTransform() const;
private:
	glm::vec3 m_Position;
	glm::vec3 m_Scale;
	glm::vec3 m_EulerRotation;
	glm::quat m_Quaternion;
	glm::mat4 m_Transform;

	void RecalculateTransform();
};