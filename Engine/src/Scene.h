#pragma once
#include <list>
#include <memory>
#include "Physics.h"
#include "ILifeCycle.h"

class GameObject;
class RendererComponent;
class CameraComponent;

class Scene : ILifeCycle
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void AddGameObject(std::shared_ptr<GameObject> gameObject);
	void OnDraw();
	void OnDestroy() override;

	void RegisterRenderer(RendererComponent* renderer);
	void UnregisterRenderer(RendererComponent* renderer);
	PhysicsEngine* GetPhysicsEngine() { return m_PhysicsEngine.get(); }
private:
	void SetMainCamera();

	std::list<std::shared_ptr<GameObject>> m_GameObjects;
	std::vector<RendererComponent*> m_Renderers;
	CameraComponent* m_CurrentCamera;
	std::unique_ptr<PhysicsEngine> m_PhysicsEngine;

};