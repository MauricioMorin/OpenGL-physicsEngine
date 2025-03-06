#include "MovementSystem.h"

MovementSystem::MovementSystem(ComponentManager& manager) : componentManager(manager) {}

void MovementSystem::Update(float deltaTime) {
    for (Entity entity : entities) {
        TransformComponent* transform = componentManager.GetComponent<TransformComponent>(entity);
        if (transform) {
            transform->position.x += 10.0f * deltaTime;
            transform->position.y += 5.0f * deltaTime;
        }
    }
}