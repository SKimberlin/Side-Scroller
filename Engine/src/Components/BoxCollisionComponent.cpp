#include "BoxCollisionComponent.h"
#include <Jolt/Physics/Collision/Shape/BoxShape.h>

BoxCollisionComponent::BoxCollisionComponent(const Vector3& halfExtents) :
    m_HalfExtents(halfExtents)
{
    m_Shape = new JPH::BoxShape({ halfExtents.x, halfExtents.y, halfExtents.z });
}

BoxCollisionComponent::~BoxCollisionComponent()
{
    delete m_Shape;
}

void BoxCollisionComponent::SetHalfExtents(const Vector3& halfExtents)
{
    m_HalfExtents = halfExtents;
    delete m_Shape;
    m_Shape = new JPH::BoxShape({ halfExtents.x, halfExtents.y, halfExtents.z });
}

Vector3 BoxCollisionComponent::GetHalfExtents() const
{
    return m_HalfExtents;
}