#pragma once
#include "Test.h"
#include "../Core/Transform.h"
#include <memory>
#include "../Renderer/GLRenderer.h"
namespace Tests
{
    class Primitives : public Test
    {
    private:
        Transform m_Transform0, m_Transform1; 
        glm::vec4 Color0, Color1;

        std::unique_ptr<Graphics::Shader> m_Shader;

        std::unique_ptr<Graphics::VertexArray> m_VertexArray0;
        std::unique_ptr<Graphics::VertexBuffer> m_VertexBuffer0; 
        std::unique_ptr<Graphics::IndexBuffer> m_IndexBuffer0;   

        std::unique_ptr<Graphics::VertexArray> m_VertexArray1;
        std::unique_ptr<Graphics::VertexBuffer> m_VertexBuffer1;
        std::unique_ptr<Graphics::IndexBuffer> m_IndexBuffer1;

    public:
        Primitives();
        ~Primitives();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
    };
}


