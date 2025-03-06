#pragma once
#include "Component.h"

struct BallColliderComponent : public Component {

    float radius;
    // Constructor with default values
    BallColliderComponent(const float& r = 1.0f): radius(r){
    }

};