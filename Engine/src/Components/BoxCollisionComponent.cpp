#include "BoxCollisionComponent.h"
#include <Jolt/Physics/Collision/Shape/BoxShape.h>

BoxCollisionComponent::BoxCollisionComponent(const Vector3& halfExtents) :
    m_HalfExtents(halfExtents)
{
    
}

BoxCollisionComponent::~BoxCollisionComponent()
{
    delete m_Shape;
}

void BoxCollisionComponent::OnStart()
{
    JPH::BoxShapeSettings shapeSettings(JPH::Vec3(m_HalfExtents.x, m_HalfExtents.y, m_HalfExtents.z));
    auto shapeResult = shapeSettings.Create();
    JPH_ASSERT(!shapeResult.HasError());
    m_Shape = shapeResult.Get();
}

void BoxCollisionComponent::SetHalfExtents(const Vector3& halfExtents)
{
    m_HalfExtents = halfExtents;
    delete m_Shape;
    JPH::BoxShapeSettings shapeSettings({ halfExtents.x, halfExtents.y, halfExtents.z });
    auto shapeResult = shapeSettings.Create();
    JPH_ASSERT(!shapeResult.HasError());
    m_Shape = shapeResult.Get();
}

Vector3 BoxCollisionComponent::GetHalfExtents() const
{
    return m_HalfExtents;
}