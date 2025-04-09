#include "GameObject.h"

void GameObject::OnUpdate()
{
	for (auto& component : m_Components)
	{
		if (component->isActive) component->OnUpdate();
	}
}