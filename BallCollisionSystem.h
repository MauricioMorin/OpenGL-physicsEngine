#pragma once
#include "System.h"
#include "Component.h"
#include "TransformComponent.h"
#include "BallColliderComponent.h"
#include "PhysicsComponent.h"

class BallCollisionSystem : public System {
    ComponentManager& componentManager;

public:
    BallCollisionSystem(ComponentManager& manager);

    void Update(float deltaTime) override;

    std::pair<glm::vec3, glm::vec3> computeElasticCollision3D(
        float m1, float m2,
        glm::vec3 v1, glm::vec3 v2,
        glm::vec3 p1, glm::vec3 p2
    ) {
        glm::vec3 n = glm::normalize(p2 - p1);

        // Relative velocity along the collision normal
        glm::vec3 vRel = v1 - v2;

        // Calculate the relative velocity along the collision normal
        float vRelDotN = glm::dot(vRel, n);

        // Compute the impulse scalar (corrected)
        float j = (2.0f * m1 * m2 * vRelDotN) / (m1 + m2);

        // Calculate the impulse vectors for each sphere
        glm::vec3 impulse1 = (j / m1) * n;
        glm::vec3 impulse2 = (j / m2) * n;

        // Update final velocities
        glm::vec3 v1Final = v1 - impulse1;
        glm::vec3 v2Final = v2 + impulse2;

        return { v1Final, v2Final };
    }
};