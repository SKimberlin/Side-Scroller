#include "RendererComponent.h"
#include "GameObject.h"
#include "Scene.h"

void RendererComponent::OnStart()
{
	if (m_GameObject->m_Scene) m_GameObject->m_Scene->RegisterRenderer(this);
}

void RendererComponent::OnDestroy()
{
	if (m_GameObject->m_Scene) m_GameObject->m_Scene->UnregisterRenderer(this);
}