#pragma once

class Radian;

class Degree
{
public:
	Degree(float amount = 0.0f);
	virtual ~Degree();

	operator float();
	operator const float() const;
	Radian ToRadians();
	const Radian ToRadians() const;

	static void* operator new(size_t) = delete;
	static void* operator new[](size_t) = delete;
	static void  operator delete(void*) = delete;
	static void  operator delete[](void*) = delete;
private:
	float m_Amount;
};