#pragma once
#include "Component.h"
#include "Physics.h"

class CollisionComponent : public Component
{
public:
	JPH::Shape* GetCollisionShape() const { return m_Shape; };

protected:
	JPH::Shape* m_Shape;
};