#include "ShadersShowdown.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "../Renderer/GLRenderer.h"
#include <filesystem>

namespace Tests
{
    ShadersShowdown::ShadersShowdown()
    {
        float vertices[] = {
             1.0f,  1.0f, 1.0f, 1.0f,
            -1.0f,  1.0f, 0.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f,
             1.0f, -1.0f, 1.0f, 0.0f
        };

        unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };

        m_VertexArray = std::make_unique<Graphics::VertexArray>();
        m_VertexBuffer = std::make_unique<Graphics::VertexBuffer>(vertices, sizeof(vertices));
        Graphics::VertexBufferLayout layout;
        layout.Push<float>(2); // 2D position
        layout.Push<float>(2); // TexCoords
        m_VertexArray->AddBuffer(*m_VertexBuffer, layout);
        m_IndexBuffer = std::make_unique<Graphics::IndexBuffer>(indices, 6);

        std::string shaderFolder = "src/Tests/TestShaders/";
        m_ShaderFiles = getShaderFiles(shaderFolder);

        if (!m_ShaderFiles.empty())
        {
            loadShader(m_ShaderFiles[0]);
            m_SelectedShader = m_ShaderFiles[0];
        }
    }

    ShadersShowdown::~ShadersShowdown()
    {
    }



    void ShadersShowdown::OnUpdate(float deltaTime)
    {
        m_Shader->Bind();
        m_Shader->SetUniform1f("u_Aspect", Graphics::GLRenderer::GetAspectRatio());
        m_Shader->SetUniform1f("u_Time", deltaTime);
    }

    void ShadersShowdown::OnRender()
    {
        if (m_Shader)
        {
            
            Graphics::GLRenderer::Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
        }
    }

    void ShadersShowdown::OnImGuiRender()
    {
        ImGui::Text("ShadersShowdown - Wybierz shader");

        if (ImGui::BeginCombo("Shaders", m_SelectedShader.c_str()))
        {
            for (int i = 0; i < m_ShaderFiles.size(); i++)
            {
                bool isSelected = (m_SelectedShader == m_ShaderFiles[i]);
                if (ImGui::Selectable(m_ShaderFiles[i].c_str(), isSelected))
                {
                    m_SelectedShader = m_ShaderFiles[i];
                    loadShader(m_ShaderFiles[i]); 
                }

                if (isSelected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }
    }

    void ShadersShowdown::loadShader(const std::string& shaderName)
    {
        std::string shaderPath = "src/Tests/TestShaders/" + shaderName;
        m_Shader = std::make_unique<Graphics::Shader>(shaderPath);
    }
    std::vector<std::string> ShadersShowdown::getShaderFiles(const std::string& folderPath)
    {
        std::vector<std::string> shaders;
        for (const auto& entry : std::filesystem::directory_iterator(folderPath))
        {
            if (entry.path().extension() == ".shader")
            {
                shaders.push_back(entry.path().filename().string());
            }
        }
        return shaders;
    }
}
