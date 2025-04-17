#include "GameObject.h"
#include "Component.h"

void GameObject::OnStart()
{
    for (auto& component : m_Components)
    {
        component->OnStart();
    }
}

void GameObject::OnUpdate()
{
	for (auto& component : m_Components)
	{
		if (component->m_IsActive) component->OnUpdate();
	}
}

void GameObject::AddComponent(std::shared_ptr<Component> component)
{
    component->m_GameObject = this;
    m_Components.emplace_back(std::move(component));
}
