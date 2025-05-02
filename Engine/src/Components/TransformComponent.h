#pragma once
#include "Component.h"
#include "raylib.h"
#include "raymath.h"

class TransformComponent : public Component
{
private:
	Transform m_Transform;

public:
	TransformComponent()
	{
		m_Transform.translation = { 0.0f, 0.0f, 0.0f };
		m_Transform.rotation = { 0.0f, 0.0f, 0.0f, 1.0f };
		m_Transform.scale = { 1.0f, 1.0f, 1.0f };
	}

	TransformComponent(Vector3 translation, Vector3 rotation, Vector3 scale)
	{
		m_Transform.translation = translation;
		m_Transform.rotation = QuaternionFromEuler(rotation.x, rotation.y, rotation.z);
		m_Transform.scale = scale;
	}

	TransformComponent(Vector3 translation, Quaternion rotation, Vector3 scale)
	{
		m_Transform.translation = translation;
		m_Transform.rotation = rotation;
		m_Transform.scale = scale;
	}

	Vector3 GetForward() const;
	Vector3 GetUp() const;
	Vector3 GetRight() const;
	Vector3 GetTranslation() const;
	Vector3 GetScale() const;
	Quaternion GetRotation() const;
	Vector3 GetRotationDegrees() const;

	void SetTranslation(const Vector3& translation);
	void SetRotation(const Quaternion& rotation);

	void Translate(const Vector3& offset);
	void Rotate(const Vector3& rotation);
	void Scale(const Vector3& scaleFactor);
	void LookAt(const Vector3& target);


	Matrix GetTransformMatrix() const;
};