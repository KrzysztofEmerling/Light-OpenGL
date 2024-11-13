#pragma once
#include"Macros.h"

enum class Primitive
{
    Quad,
    Hexagon
};

namespace Graphics
{

    class VertexBuffer
    {
    private:
        unsigned int m_RendererID;
        int m_DataSize;
    public:
        VertexBuffer(const void* data, unsigned int size);

        VertexBuffer(const VertexBuffer& other);
        VertexBuffer(VertexBuffer&& other) noexcept;
        VertexBuffer& operator=(const VertexBuffer& other);
        VertexBuffer& operator=(VertexBuffer&& other) noexcept;
        ~VertexBuffer();

        inline unsigned int GetDataSize() const { return m_DataSize; }
        void Bind() const;
        void Unbind() const;
    };

    class IndexBuffer
    {
    private:
        unsigned int m_RendererID;
        unsigned int m_Count;
    public:
        IndexBuffer(const unsigned int* data, unsigned int count);

        IndexBuffer(const IndexBuffer& other);
        IndexBuffer(IndexBuffer&& other) noexcept;
        IndexBuffer& operator=(const IndexBuffer& other);
        IndexBuffer& operator=(IndexBuffer&& other) noexcept;
        ~IndexBuffer();

        void Bind() const;
        void Unbind() const;
        inline unsigned int GetCount() const { return m_Count; }
    };

    struct VertexBufferElement
    {
        unsigned int type;
        unsigned int count;
        unsigned char normalized;

        unsigned int GetSize(unsigned int type)const;

    };

    class VertexBufferLayout
    {
    private:
        std::vector<VertexBufferElement> m_Elements;
        unsigned int m_Stride;
    public:
        VertexBufferLayout() : m_Stride(0) {}

        template<typename T>
        void Push(unsigned int count);

        inline unsigned int GetStride() const { return m_Stride; }
        inline const std::vector<VertexBufferElement> GetElements() const& { return m_Elements; }
    };
    
    template<>
    inline void VertexBufferLayout::Push<float>(unsigned int count)
    {
        m_Elements.push_back({ GL_FLOAT,count,GL_FALSE });
        m_Stride += sizeof(GLfloat) * count;
    }
    template<>
    inline void VertexBufferLayout::Push<int>(unsigned int count)
    {
        m_Elements.push_back({ GL_INT,count,GL_FALSE });
        m_Stride += sizeof(GLint) * count;
    }
    template<>
    inline void VertexBufferLayout::Push<unsigned int>(unsigned int count)
    {
        m_Elements.push_back({ GL_UNSIGNED_INT,count,GL_FALSE });
        m_Stride += sizeof(GLuint) * count;
    }
    template<>
    inline void VertexBufferLayout::Push<unsigned char>(unsigned int count)
    {
        m_Elements.push_back({ GL_UNSIGNED_BYTE,count,GL_TRUE });
        m_Stride += sizeof(GLbyte) * count;
    }


    class VertexArray
    {
    private:
        unsigned int m_RendererID;
    public:
        VertexArray();
        ~VertexArray();

        void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) const;

        void Bind() const;
        void Unbind() const;
    };

}