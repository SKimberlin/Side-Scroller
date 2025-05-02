#pragma once
#include "ILifeCycle.h"
#include <memory>
#include <string>

class Scene;

class Game : public ILifeCycle
{
public:
	void Run();
	void OnStart() override;
	void SetCurrentScene(std::shared_ptr<Scene> scene, bool start = false);
	void SetCurrentScene(std::string& scene);
	void OnUpdate() override;
	void OnDraw();
	void OnShutdown();

private:
	int m_Width = 800;
	int m_Height = 600;
	std::string m_Title = "Base";
	int m_TargetFPS = 60;

protected:
	std::shared_ptr<Scene> m_CurrentScene;
};