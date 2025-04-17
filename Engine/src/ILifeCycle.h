#pragma once

class ILifeCycle
{
public:
	virtual void OnStart() {};
	virtual void OnUpdate() {};
	virtual void OnDestroy() {};

	virtual ~ILifeCycle() = default;
};