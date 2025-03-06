#include "BallCollisionSystem.h"
#include <iostream>
BallCollisionSystem::BallCollisionSystem(ComponentManager& manager) : componentManager(manager) {}

void BallCollisionSystem::Update(float deltaTime) {
    float totalenergy = 0;

    for (size_t i = 0; i < entities.size(); ++i) {
        Entity entity1 = entities[i];
        
        TransformComponent* transform1 = componentManager.GetComponent<TransformComponent>(entity1);
        PhysicsComponent* physics1 = componentManager.GetComponent<PhysicsComponent>(entity1);
        BallColliderComponent* collider1 = componentManager.GetComponent<BallColliderComponent>(entity1);
        
        if (transform1 && physics1 && collider1) {

            glm::vec3 t1pos = transform1->position;
            float c1r = collider1->radius;
            float mass1 = physics1->mass;
            glm::vec3 vel1 = physics1->velocity;
            float epot = mass1 * abs(physics1->acceleration.y) * (t1pos.y + 5.0f - c1r);
            float ekin = 0.5f * mass1 * std::pow(glm::length(vel1), 2);
            float energy = ekin + epot;
            //std::cout << "ekin: " << ekin << std::endl;
            //std::cout << "epot: " << epot << std::endl;
            //float energy = 0.5f * mass1 * glm::length(vel1) * glm::length(vel1) + mass1 * glm::length(physics1->acceleration) * (t1pos.y + 5.0f - c1r);
            //float energy = 0.5f * 1.0f * std::pow(glm::length(vel1 + physics1->acceleration * deltaTime), 2) + 1.0f * abs(physics1->acceleration.y) * (t1pos.y + 5.0f - c1r);
            //float energy = 0.5f * mass1 * std::pow(glm::length(vel1 + physics1->acceleration), 2) + mass1 * glm::length(physics1->acceleration.y) * (t1pos.y + 5.0f - c1r);
            
            totalenergy += energy; 
            //std::cout << energy << std::endl;
            //std::cout << "heihgt: " << (t1pos.y + 5.0f - c1r) << std::endl;
            for (size_t j = i + 1; j < entities.size(); ++j) {
                Entity entity2 = entities[j];

                TransformComponent* transform2 = componentManager.GetComponent<TransformComponent>(entity2);
                PhysicsComponent* physics2 = componentManager.GetComponent<PhysicsComponent>(entity2);
                BallColliderComponent* collider2 = componentManager.GetComponent<BallColliderComponent>(entity2);

                if (transform2 && physics2 && collider2) {
                    float mass2 = physics2->mass;
                    glm::vec3 t2pos = transform2->position;
                    float c2r = collider2->radius;

                    glm::vec3 vel2 = physics2->velocity;

                    float distance = glm::distance(t1pos, t2pos);
                    if (distance <= c2r + c1r) {
                        float overlap = (c1r + c2r) - glm::length(t2pos - t1pos);

                        std::pair < glm::vec3, glm::vec3> velocities = computeElasticCollision3D(mass1, mass2, vel1, vel2, t1pos, t2pos);
                        
                        glm::vec3 correction = 0.5f * overlap * glm::normalize(t2pos - t1pos);
                        transform1->position -= correction;
                        transform2->position += correction;

                        physics1->velocity = velocities.first * physics1->bouncyness;
                        physics2->velocity = velocities.second * physics2->bouncyness;
                        //std::cout << "Pair: (" << entity1 << ", " << entity2 << ")" << std::endl;
                    }
                    //std::cout << "Pair: (" << entity1 << ", " << entity2 << ")" << std::endl;
                     
                }
            }
        }
        
    }
    std::cout << totalenergy << std::endl;
}