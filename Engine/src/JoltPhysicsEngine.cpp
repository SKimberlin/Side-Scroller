#include "JoltPhysicsEngine.h"
#include "TransformComponent.h"
#include "CollisionComponent.h"
#include "RigidBodyComponent.h"
#include "Jolt/RegisterTypes.h"
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Collision/Shape/EmptyShape.h>
#include <iostream>


using namespace JPH;
// --- BroadPhaseLayerInterfaceImpl Implementation ---
uint BroadPhaseLayerInterfaceImpl::GetNumBroadPhaseLayers() const
{
    return BroadPhaseLayers::NUM_LAYERS;
}

BroadPhaseLayer BroadPhaseLayerInterfaceImpl::GetBroadPhaseLayer(ObjectLayer inLayer) const
{
    switch (inLayer)
    {
    case 0:
        return BroadPhaseLayers::NON_MOVING;
    case 1:
        return BroadPhaseLayers::MOVING;
    default:
        return BroadPhaseLayer(); // Invalid layer
    }
}

const char* BroadPhaseLayerInterfaceImpl::GetBroadPhaseLayerName(BroadPhaseLayer inLayer) const
{
    switch ((BroadPhaseLayer::Type)inLayer)
    {
    case (BroadPhaseLayer::Type)BroadPhaseLayers::NON_MOVING:
        return "NON_MOVING";
    case (BroadPhaseLayer::Type)BroadPhaseLayers::MOVING:
        return "MOVING";
    default:
        return "INVALID";
    }
}

// --- ObjectVsBroadPhaseLayerFilterImpl Implementation ---
bool ObjectVsBroadPhaseLayerFilterImpl::ShouldCollide(ObjectLayer inObjectLayer, BroadPhaseLayer inBroadPhaseLayer) const
{
    return (inObjectLayer == Layers::MOVING && inBroadPhaseLayer == BroadPhaseLayers::MOVING) ||
        (inObjectLayer == Layers::MOVING && inBroadPhaseLayer == BroadPhaseLayers::NON_MOVING);
}

// --- ObjectLayerPairFilterImpl Implementation ---
bool ObjectLayerPairFilterImpl::ShouldCollide(ObjectLayer inObjectLayer1, ObjectLayer inObjectLayer2) const
{
    return true; // Allow all object layers to collide for now
}

void JoltPhysicsEngine::SetGravity(const Vector3& grav)
{
    m_PhysicsSystem->SetGravity({ grav.x, grav.y, grav.z });
}

void JoltPhysicsEngine::Initialize()
{
    RegisterDefaultAllocator();
    Factory::sInstance = new Factory();
    RegisterTypes();

    m_Allocator = new TempAllocatorImpl(10 * 1024 * 1024);
    m_JobSystem = new JobSystemThreadPool(cMaxPhysicsJobs, cMaxPhysicsBarriers, std::thread::hardware_concurrency() - 1);
    m_PhysicsSystem = new PhysicsSystem();

    m_PhysicsSystem->Init(
        1024,
        0,
        1024,
        1024,
        m_BroadPhaseLayerInterface,
        m_ObjectVsBroadPhaseLayerFilter,
        m_ObjectLayerPairFilter
    );
    m_PhysicsSystem->SetGravity({ 0.0f, -9.81f, 0.0f });

    m_BodyInterface = &m_PhysicsSystem->GetBodyInterface();
}

void JoltPhysicsEngine::Shutdown()
{
    std::cout << "Physics Engine Shut Down" << std::endl;
    m_Bodies.clear();
}

void JoltPhysicsEngine::Update()
{
    m_PhysicsSystem->Update(GetFrameTime(), 2, m_Allocator, m_JobSystem);
}

BodyID JoltPhysicsEngine::CreateBody(TransformComponent* transform, CollisionComponent* collision, RigidBodyComponent* rigidBody)
{
    if (!transform || !rigidBody)
    {
        return BodyID();
    }

    ShapeRefC shape = NULL;
    if (collision)
        shape = collision->GetCollisionShape();
    else
    {
        EmptyShapeSettings shapeSettings;
        auto shapeResult = shapeSettings.Create();
        JPH_ASSERT(!shapeResult.HasError());
        shape = shapeResult.Get();
    }


    BodyCreationSettings settings(
        shape,
        ToJolt(transform->GetTranslation()),
        ToJolt(transform->GetRotation()).Normalized(),
        rigidBody->GetMotionType() == RigidBodyComponent::MotionType::Static ? EMotionType::Static :
        rigidBody->GetMotionType() == RigidBodyComponent::MotionType::Kinematic ? EMotionType::Kinematic :
        EMotionType::Dynamic,
        Layers::MOVING
    );

    
    if (rigidBody->GetMotionType() == RigidBodyComponent::MotionType::Dynamic)
    {
        MassProperties massProperties = shape->GetMassProperties();
        massProperties.mMass = rigidBody->GetMass();
        settings.mMassPropertiesOverride = massProperties;
    }

    settings.mLinearDamping = rigidBody->GetLinearDamping();
    settings.mAngularDamping = rigidBody->GetAngularDamping();
    settings.mAllowSleeping = true;
    

    Body* body = m_BodyInterface->CreateBody(settings);
    BodyID bodyID = body->GetID();
    m_BodyInterface->AddBody(bodyID, EActivation::Activate);
    m_Bodies.push_back(bodyID);

    return bodyID;
}


BodyInterface* JoltPhysicsEngine::GetBodyInterface()
{
    return m_BodyInterface;
}

