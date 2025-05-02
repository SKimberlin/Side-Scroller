#pragma once
#include <unordered_map>
#include <string>
#include "raylib.h"

class ModelManager {
public:
    static ModelManager& Instance();

    Model* LoadModel(const std::string& path);
    void UnloadAll(); // cleanup

private:
    ModelManager() = default;
    ~ModelManager();

    std::unordered_map<std::string, Model> m_ModelCache;
};
