#include "ModelRendererComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "raymath.h"

void ModelRendererComponent::LoadModelFromFile(const std::string& fileName)
{
	m_Model = new Model(LoadModel(fileName.c_str()));
}

void ModelRendererComponent::LoadTextureFromFile(const std::string& fileName)
{
	m_Texture = new Texture2D(LoadTexture(fileName.c_str()));
	if (m_Model) m_Model->materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = (*m_Texture);
}

void ModelRendererComponent::OnUpdate()
{

}

void ModelRendererComponent::OnDraw() 
{
	if (!m_Model || !m_GameObject) return;

	auto* transform = m_GameObject->GetComponent<TransformComponent>();
	if (!transform) return;

	DrawModelEx(*m_Model, transform->GetTranslation(), Vector3{0}, 0.0f, transform->GetScale(), WHITE);
	DrawSphere(transform->GetTranslation(), 0.2f, GREEN);


}