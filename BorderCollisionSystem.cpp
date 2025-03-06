#include "BorderCollisionSystem.h"
#include <iostream>
BorderCollisionSystem::BorderCollisionSystem(ComponentManager& manager) : componentManager(manager) {}

void BorderCollisionSystem::Update(float deltaTime) {
    for (Entity entity : entities) {
        TransformComponent* transform = componentManager.GetComponent<TransformComponent>(entity);
        PhysicsComponent* physics = componentManager.GetComponent<PhysicsComponent>(entity);
        BallColliderComponent* collider = componentManager.GetComponent<BallColliderComponent>(entity);
        
        if (transform && physics) {
            if (collider) {
                float bouncyness = physics->bouncyness;
                float r = collider->radius;
                glm::vec3 startPosition = transform->position;
                glm::vec3 endPosition = startPosition + physics->velocity * deltaTime + 0.5f * physics->acceleration * deltaTime * deltaTime;

                // Check and handle collisions for each boundary
                if (endPosition.y < -(5.0f - r)) {
                    if (physics->velocity.y > -0.01f) {
                        physics->velocity.y = 0.0f;
                        transform->position.y = -(5.0f - r);
                        std::cout << "skibidi skibidi sigma" << std::endl;
                    }
                    else {
                        float t = (-(5.0f - r) - startPosition.y) / physics->velocity.y;
                        transform->position = startPosition + physics->velocity * t + 0.5f * physics->acceleration * t * t;
                        physics->velocity += physics->acceleration * t;
                        physics->velocity.y *= -bouncyness;

                        float remainingTime = deltaTime - t;
                        transform->position += physics->velocity * remainingTime + 0.5f * physics->acceleration * remainingTime * remainingTime;
                        physics->velocity += physics->acceleration * remainingTime;
                    }
                    
                    if (physics->velocity.y < 0.1f) {
                        physics->velocity.y = 0.0f;
                        transform->position.y = -(5.0f - r);
                    }
                }
                if (endPosition.y > (5.0f - r)) {
                    float t = ((5.0f - r) - startPosition.y) / physics->velocity.y;
                    transform->position = startPosition + physics->velocity * t + 0.5f * physics->acceleration * t * t;
                    physics->velocity += physics->acceleration * t;
                    physics->velocity.y *= -bouncyness;

                    float remainingTime = deltaTime - t;
                    transform->position += physics->velocity * remainingTime + 0.5f * physics->acceleration * remainingTime * remainingTime;
                    physics->velocity += physics->acceleration * remainingTime;
                }

                if (endPosition.x < -(5.0f - r)) {
                    float t = (-(5.0f - r) - startPosition.x) / physics->velocity.x;
                    transform->position = startPosition + physics->velocity * t + 0.5f * physics->acceleration * t * t;
                    physics->velocity += physics->acceleration * t;
                    physics->velocity.x *= -bouncyness;

                    float remainingTime = deltaTime - t;
                    transform->position += physics->velocity * remainingTime + 0.5f * physics->acceleration * remainingTime * remainingTime;
                    physics->velocity += physics->acceleration * remainingTime;
                }
                if (endPosition.x > (5.0f - r)) {
                    float t = ((5.0f - r) - startPosition.x) / physics->velocity.x;
                    transform->position = startPosition + physics->velocity * t + 0.5f * physics->acceleration * t * t;
                    physics->velocity += physics->acceleration * t;
                    physics->velocity.x *= -bouncyness;

                    float remainingTime = deltaTime - t;
                    transform->position += physics->velocity * remainingTime + 0.5f * physics->acceleration * remainingTime * remainingTime;
                    physics->velocity += physics->acceleration * remainingTime;
                }

                if (endPosition.z < -(5.0f - r)) {
                    float t = (-(5.0f - r) - startPosition.z) / physics->velocity.z;
                    transform->position = startPosition + physics->velocity * t + 0.5f * physics->acceleration * t * t;
                    physics->velocity += physics->acceleration * t;
                    physics->velocity.z *= -bouncyness;

                    float remainingTime = deltaTime - t;
                    transform->position += physics->velocity * remainingTime + 0.5f * physics->acceleration * remainingTime * remainingTime;
                    physics->velocity += physics->acceleration * remainingTime;
                }
                if (endPosition.z > (5.0f - r)) {
                    float t = ((5.0f - r) - startPosition.z) / physics->velocity.z;
                    transform->position = startPosition + physics->velocity * t + 0.5f * physics->acceleration * t * t;
                    physics->velocity += physics->acceleration * t;
                    physics->velocity.z *= -bouncyness;

                    float remainingTime = deltaTime - t;
                    transform->position += physics->velocity * remainingTime + 0.5f * physics->acceleration * remainingTime * remainingTime;
                    physics->velocity += physics->acceleration * remainingTime;
                }


            }
        }
    }
}