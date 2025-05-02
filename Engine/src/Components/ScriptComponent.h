#pragma once
#include "Component.h"

class ScriptComponent : public Component
{

	virtual void OnCollisionEnter() {};
	virtual void OnCollisionStay() {};
	virtual void OnCollisionExit() {};

	virtual void OnTriggerEnter() {};
	virtual void OnTriggerStay() {};
	virtual void OnTriggerExit() {};
};