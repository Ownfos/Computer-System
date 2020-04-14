#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "Vector.h"

using DirectX::XMMATRIX;

namespace waffle
{
	// Wrapper class for XMMATRIX
	class Transform
	{
	public:
		Transform();
		Transform(XMMATRIX data);

		static Transform Translate(const Vector& offset);
		// Angle in radian
		static Transform Rotate(const Vector& angle);
		static Transform Scale(const Vector& scale);
		static Transform LookAt(const Vector& eye, const Vector& focus, const Vector& up = { 0.0f, 1.0f, 0.0f });
		static Transform LookTo(const Vector& eye, const Vector& direction, const Vector& up = { 0.0f, 1.0f, 0.0f });
		// Angle in radian
		static Transform Perspective(float fovy, float aspectRatio, float nearZ, float farZ);
		// View size is different from window size!
		static Transform Orthographic(float viewWidth, float viewHeight, float nearZ, float farZ);
		static Transform Inverse(const Transform& transform);

		Transform& operator*=(const Transform& other);
		Transform operator*(const Transform& other) const;

		XMMATRIX Data() const;
		// Matrices should be transposed before setting to any constant buffer
		XMMATRIX Transposed() const;

	private:
		XMMATRIX data;
	};
}

#endif