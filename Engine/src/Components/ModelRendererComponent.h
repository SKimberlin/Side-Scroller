#pragma once

#include "RendererComponent.h"
#include "raylib.h"
#include <string>

class ModelRendererComponent : public RendererComponent
{
public:
  
    void OnStart() override;
    void OnUpdate() override;
    void LoadModelFromFile(const std::string& fileName);
    void LoadTextureFromFile(const std::string& fileName);
    void OnDraw() override;
    void SetModelFile(const std::string& filename);
    void SetModelScale(float scale) { m_ModelScale = Vector3{ scale, scale, scale }; }

private:
    Model* m_Model = nullptr;
    Texture2D* m_Texture = nullptr;
    std::string m_ModelName;
    Vector3 m_ModelScale = Vector3{ 1, 1, 1 };
};
