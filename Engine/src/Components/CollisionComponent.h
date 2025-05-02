#pragma once
#include "Component.h"
#include "IPhysicsEngine.h"
#include <Jolt/Physics/Collision/Shape/Shape.h>
#include <Jolt/Jolt.h>

class CollisionComponent : public Component
{
public:
	JPH::ShapeRefC GetCollisionShape() const { return m_Shape; };

protected:
	JPH::ShapeRefC m_Shape;
};