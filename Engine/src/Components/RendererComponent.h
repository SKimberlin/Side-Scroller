#pragma once
#include "Component.h"

class RendererComponent : public Component
{
public:
	void OnStart() override;
	void OnDestroy() override;
	virtual void OnDraw() {};
};