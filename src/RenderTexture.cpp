#include "RenderTexture.h"
#include <OpenGL/gl3.h>

void RenderTexture::Invalidate(Vector2 size)
{
    glGenFramebuffers(1, &Id);

    glBindFramebuffer(GL_FRAMEBUFFER, Id);

    glGenTextures(1, &ColorAttachment);
    glBindTexture(GL_TEXTURE_2D, ColorAttachment);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ColorAttachment, 0);


    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        // Debug.Log("RENDER TEXTURE ERROR");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderTexture::Bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, Id);

}

void RenderTexture::Unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderTexture::Render(GLuint targetTexture, float sampleSize)
{
//    if (RenderTextureMaterial == null)
//    {
//        return;
//    }
//
//    //return;
//    ShaderCache.UseShader(RenderTextureMaterial.Shader);
//    // renderTextureMaterial.shader.SetVector2("u_resolution", Camera.I.size);
//    //	renderTextureMaterial.shader.SetMatrix4x4("u_mvp", GetModelViewProjection(sampleSize));
//
//    ShaderCache.BindVao(RenderTextureMaterial.Vao);
//    GL.Enable(EnableCap.Blend);
//
//
//    TextureCache.BindTexture(targetTexture);
//
//    //GL.DrawArrays(PrimitiveType.Triangles, 0, 6);
//
//    ShaderCache.BindVao(0);
//    GL.Disable(EnableCap.Blend);
}
