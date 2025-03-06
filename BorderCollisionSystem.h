#pragma once
#include "System.h"
#include "Component.h"
#include "TransformComponent.h"
#include "BallColliderComponent.h"
#include "PhysicsComponent.h"

class BorderCollisionSystem : public System {
    ComponentManager& componentManager;

public:
    BorderCollisionSystem(ComponentManager& manager);

    void Update(float deltaTime) override;
};