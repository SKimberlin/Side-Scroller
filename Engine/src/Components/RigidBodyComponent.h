#pragma once

#include "Component.h"
#include "Physics.h"

class RigidBodyComponent : public Component {
public:
    enum class MotionType {
        Static,
        Kinematic,
        Dynamic
    };

    RigidBodyComponent();
    ~RigidBodyComponent() override = default;

    MotionType GetMotionType() const;
    void SetMotionType(MotionType motionType);

    float GetMass() const;
    void SetMass(float mass);

    float GetLinearDamping() const;
    void SetLinearDamping(float damping);

    float GetAngularDamping() const;
    void SetAngularDamping(float damping);

    bool IsAffectedByGravity() const;
    void SetAffectedByGravity(bool affectedByGravity);

    void OnStart() override;
    void OnUpdate() override;

private:
    MotionType m_MotionType;
    float m_Mass;
    float m_LinearDamping;
    float m_AngularDamping;
    bool m_AffectedByGravity;
    bool m_BodyCreated;
    JPH::BodyID m_BodyID;
};