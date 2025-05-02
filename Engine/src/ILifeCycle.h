#pragma once

class ILifeCycle
{
public:
	virtual void OnAwake() {};
	virtual void OnEnable() {};
	virtual void OnStart() {};
	virtual void OnUpdate() {};
	virtual void OnApplicationQuit() {};
	virtual void OnDisable() {};
	virtual void OnDestroy() {};

	virtual ~ILifeCycle() = default;
};