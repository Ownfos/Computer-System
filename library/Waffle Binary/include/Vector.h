#ifndef VECTOR_H
#define VECTOR_H

#include <DirectXMath.h>

using DirectX::XMVECTOR;

namespace waffle
{
	class Transform;

	// Wrapper class for XMVECTOR
	class Vector
	{
	public:
		Vector() = default;
		Vector(float x, float y, float z);
		Vector(XMVECTOR data);

		//Vector& operator+=(const Vector& other);
		//Vector& operator-=(const Vector& other);
		//Vector& operator^=(const Vector& other);
		//Vector& operator*=(const Transform& other);
		float operator*(const Vector& other) const;
		Vector operator+(const Vector& other) const;
		Vector operator-(const Vector& other) const;
		Vector operator^(const Vector& other) const;
		Vector operator*(const Transform& transform) const;

		XMVECTOR Data() const;
		
		float Length() const;
		float LengthSquare() const;

		Vector Normalized() const;

	private:
		XMVECTOR data;
	};
}

#endif