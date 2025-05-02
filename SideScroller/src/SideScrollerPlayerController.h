#pragma once
#include "ScriptComponent.h"
#include "raylib.h"

class SideScrollerPlayerController : public ScriptComponent
{
public:
	float m_MoveSpeed = 50;
	void OnStart() override;
	void OnUpdate() override;

private:
	class RigidBodyComponent* m_RigidBody;
};