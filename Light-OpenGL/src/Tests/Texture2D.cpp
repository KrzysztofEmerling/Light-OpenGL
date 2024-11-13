#include "Texture2D.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

#include "../Renderer/GLRenderer.h"

namespace Tests
{
    Texture2D::Texture2D():
        m_Transform0(glm::vec2(300.0f, 100.0f)),m_Transform1(glm::vec2(700.0f, 300.0f))
    {
        float vertices[] = {
             36.13f,  36.13f, 1.0f, 1.0f,
            -36.13f,  36.13f, 0.0f, 1.0f,
            -36.13f, -36.13f, 0.0f, 0.0f, 
             36.13f, -36.13f, 1.0f, 0.0f
        };
        unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };

        glCall(glEnable(GL_BLEND));
        glCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


        m_Shader = std::make_unique <Graphics::Shader>("Resources/Shaders/Texture.shader");
        m_Texture = std::make_unique <Graphics::Texture>("Resources/Textures/logo.png");

        m_Shader->Bind();
        m_Shader->SetUniform1i("u_Texture",0);

        m_VertexArray = std::make_unique<Graphics::VertexArray>();

        m_VertexBuffer = std::make_unique<Graphics::VertexBuffer>(vertices, sizeof(vertices));
        Graphics::VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        m_IndexBuffer = std::make_unique<Graphics::IndexBuffer>(indices,6);

        m_VertexArray->AddBuffer(*m_VertexBuffer, layout);
        
    }

    Texture2D::~Texture2D()
    {
    }

    void Texture2D::OnUpdate(float deltaTime)
    {
    }

    void Texture2D::OnRender()
    {
        glm::mat4 proj = Graphics::GLRenderer::GetProjection();
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, -10, 0));

        m_Shader->Bind();
        m_Texture->Bind(0);
        m_Shader->SetUniformMat4f("u_MVP", proj * view * m_Transform0.GetModel());
        Graphics::GLRenderer::Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
        
        m_Shader->SetUniformMat4f("u_MVP", proj * view * m_Transform1.GetModel());
        Graphics::GLRenderer::Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
    }

    void Texture2D::OnImGuiRender()
    {
        m_Transform0.DrawImGui("1");
        m_Transform1.DrawImGui("2");
    }
}

