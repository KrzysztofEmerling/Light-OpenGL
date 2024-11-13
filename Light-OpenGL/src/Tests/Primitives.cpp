#include "Primitives.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

#include "../Renderer/GLRenderer.h"

namespace Tests
{
    Primitives::Primitives():
        m_Transform0(glm::vec2(300.0f, 100.0f)),m_Transform1(glm::vec2(700.0f, 300.0f)),
        Color0(glm::vec4(1.0f)), Color1(glm::vec4(1.0f))
    {
        glCall(glEnable(GL_BLEND));
        glCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));


        m_Shader = std::make_unique <Graphics::Shader>("Resources/Shaders/Basic.shader");

        float quad_vertices[] = {
             36.13f,  36.13f, 1.0f, 1.0f,
            -36.13f,  36.13f, 0.0f, 1.0f,
            -36.13f, -36.13f, 0.0f, 0.0f,
             36.13f, -36.13f, 1.0f, 0.0f
        };
        unsigned int quad_indices[] = { 0, 1, 2, 2, 3, 0 };
        m_VertexArray0 = std::make_unique<Graphics::VertexArray>();

        m_VertexBuffer0 = std::make_unique<Graphics::VertexBuffer>(quad_vertices, sizeof(quad_vertices));
        Graphics::VertexBufferLayout layout0;
        layout0.Push<float>(2);
        layout0.Push<float>(2);
        m_IndexBuffer0 = std::make_unique<Graphics::IndexBuffer>(quad_indices,6);

        m_VertexArray0->AddBuffer(*m_VertexBuffer0, layout0);

        float hexagon_vertices[] = {
             36.130f,  0.00f, 1.0f, 0.0f,
             18.066f,  31.3f, 0.0f, 1.0f,
            -18.066f,  31.3f, 0.0f, 0.0f,
            -36.130f,  0.00f, 1.0f, 1.0f,
            -18.066f, -31.3f, 0.0f, 1.0f,
             18.066f, -31.3f, 1.0f, 0.0f
        };
        unsigned int hexagon_indices[] = { 0, 1, 2, 2, 3, 4, 4, 5, 0, 0, 2, 4 };
        m_VertexArray1 = std::make_unique<Graphics::VertexArray>();

        m_VertexBuffer1 = std::make_unique<Graphics::VertexBuffer>(hexagon_vertices, sizeof(hexagon_vertices));
        Graphics::VertexBufferLayout layout1;
        layout1.Push<float>(2);
        layout1.Push<float>(2);
        m_IndexBuffer1 = std::make_unique<Graphics::IndexBuffer>(hexagon_indices, 12);

        m_VertexArray1->AddBuffer(*m_VertexBuffer1, layout1);
        
    }

    Primitives::~Primitives()
    {
    }

    void Primitives::OnUpdate(float deltaTime)
    {
    }

    void Primitives::OnRender()
    {
        glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, 0.0f, 100.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, -10, 0));

        m_Shader->Bind();
        m_Shader->SetUniform4f("u_Color",Color0);
        m_Shader->SetUniformMat4f("u_MVP", proj * view * m_Transform0.GetModel());
        Graphics::GLRenderer::Draw(*m_VertexArray0, *m_IndexBuffer0, *m_Shader);
        
        m_Shader->SetUniform4f("u_Color", Color1);
        m_Shader->SetUniformMat4f("u_MVP", proj * view * m_Transform1.GetModel());
        Graphics::GLRenderer::Draw(*m_VertexArray1, *m_IndexBuffer1, *m_Shader);
    }

    void Primitives::OnImGuiRender()
    {
        ImGui::ColorEdit4("Bg_Color1", &Color0[0]);
        m_Transform0.DrawImGui("1");
        ImGui::ColorEdit4("Bg_Color2", &Color1[0]);
        m_Transform1.DrawImGui("2");
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }
}

