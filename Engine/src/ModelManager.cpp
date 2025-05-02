#include "ModelManager.h"

ModelManager& ModelManager::Instance() {
    static ModelManager instance;
    return instance;
}

Model* ModelManager::LoadModel(const std::string& path) {
    if (!FileExists(path.c_str()))
    {
        TraceLog(LOG_ERROR, "Model file does not exist: %s", path.c_str());
        return nullptr;
    }

    auto it = m_ModelCache.find(path);
    if (it != m_ModelCache.end()) return &it->second;

    Model model = ::LoadModel(path.c_str());
    m_ModelCache[path] = model;
    return &m_ModelCache[path];
}

ModelManager::~ModelManager() {
    UnloadAll();
}

void ModelManager::UnloadAll() {
    for (auto& [_, model] : m_ModelCache) {
        UnloadModel(model);
    }
    m_ModelCache.clear();
}
