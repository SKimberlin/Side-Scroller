#pragma once

#include "RendererComponent.h"
#include "raylib.h"
#include <string>

class ModelRendererComponent : public RendererComponent
{
public:
  
    void OnUpdate() override;
    void LoadModelFromFile(const std::string& fileName);
    void LoadTextureFromFile(const std::string& fileName);
    void OnDraw() override;

private:
    Model* m_Model = nullptr;
    Texture2D* m_Texture = nullptr;
    std::string m_ModelName;
};
