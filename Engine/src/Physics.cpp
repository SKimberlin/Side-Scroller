#include "Physics.h"
#include "TransformComponent.h"
#include "CollisionComponent.h"
#include "RigidBodyComponent.h"
#include "Jolt/RegisterTypes.h"
#include <Jolt/Physics/Body/BodyCreationSettings.h>
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

PhysicsEngine::PhysicsEngine()
{
    m_Allocator = new TempAllocatorImpl(10 * 1024 * 1024); // 10MB
    m_JobSystem = new JobSystemThreadPool(cMaxPhysicsJobs, cMaxPhysicsBarriers, std::thread::hardware_concurrency() - 1);
    m_PhysicsSystem = new PhysicsSystem();
    // Register all Jolt physics types
    Factory::sInstance = new Factory();
    RegisterTypes();

    m_PhysicsSystem->Init(
        10240,               // inMaxBodies
        0,               // inNumBodyMutexes
        10240,               // inMaxBodyPairs
        10240,               // inMaxContactConstraints
        m_BroadPhaseLayerInterface,
        m_ObjectVsBroadPhaseLayerFilter,
        m_ObjectLayerPairFilter
    );
    m_PhysicsSystem->SetGravity({ 0.0f, -9.81f, 0.0f });

    m_BodyInterface = &m_PhysicsSystem->GetBodyInterface();
}

PhysicsEngine::~PhysicsEngine()
{
    m_BodyInterface = nullptr;
}

void PhysicsEngine::Initialize()
{
    std::cout << "Physics Engine Initialized" << std::endl;
}

void PhysicsEngine::Shutdown()
{
    std::cout << "Physics Engine Shut Down" << std::endl;
    m_Bodies.clear(); // Release any held body IDs
}

void PhysicsEngine::Update()
{
    m_PhysicsSystem->Update(GetFrameTime(), 4, m_Allocator, m_JobSystem); // Integrate physics time step
}

BodyID PhysicsEngine::CreateBody(TransformComponent* transform, CollisionComponent* collision, RigidBodyComponent* rigidBody)
{
    if (!transform || !collision || !rigidBody)
    {
        std::cerr << "Error: Cannot create body, missing required components." << std::endl;
        return BodyID();
    }

    BodyCreationSettings settings(
        collision->GetCollisionShape(),
        ToJolt(transform->GetTranslation()),
        ToJolt(transform->GetRotation()),
        rigidBody->GetMotionType() == RigidBodyComponent::MotionType::Static ? EMotionType::Static :
        rigidBody->GetMotionType() == RigidBodyComponent::MotionType::Kinematic ? EMotionType::Kinematic :
        EMotionType::Dynamic,
        Layers::MOVING // Default to moving layer
    );

    MassProperties massProperties;
    if (rigidBody->GetMotionType() == RigidBodyComponent::MotionType::Dynamic)
    {
        // Calculate the mass properties from the shape.
        massProperties = collision->GetCollisionShape()->GetMassProperties();
        massProperties.mMass = rigidBody->GetMass(); // Override with the component's mass
        settings.mMassPropertiesOverride = massProperties;
    }
    else
    {
        settings.mMassPropertiesOverride = massProperties; // For static/kinematic bodies
    }

    settings.mLinearDamping = rigidBody->GetLinearDamping();
    settings.mAngularDamping = rigidBody->GetAngularDamping();
    settings.mAllowSleeping = true;

    BodyID bodyID = m_BodyInterface->CreateBody(settings)->GetID(); // Corrected return type
    m_Bodies.push_back(bodyID);
    std::cout << "Created Jolt body with ID: " << bodyID.GetIndex() << std::endl;
    return bodyID;
}

BodyInterface& PhysicsEngine::GetBodyInterface()
{
    return *m_BodyInterface;
}