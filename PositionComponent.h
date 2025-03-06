#pragma once
#include "Component.h"

struct PositionComponent : public Component {
    float x, y, z;

    PositionComponent(float x, float y, float z) : x(x), y(y), z(z) {}
};