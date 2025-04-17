#include "Game.h"
#include "raylib.h"
#include "Scene.h"

void Game::Run()
{
    bool quit = false;
    OnStart();
    while (!quit && !WindowShouldClose())
    {

        OnUpdate();
        OnDraw();

        quit = IsKeyPressed(KEY_ESCAPE);
    }
    OnShutdown();
}

void Game::OnStart()
{
    InitWindow(m_Width, m_Height, m_Title.c_str());
    SetTargetFPS(m_TargetFPS);
    if (m_CurrentScene) m_CurrentScene->OnStart();
}

void Game::SetCurrentScene(std::shared_ptr<Scene> scene)
{
    m_CurrentScene = scene;
    if (m_CurrentScene) m_CurrentScene->OnStart();
}

void Game::SetCurrentScene(std::string& scene)
{

}

void Game::OnUpdate()
{
    if (m_CurrentScene) m_CurrentScene->OnUpdate();
}

void Game::OnDraw()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    if (m_CurrentScene) m_CurrentScene->OnDraw();
    EndDrawing();
}

void Game::OnShutdown()
{
    //if (m_CurrentScene) m_CurrentScene->OnShutdown(); // Implement OnShutdown in Scene if needed
    CloseWindow();
}