#include <memory>
#include <vector>
#include <iostream>
#include "Components.h"

class Entitiy
{
private:
    std::vector<std::unique_ptr<Component>> components;
public:
    template<typename T,typename... Args>
    void addComponent(Args&&... args)
    {
        if constexpr (sizeof...(args) == 0) {
            throw std::invalid_argument("addComponent(argument) must be called with at least one argument.");
        } else {
            components.emplace_back(std::make_unique<T>(std::forward<Args>(args)...));
        }
    }
    template<typename T>
    T* getComponent()
    {
        for(const auto& component : components)
            if(T* casted_component = dynamic_cast<T*>(component.get()))
                return casted_component;
        return nullptr;
    }
};
