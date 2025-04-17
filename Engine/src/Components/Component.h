#pragma once

#include "ILifeCycle.h"

class GameObject;

class Component : public ILifeCycle
{
public:
    GameObject* m_GameObject = nullptr;
    bool m_IsActive = true;

    virtual ~Component() = default;
};