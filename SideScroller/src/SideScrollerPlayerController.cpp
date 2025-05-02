#pragma message("Compiling SideScrollerPlayerController.cpp")
#include "SideScrollerPlayerController.h"
#include "TransformComponent.h"
#include "RigidBodyComponent.h"
#include "GameObject.h"

void SideScrollerPlayerController::OnStart()
{
	m_RigidBody = m_GameObject->GetComponent<RigidBodyComponent>();
}
void SideScrollerPlayerController::OnUpdate()
{
	if (IsKeyDown(KEY_A)) {};
	if (IsKeyDown(KEY_D)) {};
	if (IsKeyDown(KEY_W)) {};
	if (IsKeyDown(KEY_S)) {};
}