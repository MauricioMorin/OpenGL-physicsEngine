
#pragma once
#include "Component.h"
#include <glm/glm.hpp>  // Include GLM for vector and matrix math
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>

struct PhysicsComponent : public Component {

    glm::vec3 velocity; //movement speed
    glm::vec3 acceleration; //acceleration
    float mass;
    float bouncyness;
    float drag;

    // Constructor with default values
    PhysicsComponent(const float& m = 0.0f,
        const glm::vec3& vel = glm::vec3(0.0f),
        const glm::vec3& acc = glm::vec3(0.0f),
        const float& bounce = 1.0f,
        const float& drg = 0.0f)
        : mass(m),velocity(vel), acceleration(acc), bouncyness(bounce), drag(drg){
    }

};