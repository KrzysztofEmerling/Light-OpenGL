#include "ParentTransform.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

#include "../Renderer/GLRenderer.h"


namespace Tests
{
    ParentTransform::ParentTransform():
        m_Transform0(glm::vec2(500.0f, 260.0f), 0.0f, glm::vec2(2.0f, 2.0f)),m_Transform1(glm::vec2(0.0f, 140.0f), 0.0f, glm::vec2(0.6f, 0.6f))
    {
        float vertices[] = {
             36.13f,  36.13f, 1.0f, 1.0f,
            -36.13f,  36.13f, 0.0f, 1.0f,
            -36.13f, -36.13f, 0.0f, 0.0f, 
             36.13f, -36.13f, 1.0f, 0.0f
        };
        unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };

        m_Shader = std::make_unique <Graphics::Shader>("Resources/Shaders/Texture.shader");
        m_Texture1 = std::make_unique <Graphics::Texture>("Resources/Textures/zielona_planeta.png");
        m_Texture2 = std::make_unique <Graphics::Texture>("Resources/Textures/czerwona_planeta.png");
        

        m_VertexArray = std::make_unique<Graphics::VertexArray>();

        m_VertexBuffer = std::make_unique<Graphics::VertexBuffer>(vertices, sizeof(vertices));
        Graphics::VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        m_IndexBuffer = std::make_unique<Graphics::IndexBuffer>(indices,6);

        m_VertexArray->AddBuffer(*m_VertexBuffer, layout);
        
    }

    ParentTransform::~ParentTransform()
    {
    }

    void ParentTransform::OnUpdate(float deltaTime)
    {
        float t0_rotation = m_Transform0.GetRotation() + 0.005f;
        float t1_rotation = m_Transform1.GetRotation() - 0.007f;
        m_Transform0.SetRotation(t0_rotation);
        m_Transform1.SetRotation(t1_rotation);
        m_Transform1.SetParentModel(m_Transform0.GetModel());
    }

    void ParentTransform::OnRender()
    {
        glm::mat4 proj = Graphics::GLRenderer::GetProjection();
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, -10, 0));

        m_Shader->Bind();
        m_Texture1->Bind(0);
        m_Shader->SetUniform1i("u_Texture", 0);
        m_Shader->SetUniformMat4f("u_MVP", proj * view * m_Transform0.GetModel());
        Graphics::GLRenderer::Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
        
        m_Texture2->Bind(1);
        m_Shader->SetUniform1i("u_Texture", 1);
        m_Shader->SetUniformMat4f("u_MVP", proj * view * m_Transform1.GetModel());
        Graphics::GLRenderer::Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
    }

    void ParentTransform::OnImGuiRender()
    {
        m_Transform0.DrawImGui("-parent");
        m_Transform1.DrawImGui("-child");
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }
}

