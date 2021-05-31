#include "pch.h"
#include "Degree.h"
#include "Radian.h"

#include <glm/glm.hpp>
Degree::Degree(float amount) :
	m_Amount(amount)
{
}

Degree::~Degree()
{
}

Degree::operator float()
{
	return m_Amount;
}

Degree::operator const float() const
{
	return m_Amount;
}

Radian Degree::ToRadians()
{
	return Radian(glm::radians(m_Amount));
}

const Radian Degree::ToRadians() const
{
	return Radian(glm::radians(m_Amount));
}