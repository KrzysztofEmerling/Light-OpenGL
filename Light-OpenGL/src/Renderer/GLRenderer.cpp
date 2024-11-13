#include "GLRenderer.h"

namespace Graphics
{
    glm::mat4 GLRenderer::m_Projection;
    float GLRenderer::m_AspectRatio;
    GLRenderer::GLRenderer()
    {
        m_AspectRatio = 960.0f / 540.0f;
        m_Projection = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, 0.0f, 100.0f);
    }
    void GLRenderer::UpdateWindowSize(int width, int height)
    {
        GLRenderer::m_AspectRatio = (float)width / (float)height;
        GLRenderer::m_Projection = glm::ortho(0.0f, (float)width, 0.0f, (float)height, 0.0f, 100.0f);
    }
    void GLRenderer::Clear()
    {
        glCall(glClearColor(0.1f, 0.1f, 0.1f, 1.0f));
        glCall(glClear(GL_COLOR_BUFFER_BIT));
    }
    void GLRenderer::Draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader)
    { 
        vao.Bind();
        ibo.Bind();
        shader.Bind();
        glCall(glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, nullptr));
    }
    void GLRenderer::Draw(const dVertexArray& vao, const dIndexBuffer& ibo, const Shader& shader)
    {
        vao.Bind();
        ibo.Bind();
        shader.Bind();
        glCall(glDrawElements(GL_TRIANGLES, ibo.GetCount(), GL_UNSIGNED_INT, nullptr));
    }
    void GLRenderer::Draw(const std::unique_ptr<VertexArray>& vao, const std::unique_ptr<IndexBuffer>& ibo, const std::unique_ptr<Shader>& shader)
    {
        
        vao->Bind();
        ibo->Bind();
        shader->Bind();
        glCall(glDrawElements(GL_TRIANGLES, ibo->GetCount(), GL_UNSIGNED_INT, nullptr));
    }

}
