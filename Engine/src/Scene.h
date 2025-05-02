#pragma once
#include <list>
#include <vector>
#include <memory>
#include "ILifeCycle.h"

class GameObject;
class RendererComponent;
class CameraComponent;
class IPhysicsEngine;

class Scene : public ILifeCycle
{
public:
	void OnStart() override;
	void OnUpdate() override;
	void AddGameObject(std::shared_ptr<GameObject> gameObject);
	void OnDraw();
	void OnDestroy() override;

	void RegisterRenderer(RendererComponent* renderer);
	void UnregisterRenderer(RendererComponent* renderer);
	IPhysicsEngine* GetPhysicsEngine() { return m_PhysicsEngine.get(); }
private:
	void SetMainCamera();

	std::list<std::shared_ptr<GameObject>> m_GameObjects;
	std::vector<RendererComponent*> m_Renderers;
	CameraComponent* m_CurrentCamera;
	std::unique_ptr<IPhysicsEngine> m_PhysicsEngine;
	bool m_IsRunning = false;
};