#include "GameObject.h"
#include "Game.h"
#include "ModelRendererComponent.h"
#include "CameraComponent.h"
#include "AnimatorComponent.h"
#include "TransformComponent.h"
#include "RigidBodyComponent.h"
#include "Scene.h"

int main(void)
{
    std::shared_ptr<GameObject> player = std::make_shared<GameObject>();
    std::shared_ptr<ModelRendererComponent> model = std::make_shared<ModelRendererComponent>();
    std::shared_ptr<CameraComponent> cam = std::make_shared<CameraComponent>();
    std::shared_ptr<TransformComponent> transform = std::make_shared<TransformComponent>();
    std::shared_ptr<RigidBodyComponent> rigidBody = std::make_shared<RigidBodyComponent>();
    player->AddComponent(rigidBody);
    player->AddComponent(transform);
    model->LoadModelFromFile("$(SolutionDir)Assets/Models/bird.obj");
    model->LoadTextureFromFile("$(SolutionDir)Assets/Textures/bird.jpg");
    cam->camera.target = Vector3{ 0, 0, 0 };
    cam->camera.position = Vector3{ 10, 2, 10 };
    cam->camera.fovy = 60.0f;
    cam->camera.up = Vector3{ 0, 1, 0 };
    cam->camera.projection = CAMERA_PERSPECTIVE;
    player->AddComponent(model);
    player->AddComponent(cam);
    std::shared_ptr<Scene> scene = std::make_shared<Scene>();
    scene->AddGameObject(player);
    std::unique_ptr<Game> game = std::make_unique<Game>();
    game->SetCurrentScene(scene);
    game->Run();
}