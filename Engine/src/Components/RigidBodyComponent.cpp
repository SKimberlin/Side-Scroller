#include "RigidBodyComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "CollisionComponent.h"
#include "Scene.h"

RigidBodyComponent::RigidBodyComponent() :
    m_MotionType(MotionType::Dynamic), // Default to dynamic
    m_Mass(1.0f),
    m_LinearDamping(0.0f),
    m_AngularDamping(0.0f),
    m_AffectedByGravity(true),
    m_BodyCreated(false)
{
}

RigidBodyComponent::MotionType RigidBodyComponent::GetMotionType() const
{
    return m_MotionType;
}

void RigidBodyComponent::SetMotionType(MotionType motionType)
{
    m_MotionType = motionType;
}

float RigidBodyComponent::GetMass() const
{
    return m_Mass;
}

void RigidBodyComponent::SetMass(float mass)
{
    m_Mass = mass;
}

float RigidBodyComponent::GetLinearDamping() const
{
    return m_LinearDamping;
}

void RigidBodyComponent::SetLinearDamping(float damping)
{
    m_LinearDamping = damping;
}

float RigidBodyComponent::GetAngularDamping() const
{
    return m_AngularDamping;
}

void RigidBodyComponent::SetAngularDamping(float damping)
{
    m_AngularDamping = damping;
}

bool RigidBodyComponent::IsAffectedByGravity() const
{
    return m_AffectedByGravity;
}

void RigidBodyComponent::SetAffectedByGravity(bool affectedByGravity)
{
    m_AffectedByGravity = affectedByGravity;
}

void RigidBodyComponent::OnStart()
{
    if (!m_GameObject || !m_GameObject->m_Scene || m_BodyCreated)
        return;

    auto physics = m_GameObject->m_Scene->GetPhysicsEngine();
    if (!physics)
        return;

    auto* transform = m_GameObject->GetComponent<TransformComponent>();
    auto* collision = m_GameObject->GetComponent<CollisionComponent>();

    if (!transform || !collision)
    {
        return;
    }

    m_BodyID = physics->CreateBody(transform, collision, this);
    m_BodyCreated = true;
}

void RigidBodyComponent::OnUpdate()
{
    if (!m_GameObject || !m_GameObject->m_Scene)
        return;

    auto physics = m_GameObject->m_Scene->GetPhysicsEngine();
    if (!physics)
        return;

    JPH::BodyInterface& bodyInterface = physics->GetBodyInterface();

    if (!bodyInterface.IsActive(m_BodyID))
        return;

    auto* transform = m_GameObject->GetComponent<TransformComponent>();
    if (!transform)
        return;

    JPH::RVec3 pos;
    JPH::Quat rot;

    bodyInterface.GetPositionAndRotation(m_BodyID, pos, rot);

    transform->SetTranslation({ (float)pos.GetX(), (float)pos.GetY(), (float)pos.GetZ() });
    transform->SetRotation({ rot.GetX(), rot.GetY(), rot.GetZ(), rot.GetW() });
}