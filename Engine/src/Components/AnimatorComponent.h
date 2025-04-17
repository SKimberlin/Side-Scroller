#pragma once

#include "Component.h"
#include "raylib.h"
#include <string>
#include <unordered_map>

class AnimatorComponent : Component
{
public:
    Model* model = nullptr;
    int animationCount = 0;

private:
    std::unordered_map<std::string, ModelAnimation*> animations;
    ModelAnimation* currentAnimation = nullptr;
    std::string currentName;
    float frame = 0;
    float speed = 12.0f;
    bool loop = true;

public:
    void AddAnimation(ModelAnimation* anim);
    void RemoveAnimation(ModelAnimation* anim);
    bool Play(const std::string& name, bool loop = true);
};
