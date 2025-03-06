#pragma once
#include "Component.h"
#include "Mesh.h"

struct TransparentMeshComponent : public Component {
    Mesh mesh;

    TransparentMeshComponent(const Mesh& mesh) : mesh(mesh) {}

};