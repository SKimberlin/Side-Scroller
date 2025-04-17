#pragma once
#include "ILifeCycle.h"

#include <string>
#include <vector>
#include <memory>
#include <type_traits>
#include <typeinfo>


class Scene;
class Component;

class GameObject : public ILifeCycle
{
public:
    bool m_IsActive = true;
    Scene* m_Scene = nullptr;
    std::string m_Name;
    std::string m_Tag;
    bool m_IsDestroyed = false;

    std::vector<std::shared_ptr<GameObject>> m_Children;
    std::vector<std::shared_ptr<Component>> m_Components;

public:
    GameObject() = default;
    virtual ~GameObject() = default;
    void OnStart() override;
    void OnUpdate() override;

    void AddComponent(std::shared_ptr<Component> component);

    template<typename T>
    T* GetComponent()
    {
        static_assert(std::is_base_of_v<Component, T>, "T must be derived from Component");

        for (auto& comp : m_Components)
        {
            if (auto* casted = dynamic_cast<T*>(comp.get()))
                return casted;
        }
        return nullptr;
    }

    template<typename T>
    T* GetComponentInChildren()
    {
        T* result = GetComponent<T>();
        if (result) return result;

        for (auto& child : m_Children)
        {
            result = child->GetComponentInChildren<T>();
            if (result) return result;
        }

        return nullptr;
    }

};
