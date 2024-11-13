#pragma once

#include "Test.h"
#include "../Renderer/GLRenderer.h"
#include "../Core/Transform.h"

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

namespace Tests
{
    class SimpleBaching : public Test
    {
    private:
        std::unique_ptr<Graphics::Shader> m_Shader;
        std::unique_ptr<Graphics::Texture> m_Texture0;
        std::unique_ptr<Graphics::Texture> m_Texture1;
        std::unique_ptr<Graphics::Texture> m_Texture2;

        std::unique_ptr<Graphics::dVertexBuffer> m_VertexBuffer;
        std::unique_ptr<Graphics::dIndexBuffer> m_IndexBuffer;
        std::unique_ptr<Graphics::dVertexArray> m_VertexArray;

        Graphics::Vertex m_Vertices[16];
        unsigned int m_Indices[6];

        glm::mat4 m_Proj, m_View;
        Transform m_Transform;

    public:
        SimpleBaching();
        ~SimpleBaching() override;

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
    };
}