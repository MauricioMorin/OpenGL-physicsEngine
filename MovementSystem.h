#pragma once
#include "System.h"
#include "Component.h"
#include "TransformComponent.h"

class MovementSystem : public System {
    ComponentManager& componentManager;

public:
    MovementSystem(ComponentManager& manager);

    void Update(float deltaTime) override;
};