#pragma once
#include <Jolt/Jolt.h>
#include <Jolt/Physics/Body/BodyInterface.h>
#include "raylib.h"

class TransformComponent;
class CollisionComponent;
class RigidBodyComponent;

class IPhysicsEngine {
public:
    virtual ~IPhysicsEngine() = default;
    virtual void Initialize() = 0;
    virtual void Shutdown() = 0;
    virtual void Update() = 0;

    virtual void StartSimulation() = 0;
    virtual void SetGravity(const Vector3& gravity) = 0;

    virtual JPH::BodyID CreateBody(TransformComponent*, CollisionComponent*, RigidBodyComponent*) = 0;
    virtual JPH::BodyInterface* GetBodyInterface() = 0;
};
