#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include "Test.h"
#include "../Renderer/GLRenderer.h"

namespace Tests
{
    class ShadersShowdown : public Test
    {
    private:
        std::unique_ptr<Graphics::Shader> m_Shader;
        std::unique_ptr<Graphics::VertexArray> m_VertexArray;
        std::unique_ptr<Graphics::VertexBuffer> m_VertexBuffer;
        std::unique_ptr<Graphics::IndexBuffer> m_IndexBuffer;
        std::vector<std::string> m_ShaderFiles;
        std::string m_SelectedShader;

    public:
        ShadersShowdown();
        ~ShadersShowdown();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;

        void loadShader(const std::string& shaderName);
        std::vector<std::string> getShaderFiles(const std::string& folderPath);
    };
}
