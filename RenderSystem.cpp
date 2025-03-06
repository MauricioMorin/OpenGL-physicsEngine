#include "RenderSystem.h"
#include<map>
RenderSystem::RenderSystem(ComponentManager& manager, Shader& shader, Camera& camera) : componentManager(manager), shader(shader), camera(camera) {}

void RenderSystem::Update(float deltaTime) {

    std::map<float, Entity> sorted;

    for (Entity entity : entities) {
        TransformComponent* transform = componentManager.GetComponent<TransformComponent>(entity);
        MeshComponent* meshcomp = componentManager.GetComponent<MeshComponent>(entity);
        TransparentMeshComponent* tmeshcomp = componentManager.GetComponent<TransparentMeshComponent>(entity);

        if (transform) {
            glm::mat4 modelmatrix = transform->GetWorldTransformMatrix(componentManager);
            if (meshcomp) {
                
                meshcomp->mesh.Draw(shader, camera,
                    modelmatrix);
            }
            if (tmeshcomp) {
                float distance = glm::length(camera.Position - glm::vec3(modelmatrix[3])); //distance to camera
                sorted[distance] = entity;
            }
            
        }
    }


    //sorts transparent objects so that objects in the back get rendered first
    for (std::map<float, Entity>::reverse_iterator it = sorted.rbegin(); it != sorted.rend(); ++it)
    {
        TransformComponent* transform = componentManager.GetComponent<TransformComponent>(it->second);
        TransparentMeshComponent* tmeshcomp = componentManager.GetComponent<TransparentMeshComponent>(it->second);

        glm::mat4 modelmatrix = transform->GetWorldTransformMatrix(componentManager);
        tmeshcomp->mesh.Draw(shader, camera,
            modelmatrix);
    }
}