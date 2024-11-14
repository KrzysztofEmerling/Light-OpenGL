#pragma once
#include"glm.hpp"
#include<vector>
#include"Macros.h"
#include"Buffers.h"

namespace Graphics
{
    struct Vertex
    {
        glm::vec3 Position;

        glm::vec2 TexCoords;
        glm::vec4 Color;
        float     TexID;

    };

    class dVertexBuffer
    {
    private:
        unsigned int m_RendererID;
        unsigned int m_MaxSize;
    public:
        dVertexBuffer(unsigned int max_size = 1024 * sizeof(Vertex));
        ~dVertexBuffer();
        void AddVertices(const Vertex* data, unsigned int count);
        
        inline unsigned int GetMaxSize() const { return m_MaxSize; }
        void Bind() const;
        void Unbind() const;
    };

    class dIndexBuffer
    {
    private:
        unsigned int m_RendererID;
        unsigned int m_Count;
        unsigned int m_MaxCount;
    public:
        dIndexBuffer(unsigned int count);
        ~dIndexBuffer();

        void AddIndices(const unsigned int* data, unsigned int count, unsigned int repet = 1, unsigned int space = 4);
        void Bind() const;
        void Unbind() const;
        inline unsigned int GetCount() const { return m_Count; }
        inline unsigned int GetMaxCount() const { return m_MaxCount; }
    };

    class dVertexArray
    {
    private:
        unsigned int m_RendererID;
        VertexBufferLayout m_Layout;
        mutable unsigned int  m_Offset;
    public:
        dVertexArray(const VertexBufferLayout& layout);
        ~dVertexArray();

        void AddBuffer(const dVertexBuffer& vb) const;

        void Bind() const;
        void Unbind() const;
    };
}
