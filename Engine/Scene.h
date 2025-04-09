#pragma once
#include "GameObject.h"
#include <list>
#include <memory>

class Scene
{
public:
	void OnStart();
	void OnUpdate();
	void AddGameObject(std::unique_ptr<GameObject> gameObject);
private:
	std::list<std::unique_ptr<GameObject>> gameObjects;
};