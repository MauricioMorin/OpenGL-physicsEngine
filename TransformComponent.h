#pragma once
#include "Component.h"
#include <glm/glm.hpp>  // Include GLM for vector and matrix math
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

struct TransformComponent : public Component {
    glm::vec3 position;  // Position in world space
    glm::vec3 rotation;  // Rotation in degrees (x, y, z)
    glm::vec3 scale;     // Scale (default is 1,1,1)
    
    Entity Parent;
    std::vector<Entity> children;

    // Constructor with default values
    TransformComponent(const glm::vec3& pos = glm::vec3(0.0f),
        const glm::vec3& rot = glm::vec3(1.0f),
        const glm::vec3& scl = glm::vec3(1.0f),
        const Entity& prnt = 0)
        : position(pos), rotation(rot), scale(scl), Parent(prnt){
    }

    // Calculate the transformation matrix
    glm::mat4 GetLocalTransformMatrix() const {
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform, position);  // Apply position
        transform = glm::rotate(transform, glm::radians(rotation.x), glm::vec3(1, 0, 0));  // Rotate around X
        transform = glm::rotate(transform, glm::radians(rotation.y), glm::vec3(0, 1, 0));  // Rotate around Y
        transform = glm::rotate(transform, glm::radians(rotation.z), glm::vec3(0, 0, 1));  // Rotate around Z
        transform = glm::scale(transform, scale);  // Apply scale
        return transform;
    }

    glm::mat4 GetWorldTransformMatrix(const ComponentManager& componentManager) const {
        if (Parent == 0) {
            return GetLocalTransformMatrix();
        }

        TransformComponent* parentTransform = componentManager.GetComponent<TransformComponent>(Parent);
        if (!parentTransform) {
            return GetLocalTransformMatrix();
        }

        return parentTransform->GetWorldTransformMatrix(componentManager) * GetLocalTransformMatrix();
    }

    void AddChild(Entity entity) { children.push_back(entity); }

    void RemoveChild(Entity entity) {
        children.erase(std::remove(children.begin(), children.end(), entity), children.end());
    }
};