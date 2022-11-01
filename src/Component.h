#pragma once

class Component
{
public:
    Component();

public:
    int Id;
    int Type = 40;
public:
    virtual void Render();
};
