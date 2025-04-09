#pragma once

#include "ILifeCycle.h"

class GameObject;

class Component : public ILifeCycle
{
public:
    GameObject* gameObject = nullptr;
    bool isActive = true;

    virtual ~Component() = default;
};