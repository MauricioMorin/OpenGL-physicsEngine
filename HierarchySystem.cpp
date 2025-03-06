#include "HierarchySystem.h"

HierarchySystem::HierarchySystem(ComponentManager& manager) : componentManager(manager) {}

void HierarchySystem::Update(float deltaTime) {
    for (Entity entity : entities) {
        TransformComponent* transform = componentManager.GetComponent<TransformComponent>(entity);
        if (transform) {
            if (transform->Parent != 0) {
                TransformComponent* parent = componentManager.GetComponent<TransformComponent>(entity);

            }
        }
    }
}