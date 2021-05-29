#pragma once
#include "glm/glm.hpp"
class Degree;
class Radian final
{
public:
	explicit Radian(float amount = 0.0f);
	virtual ~Radian();

	operator float();
	operator const float() const;
	Degree ToDegrees();
	const Degree ToDegrees() const;

	static void* operator new(size_t) = delete;
	static void* operator new[](size_t) = delete;
	static void  operator delete(void*) = delete;
	static void  operator delete[](void*) = delete;
private:
	float m_Amount;
};