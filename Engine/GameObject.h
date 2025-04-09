#pragma once
#include "Component.h"
#include <string>
#include <vector>
#include <memory>

class GameObject
{
public:
	bool m_IsActive;
	class Scene* m_Scene;
	std::string m_Name;
	std::string m_Tag;
	bool m_IsDestroyed;

	std::vector<std::unique_ptr<GameObject>> m_Children;
	std::vector<std::unique_ptr<Component>> m_Components;

public:

	virtual void OnStart() {};
	virtual void OnUpdate();
	virtual ~GameObject() {};

	virtual std::string ToString() {};

	static void OnDestroy() {};

};