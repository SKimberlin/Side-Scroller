#include "TransformComponent.h"
#include "raymath.h"

Vector3 TransformComponent::GetForward() const
{
    Matrix mat = GetTransformMatrix();
    return { mat.m8, mat.m9, mat.m10 };
}

Vector3 TransformComponent::GetUp() const
{
    Matrix mat = GetTransformMatrix();
    return { mat.m4, mat.m5, mat.m6 };
}

Vector3 TransformComponent::GetRight() const
{
    Matrix mat = GetTransformMatrix();
    return { mat.m0, mat.m1, mat.m2 };
}

void TransformComponent::Translate(const Vector3& offset)
{
    m_Transform.translation = Vector3Add(m_Transform.translation, offset);
}

void TransformComponent::Rotate(const Vector3& rotation)
{
    Quaternion deltaRotation = QuaternionFromEuler(rotation.x * DEG2RAD, rotation.y * DEG2RAD, rotation.z * DEG2RAD);

    m_Transform.rotation = QuaternionMultiply(m_Transform.rotation, deltaRotation);
}

void TransformComponent::LookAt(const Vector3& target)
{
    Vector3 forward = Vector3Normalize(Vector3Subtract(target, m_Transform.translation));

    Vector3 up = { 0.0f, 1.0f, 0.0f };

    Matrix lookAtMatrix = MatrixLookAt(m_Transform.translation, target, up);

    m_Transform.rotation = QuaternionFromMatrix(lookAtMatrix);
}


void TransformComponent::Scale(const Vector3& scaleFactor)
{
    m_Transform.scale = Vector3Multiply(m_Transform.scale, scaleFactor);
}

Matrix TransformComponent::GetTransformMatrix() const
{
	Matrix translation = MatrixTranslate(m_Transform.translation.x, m_Transform.translation.y, m_Transform.translation.z);
	Matrix rotation = QuaternionToMatrix(m_Transform.rotation);
	Matrix scale = MatrixScale(m_Transform.scale.x, m_Transform.scale.y, m_Transform.scale.z);

	return MatrixMultiply(MatrixMultiply(scale, rotation), translation);
}
