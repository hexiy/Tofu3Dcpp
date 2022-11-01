#pragma once

#include <GLFW/glfw3.h>
#include "RenderTexture.h"
#include "Scene.h"

class Window
{

public:
    GLFWwindow *window;
    RenderTexture sceneRenderTexture;
public:
    int Init();

    void Run(Scene *scene);

    void SetStyle();
};