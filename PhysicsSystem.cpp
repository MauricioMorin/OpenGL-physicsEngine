#include "PhysicsSystem.h"

PhysicsSystem::PhysicsSystem(ComponentManager& manager) : componentManager(manager) {}

void PhysicsSystem::Update(float deltaTime) {
    for (Entity entity : entities) {
        TransformComponent* transform = componentManager.GetComponent<TransformComponent>(entity);
        PhysicsComponent* physics = componentManager.GetComponent<PhysicsComponent>(entity);
        if (transform && physics) {
            transform->position += physics->velocity * deltaTime + 0.5f * physics->acceleration * deltaTime * deltaTime;
            physics->velocity += physics->acceleration * deltaTime;
            physics->velocity -= physics->velocity * physics->drag * deltaTime;
        }
    }
}