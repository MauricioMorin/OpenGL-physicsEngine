#pragma once
#include "System.h"
#include "Component.h"
#include "TransformComponent.h"
#include "PhysicsComponent.h"

class PhysicsSystem : public System {
    ComponentManager& componentManager;

public:
    PhysicsSystem(ComponentManager& manager);

    void Update(float deltaTime) override;
};