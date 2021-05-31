#include "pch.h"
#include "glm/glm.hpp"
#include "Radian.h"
#include "Degree.h"

Radian::Radian(float amount) :
	m_Amount(amount)
{
}

Radian::~Radian()
{
}

Radian::operator float()
{
	return m_Amount;
}

Radian::operator const float() const
{
	return m_Amount;
}

Degree Radian::ToDegrees()
{
	return Degree(glm::degrees(m_Amount));
}

const Degree Radian::ToDegrees() const
{
	return Degree(glm::degrees(m_Amount));
}