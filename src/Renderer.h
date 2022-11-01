#pragma once

#include "Component.h"

class Renderer : public Component
{
public:
    int type = 50;
public:
    void Render() override;
};
