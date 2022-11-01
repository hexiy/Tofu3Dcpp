#pragma once

#include "vector"
#include "Component.h"

class GameObject
{
public:
    GameObject();

public:
    int Id;
    std::vector<Component *> Components;

    void Init();

    void Render();
};
