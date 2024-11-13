#pragma once
#include "Test.h"
#include "../Core/Transform.h"
#include <memory>
#include "../Renderer/GLRenderer.h"
namespace Tests
{
    class ParentTransform : public Test
    {
    private:
        Transform m_Transform0, m_Transform1;         

        std::unique_ptr<Graphics::Shader> m_Shader;
        std::unique_ptr<Graphics::Texture> m_Texture1;
        std::unique_ptr<Graphics::Texture> m_Texture2;

        std::unique_ptr<Graphics::VertexArray> m_VertexArray;
        std::unique_ptr<Graphics::VertexBuffer> m_VertexBuffer; 
        std::unique_ptr<Graphics::IndexBuffer> m_IndexBuffer;   


    public:
        ParentTransform();
        ~ParentTransform();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
    };
}


