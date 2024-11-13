#pragma once
#include "Macros.h"

#include "Buffers.h"
#include "DynamicBuffers.h"
#include "Shaders.h"

namespace Graphics
{

    class GLRenderer
    {
    private:
        static glm::mat4 m_Projection;
        static float m_AspectRatio;
    public:
        GLRenderer();
        static inline glm::mat4 GetProjection() { return m_Projection; };
        static inline float GetAspectRatio() { return m_AspectRatio; };

        static void UpdateWindowSize(int width, int height);
        static void Clear();
        static void Draw(const VertexArray& vao, const IndexBuffer& ibo, const Shader& shader);
        static void Draw(const std::unique_ptr<VertexArray>& vao, const std::unique_ptr<IndexBuffer>& ibo, const std::unique_ptr<Shader>& shader);

        static void Draw(const dVertexArray& vao, const dIndexBuffer& ibo, const Shader& shader);
    };

}

