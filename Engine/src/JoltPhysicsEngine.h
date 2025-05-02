#ifndef SRC_PHYSICSENGINE_H
#define SRC_PHYSICSENGINE_H

#pragma once

#include "IPhysicsEngine.h"

#include <Jolt/Jolt.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Physics/Body/BodyInterface.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Core/Factory.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Physics/Collision/BroadPhase/BroadPhaseLayer.h>
#include <Jolt/Physics/Collision/BroadPhase/BroadPhase.h>
#include <Jolt/Math/Vec3.h>
#include <Jolt/Math/Quat.h>

#include "raylib.h"
#include <vector>
#include <memory>

class TransformComponent;
class CollisionComponent;
class RigidBodyComponent;

// Layer IDs for broadphase collision
namespace BroadPhaseLayers {
    static constexpr JPH::BroadPhaseLayer NON_MOVING(0);
    static constexpr JPH::BroadPhaseLayer MOVING(1);
    static constexpr JPH::uint NUM_LAYERS = 2;
}

namespace Layers
{
    static constexpr JPH::ObjectLayer NON_MOVING = 0;
    static constexpr JPH::ObjectLayer MOVING = 1;
    static constexpr JPH::ObjectLayer NUM_LAYERS = 2;
}

class BroadPhaseLayerInterfaceImpl : public JPH::BroadPhaseLayerInterface
{
public:
    virtual JPH::uint GetNumBroadPhaseLayers() const override;
    virtual JPH::BroadPhaseLayer GetBroadPhaseLayer(JPH::ObjectLayer inLayer) const override;
    virtual const char* GetBroadPhaseLayerName(JPH::BroadPhaseLayer inLayer) const override;
};

class ObjectVsBroadPhaseLayerFilterImpl : public JPH::ObjectVsBroadPhaseLayerFilter
{
public:
    virtual bool ShouldCollide(JPH::ObjectLayer inObjectLayer, JPH::BroadPhaseLayer inBroadPhaseLayer) const override;
};

class ObjectLayerPairFilterImpl : public JPH::ObjectLayerPairFilter
{
public:
    virtual bool ShouldCollide(JPH::ObjectLayer inObjectLayer1, JPH::ObjectLayer inObjectLayer2) const override;
};

// Function to convert your Vector3 to JPH::Vec3
inline JPH::RVec3 ToJolt(const Vector3& v)
{
    return { v.x, v.y, v.z };
}

// Function to convert your Quaternion (assuming w, x, y, z order) to JPH::Quat
inline JPH::QuatArg ToJolt(const Quaternion& q)
{
    return { q.x, q.y, q.z, q.w };
}

class JoltPhysicsEngine : public IPhysicsEngine
{
public:

    void StartSimulation() { m_PhysicsSystem->OptimizeBroadPhase(); }
private:

    JPH::TempAllocatorImpl* m_Allocator;
    JPH::JobSystemThreadPool* m_JobSystem;
    JPH::PhysicsSystem* m_PhysicsSystem;
    JPH::BodyInterface* m_BodyInterface = nullptr;
    std::vector<JPH::BodyID> m_Bodies;

    BroadPhaseLayerInterfaceImpl m_BroadPhaseLayerInterface;
    ObjectVsBroadPhaseLayerFilterImpl m_ObjectVsBroadPhaseLayerFilter;
    ObjectLayerPairFilterImpl m_ObjectLayerPairFilter;

    // Inherited via IPhysicsEngine
    void Initialize() override;
    void Shutdown() override;
    void Update() override;
    void SetGravity(const Vector3& gravity) override;
    JPH::BodyID CreateBody(TransformComponent*, CollisionComponent*, RigidBodyComponent*) override;
    JPH::BodyInterface* GetBodyInterface() override;
};

#endif // SRC_PHYSICSENGINE_H