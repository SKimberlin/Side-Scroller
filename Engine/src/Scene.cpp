#include "Scene.h"
#include "RendererComponent.h"
#include "raylib.h"
#include "GameObject.h"
#include "CameraComponent.h"

void Scene::OnStart()
{
	m_PhysicsEngine = std::make_unique<PhysicsEngine>();
	m_PhysicsEngine->Initialize();
	m_Renderers.clear();
	for (auto gameObject = m_GameObjects.begin(); gameObject != m_GameObjects.end(); ((*gameObject)->m_IsDestroyed) ? m_GameObjects.erase(gameObject) : ++gameObject)
	{
		if ((*gameObject)->m_IsActive) (*gameObject)->OnStart();
	}

	SetMainCamera();
}

void Scene::OnUpdate()
{
	if (m_PhysicsEngine)
		m_PhysicsEngine->Update();

	for (auto gameObject = m_GameObjects.begin(); gameObject != m_GameObjects.end(); ((*gameObject)->m_IsDestroyed) ? m_GameObjects.erase(gameObject) : ++gameObject)
	{
		if ((*gameObject)->m_IsActive) (*gameObject)->OnUpdate();
	}
}

void Scene::OnDestroy()
{
	m_PhysicsEngine->Shutdown();
}

void Scene::AddGameObject(std::shared_ptr<GameObject> gameObject)
{
	gameObject->m_Scene = this;
	m_GameObjects.push_back(gameObject);
}

void Scene::OnDraw()
{
	BeginDrawing();
	BeginMode3D(m_CurrentCamera->camera);
	ClearBackground(BLACK);

	for (auto renderer = m_Renderers.begin(); renderer != m_Renderers.end(); ++renderer)
	{
		if ((*renderer)->m_IsActive) (*renderer)->OnDraw();
	}


	EndDrawing();
	EndMode3D();
}

void Scene::RegisterRenderer(RendererComponent* renderer)
{
	m_Renderers.push_back(renderer);
}

void Scene::UnregisterRenderer(RendererComponent* renderer)
{
	m_Renderers.erase(std::remove(m_Renderers.begin(), m_Renderers.end(), renderer), m_Renderers.end());
}

void Scene::SetMainCamera()
{
	for (auto& gameObject : m_GameObjects)
	{
		if (!gameObject || gameObject->m_IsDestroyed || !gameObject->m_IsActive)
			continue;

		CameraComponent* cam = gameObject->GetComponent<CameraComponent>();
		if (!cam)
			cam = gameObject->GetComponentInChildren<CameraComponent>();

		if (cam)
		{
			m_CurrentCamera = cam;
			return;
		}
	}

	m_CurrentCamera = nullptr;
}
