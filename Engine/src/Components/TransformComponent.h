#pragma once
#include "Component.h"
#include "raylib.h"

class TransformComponent : public Component
{
private:
	Transform m_Transform;

public:

	Vector3 GetForward() const;
	Vector3 GetUp() const;
	Vector3 GetRight() const;
	Vector3 GetTranslation() const;
	Vector3 GetScale() const;
	Quaternion GetRotation() const;

	void SetTranslation(const Vector3& translation);
	void SetRotation(const Quaternion& rotation);

	void Translate(const Vector3& offset);
	void Rotate(const Vector3& rotation);
	void Scale(const Vector3& scaleFactor);
	void LookAt(const Vector3& target);


	Matrix GetTransformMatrix() const;
};