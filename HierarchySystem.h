#pragma once
#include "System.h"
#include "Component.h"
#include "TransformComponent.h"

class HierarchySystem : public System {
    ComponentManager& componentManager;

public:
    HierarchySystem(ComponentManager& manager);

    void Update(float deltaTime) override;
};