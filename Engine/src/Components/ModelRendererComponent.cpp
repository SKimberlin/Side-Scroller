#include "ModelRendererComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "raymath.h"
#include "ModelManager.h"

void ModelRendererComponent::OnStart()
{
	m_Model = ModelManager::Instance().LoadModel(m_ModelName);
	RendererComponent::OnStart();
}

void ModelRendererComponent::SetModelFile(const std::string& fileName)
{
	m_ModelName = fileName;
}

void ModelRendererComponent::OnUpdate()
{

}

void ModelRendererComponent::OnDraw()
{
    if (!m_Model || !m_GameObject) return;

    auto* transform = m_GameObject->GetComponent<TransformComponent>();
    if (!transform) return;

    Quaternion q = transform->GetRotation();
    float angle = 2.0f * acosf(q.w);
    float sinHalfAngle = sqrtf(1.0f - q.w * q.w);

    Vector3 axis;
    if (sinHalfAngle < 0.001f)
    {
        axis = Vector3{ 0.0f, 1.0f, 0.0f };
    }
    else
    {
        axis.x = q.x / sinHalfAngle;
        axis.y = q.y / sinHalfAngle;
        axis.z = q.z / sinHalfAngle;
    }

    float angleDegrees = angle * RAD2DEG;

    DrawModelEx(*m_Model,
        transform->GetTranslation(),
        axis,
        angleDegrees,
        m_ModelScale,
        WHITE);
}
