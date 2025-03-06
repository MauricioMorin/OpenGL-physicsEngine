#pragma once
#include "System.h"
#include "Component.h"
#include "TransformComponent.h"
#include "MeshComponent.h"
#include "TransparentMeshComponent.h"
#include "Camera.h"
#include "shaderClass.h"

#include<vector>

class RenderSystem : public System {
    ComponentManager& componentManager;
    Shader& shader;
    Camera& camera;

public:
    RenderSystem(ComponentManager& manager, Shader& shader, Camera& camera);

    void Update(float deltaTime) override;
};