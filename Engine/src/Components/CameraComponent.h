#pragma once
#include "Component.h"
#include "raylib.h"

class CameraComponent : public Component
{
public:
	Camera3D camera;
};