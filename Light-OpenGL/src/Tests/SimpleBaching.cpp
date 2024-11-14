#include "SimpleBaching.h"
namespace Tests
{
    SimpleBaching::SimpleBaching()
        : m_Transform(glm::vec2(0.0f, 0.0f))
    {

        m_Vertices[0] = { glm::vec3(36.13f,  36.13f, 0.0f),  glm::vec2(1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), 0.0f };
        m_Vertices[1] = { glm::vec3(-36.13f,  36.13f, 0.0f),  glm::vec2(0.0f, 1.0f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), 0.0f };
        m_Vertices[2] = { glm::vec3(-36.13f, -36.13f, 0.0f),  glm::vec2(0.0f, 0.0f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), 0.0f };
        m_Vertices[3] = { glm::vec3(36.13f, -36.13f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), 0.0f };

        m_Vertices[4] = { glm::vec3(136.13f,  36.13f, 0.0f),  glm::vec2(1.0f, 1.0f), glm::vec4(0.0f, 1.0f, 1.0f, 1.0f), 0.0f };
        m_Vertices[5] = { glm::vec3(-63.87f,  36.13f, 0.0f),  glm::vec2(0.0f, 1.0f), glm::vec4(0.0f, 1.0f, 1.0f, 1.0f), 0.0f };
        m_Vertices[6] = { glm::vec3(-63.87f, -36.13f, 0.0f), glm::vec2(0.0f, 0.0f), glm::vec4(0.0f, 1.0f, 1.0f, 1.0f), 0.0f };
        m_Vertices[7] = { glm::vec3(136.13f, -36.13f, 0.0f),  glm::vec2(1.0f, 0.0f), glm::vec4(0.0f, 1.0f, 1.0f, 1.0f), 0.0f };

        m_Vertices[8] = { glm::vec3(36.13f,  136.13f, 0.0f),  glm::vec2(1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f };
        m_Vertices[9] = { glm::vec3(-36.13f,  136.13f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f };
        m_Vertices[10] = { glm::vec3(-36.13f, -63.87f, 0.0f),  glm::vec2(0.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f };
        m_Vertices[11] = { glm::vec3(36.13f, -63.87f, 0.0f),  glm::vec2(1.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 1.0f };

        m_Vertices[12] = { glm::vec3(136.13f,  136.13f, 0.0f),  glm::vec2(1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 2.0f };
        m_Vertices[13] = { glm::vec3(-63.87f,  136.13f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 2.0f };
        m_Vertices[14] = { glm::vec3(-63.87f, -63.87f, 0.0f),  glm::vec2(0.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 2.0f };
        m_Vertices[15] = { glm::vec3(136.13f, -63.87f, 0.0f),  glm::vec2(1.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), 2.0f };

        m_Indices[0] = 0;
        m_Indices[1] = 1;
        m_Indices[2] = 2;
        m_Indices[3] = 2;
        m_Indices[4] = 3;
        m_Indices[5] = 0;

        glCall(glEnable(GL_BLEND));
        glCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        m_Shader = std::make_unique<Graphics::Shader>("Resources/Shaders/BatchQuads.shader");
        m_Texture0 = std::make_unique<Graphics::Texture>("Resources/Textures/blanc.png");
        m_Texture1 = std::make_unique<Graphics::Texture>("Resources/Textures/czerwona_planeta.png");
        m_Texture2 = std::make_unique<Graphics::Texture>("Resources/Textures/zielona_planeta.png");
       
        m_Texture0->Bind(0);
        m_Texture1->Bind(1);
        m_Texture2->Bind(2);

        int textures[3] = { 0, 1, 2 };
        glm::mat4 mvp = Graphics::GLRenderer::GetProjection() * m_Transform.GetModel();
        m_Shader->SetUniformMat4f("u_MVP", mvp);

        m_Shader->SetSampler("u_Texture", 3, textures);


        Graphics::VertexBufferLayout layout;
        layout.Push<float>(3);  // Position

        layout.Push<float>(2);  // TexCoords
        layout.Push<float>(4);  // Kolor
        layout.Push<float>(1);  // TexID

        m_VertexArray = std::make_unique<Graphics::dVertexArray>(layout);
        m_VertexBuffer = std::make_unique<Graphics::dVertexBuffer>(sizeof(Graphics::Vertex) * 1024);
        m_IndexBuffer = std::make_unique<Graphics::dIndexBuffer>(6 * 256);
    }

    SimpleBaching::~SimpleBaching() {}

    void SimpleBaching::OnUpdate(float deltaTime) {}

    void SimpleBaching::OnRender()
    {
        m_Shader->Bind();
        glm::mat4 mvp = Graphics::GLRenderer::GetProjection() * m_Transform.GetModel();
        m_Shader->SetUniformMat4f("u_MVP", mvp);

        m_VertexBuffer->AddVertices(m_Vertices, 4);
        m_IndexBuffer->AddIndices(m_Indices, 6, 4, 4);
        m_VertexArray->AddBuffer(*m_VertexBuffer);

        Graphics::GLRenderer::Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
    }

    void SimpleBaching::OnImGuiRender()
    {
        m_Transform.DrawImGui("1");

        ImGui::Begin("Bached Vertices:");
        for (size_t i = 0; i < 4; ++i) {
            std::string uniqID = std::to_string(i);

            ImGui::Text("Vertex %zu", i);
            ImGui::Text("Position");
            ImGui::DragFloat3(("##Position" + uniqID).c_str(), &m_Vertices[i].Position[0], 1.0f);

            ImGui::Text("TexCoords");
            ImGui::DragFloat2(("##TexCoords" + uniqID).c_str(), &m_Vertices[i].TexCoords[0], 0.01f);

            ImGui::Text("Color");
            ImGui::ColorEdit4(("##Color" + uniqID).c_str(), &m_Vertices[i].Color[0]);

            /*
            ImGui::Text("Texture ID");
            ImGui::RadioButton(("TexID:0##" + uniqID).c_str(), &m_Vertices[i].TexID, 0.0f);
            ImGui::SameLine();
            ImGui::RadioButton(("TexID:1##" + uniqID).c_str(), &m_Vertices[i].TexID, 1.0f);
            ImGui::SameLine();
            ImGui::RadioButton(("TexID:2##" + uniqID).c_str(), &m_Vertices[i].TexID, 2.0f);
            */
            ImGui::Separator();
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

        }
        ImGui::End();
    }
}