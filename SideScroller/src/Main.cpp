#include "GameObject.h"
#include "Game.h"
#include "ModelRendererComponent.h"
#include "CameraComponent.h"
#include "AnimatorComponent.h"
#include "TransformComponent.h"
#include "RigidBodyComponent.h"
#include "BoxCollisionComponent.h"
#include "SideScrollerPlayerController.h"
#include "Scene.h"

#include <stdio.h>
#include <direct.h>
#include <stdlib.h>

int main(void)
{
    char cwd[1024];
    _getcwd(cwd, sizeof(cwd));
    TraceLog(LOG_INFO, TextFormat("Current working directory: %s", cwd));

    std::shared_ptr<Scene> scene = std::make_shared<Scene>();
    std::shared_ptr<GameObject> player = std::make_shared<GameObject>();
    std::shared_ptr<ModelRendererComponent> model = std::make_shared<ModelRendererComponent>();
    std::shared_ptr<CameraComponent> cam = std::make_shared<CameraComponent>();
    std::shared_ptr<TransformComponent> transform = std::make_shared<TransformComponent>();
    std::shared_ptr<RigidBodyComponent> rigidBody = std::make_shared<RigidBodyComponent>();
    std::shared_ptr<SideScrollerPlayerController> playerController = std::make_shared<SideScrollerPlayerController>();
    auto boxCollision = std::make_shared<BoxCollisionComponent>(Vector3{ 1.0f, 1.0f, 1.0f });
    transform->Rotate(Vector3{ -90, 90, 0 });
    player->AddComponent(transform);
    player->AddComponent(boxCollision);
    player->AddComponent(rigidBody);
    model->SetModelFile("Assets/Models/bird.obj");
    model->SetModelScale(0.1f);
    cam->camera.target = Vector3{ 0, 0, 0 };
    cam->camera.position = Vector3{ 0, 2, 10 };
    cam->camera.fovy = 60.0f;
    cam->camera.up = Vector3{ 0, 1, 0 };
    cam->camera.projection = CAMERA_PERSPECTIVE;
    player->AddComponent(model);
    player->AddComponent(cam);
    player->AddComponent(playerController);
    scene->AddGameObject(player);

    // Add Floor
    std::shared_ptr<GameObject> floor = std::make_shared<GameObject>();
    std::shared_ptr<ModelRendererComponent> floorModel = std::make_shared<ModelRendererComponent>();
    std::shared_ptr<TransformComponent> floorTransform = std::make_shared<TransformComponent>(Vector3{0, -5, 0}, Vector3{0, 0, 0}, Vector3{1});
    std::shared_ptr<BoxCollisionComponent> floorCollision = std::make_shared<BoxCollisionComponent>(Vector3{3.0f, 1.0f, 3.0f});
    std::shared_ptr<RigidBodyComponent> floorRigidBody = std::make_shared<RigidBodyComponent>();
    floorModel->SetModelFile("Assets/Models/cube.obj");
    floorModel->SetModelScale(1.5f);
    floorRigidBody->SetAffectedByGravity(false);
    floorRigidBody->SetMotionType(RigidBodyComponent::MotionType::Static);

    floor->AddComponent(floorModel);
    floor->AddComponent(floorTransform);
    floor->AddComponent(floorCollision);
    floor->AddComponent(floorRigidBody);
    scene->AddGameObject(floor);
    std::unique_ptr<Game> game = std::make_unique<Game>();
    game->SetCurrentScene(scene);
    game->Run();
}