#pragma once
#include "Component.h"
#include "raylib.h"

class TransformComponent : Component
{
public:
	Transform m_Transform;

public:

	Vector3 GetForward() const;
	Vector3 GetUp() const;
	Vector3 GetRight() const;

	void Translate(const Vector3& offset);
	void Rotate(const Vector3& rotation);
	void Scale(const Vector3& scaleFactor);
	void LookAt(const Vector3& target);


	Matrix GetTransformMatrix() const;
};