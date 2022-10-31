#pragma once

#include "Vector2.h"
#include <OpenGL/gl3.h>

class RenderTexture
{
public:
    GLuint ColorAttachment;
    GLuint Id;

    void Invalidate(Vector2 size);

    void Bind();

    void Unbind();

    void Render(GLuint targetTexture, float sampleSize = 1);
};

