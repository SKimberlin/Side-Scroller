#pragma once

#include "CollisionComponent.h"
#include "raylib.h"

class BoxCollisionComponent : public CollisionComponent {
public:
    BoxCollisionComponent(const Vector3& halfExtents);
    ~BoxCollisionComponent() override;
    void OnStart() override;
    void SetHalfExtents(const Vector3& halfExtents);
    Vector3 GetHalfExtents() const;

private:
    Vector3 m_HalfExtents;
};