#pragma once
#include <vector>
#include "Entity.h"

class System {
protected:
    std::vector<Entity> entities;

public:
    virtual ~System() = default;

    void AddEntity(Entity entity) { entities.push_back(entity); }
    void RemoveEntity(Entity entity) {
        entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
    }

    virtual void Update(float deltaTime) = 0;  // Pure virtual for logic.
};