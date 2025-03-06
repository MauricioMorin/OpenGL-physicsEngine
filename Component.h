#pragma once
#include <unordered_map>
#include <typeindex>
#include <memory>
#include"Entity.h"
// Base class for components (optional if you need polymorphism)
class Component {
public:
    virtual ~Component() = default;
};

// Component Manager to manage different types of components.
class ComponentManager {
    using ComponentMap = std::unordered_map<std::type_index, std::unordered_map<Entity, std::unique_ptr<Component>>>;

    ComponentMap components;

public:
    template <typename T, typename... Args>
    void AddComponent(Entity entity, Args&&... args) {
        auto& componentMap = components[std::type_index(typeid(T))];
        componentMap[entity] = std::make_unique<T>(std::forward<Args>(args)...);
    }

    template <typename T>
    T* GetComponent(Entity entity) const { // Add `const` here
        auto it = components.find(std::type_index(typeid(T)));
        if (it == components.end()) return nullptr;

        const auto& componentMap = it->second; // Use const for the map
        auto entityIt = componentMap.find(entity);
        return entityIt != componentMap.end() ? static_cast<T*>(entityIt->second.get()) : nullptr;
    }

    template <typename T>
    void RemoveComponent(Entity entity) {
        auto& componentMap = components[std::type_index(typeid(T))];
        componentMap.erase(entity);
    }
};