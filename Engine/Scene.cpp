#include "Scene.h"

void Scene::OnStart()
{

}

void Scene::OnUpdate()
{
	for (auto gameObject = gameObjects.begin(); gameObject != gameObjects.end(); ((*gameObject)->m_IsDestroyed) ? gameObjects.erase(gameObject) : ++gameObject)
	{
		if ((*gameObject)->m_IsActive) (*gameObject)->OnUpdate();
	}
}

void Scene::AddGameObject(std::unique_ptr<GameObject> gameObject)
{
	gameObject->m_Scene = this;
	gameObjects.push_back(std::move(gameObject));
}