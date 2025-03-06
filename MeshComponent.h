#pragma once
#include "Component.h"
#include "Mesh.h"

struct MeshComponent : public Component {
    Mesh mesh;

    MeshComponent(const Mesh& mesh) : mesh(mesh) {}

};