#include "Buffers.h"


namespace Graphics
{
    VertexBuffer::VertexBuffer(const void* data, unsigned int size)
    {
        m_DataSize = size;
        glCall(glGenBuffers(1, &m_RendererID));
        glCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
        glCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
    }

    VertexBuffer::VertexBuffer(const VertexBuffer& other)
    {
        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_COPY_READ_BUFFER, other.m_RendererID);
        glBindBuffer(GL_COPY_WRITE_BUFFER, m_RendererID);

        m_DataSize = other.GetDataSize();
        glGetBufferParameteriv(GL_COPY_READ_BUFFER, GL_BUFFER_SIZE, &m_DataSize);

        glBufferData(GL_COPY_WRITE_BUFFER, m_DataSize, nullptr, GL_STATIC_DRAW);
        glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, m_DataSize);
    }
    VertexBuffer::VertexBuffer(VertexBuffer&& other) noexcept
        : m_RendererID(other.m_RendererID), m_DataSize(other.m_DataSize)
    {
        other.m_RendererID = 0;
        other.m_DataSize = 0;
    }
    VertexBuffer& VertexBuffer::operator=(const VertexBuffer& other)
    {
        if (this == &other)
            return *this;

        glCall(glDeleteBuffers(1, &m_RendererID));

        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_COPY_READ_BUFFER, other.m_RendererID);
        glBindBuffer(GL_COPY_WRITE_BUFFER, m_RendererID);
        m_DataSize = other.GetDataSize();
        glGetBufferParameteriv(GL_COPY_READ_BUFFER, GL_BUFFER_SIZE, &m_DataSize);
        glBufferData(GL_COPY_WRITE_BUFFER, m_DataSize, nullptr, GL_STATIC_DRAW);
        glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, m_DataSize);

        return *this;
    }
    VertexBuffer& VertexBuffer::operator=(VertexBuffer&& other) noexcept
    {
        if (this == &other)
            return *this;

        glCall(glDeleteBuffers(1, &m_RendererID));

        m_RendererID = other.m_RendererID;
        m_DataSize = other.m_DataSize;

        other.m_RendererID = 0;
        other.m_DataSize = 0;

        return *this;
    }

    VertexBuffer::~VertexBuffer()
    {
        glCall(glDeleteBuffers(1, &m_RendererID));
    }


    void VertexBuffer::Bind() const
    {
        glCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    }

    void VertexBuffer::Unbind() const
    {
        glCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    }

    IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) :
        m_Count(count)
    {
        ASSERT(sizeof(unsigned int) == sizeof(GLuint));

        glCall(glGenBuffers(1, &m_RendererID));
        glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
        glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(unsigned int), data, GL_STATIC_DRAW));
    }

    IndexBuffer::IndexBuffer(const IndexBuffer& other)
        : m_Count(other.m_Count)
    {
        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_COPY_READ_BUFFER, other.m_RendererID);
        glBindBuffer(GL_COPY_WRITE_BUFFER, m_RendererID);

        glBufferData(GL_COPY_WRITE_BUFFER, m_Count * sizeof(unsigned int), nullptr, GL_STATIC_DRAW);
        glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, m_Count * sizeof(unsigned int));
    }
    IndexBuffer::IndexBuffer(IndexBuffer&& other) noexcept
        : m_RendererID(other.m_RendererID), m_Count(other.m_Count)
    {
        other.m_RendererID = 0;
        other.m_Count = 0;       
    }
    IndexBuffer& IndexBuffer::operator=(const IndexBuffer& other)
    {
        if (this == &other)
            return *this;

        glCall(glDeleteBuffers(1, &m_RendererID));

        m_Count = other.m_Count;

        glGenBuffers(1, &m_RendererID);
        glBindBuffer(GL_COPY_READ_BUFFER, other.m_RendererID);
        glBindBuffer(GL_COPY_WRITE_BUFFER, m_RendererID);
        glBufferData(GL_COPY_WRITE_BUFFER, m_Count * sizeof(unsigned int), nullptr, GL_STATIC_DRAW);
        glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, m_Count * sizeof(unsigned int));

        return *this;
    }
    IndexBuffer& IndexBuffer::operator=(IndexBuffer&& other) noexcept
    {
        if (this == &other)
            return *this;

        glCall(glDeleteBuffers(1, &m_RendererID));

        m_RendererID = other.m_RendererID;
        m_Count = other.m_Count;

        other.m_RendererID = 0;
        other.m_Count = 0;

        return *this;
    }

    IndexBuffer::~IndexBuffer()
    {
        glCall(glDeleteBuffers(1, &m_RendererID));
    }

    void IndexBuffer::Bind() const
    {
        glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
    }

    void IndexBuffer::Unbind() const
    {
        glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
    }

    unsigned int VertexBufferElement::GetSize(unsigned int type) const
    {
        switch (type)
        {
        case GL_FLOAT:          return 4;
        case GL_UNSIGNED_INT:   return 4;
        case GL_INT:            return 4;
        case GL_UNSIGNED_BYTE:  return 1;
        }
        ASSERT(false);
        return 0;
    }

    VertexArray::VertexArray():
        m_RendererID(0)
    {
        glCall(glGenVertexArrays(1, &m_RendererID));
    }

    VertexArray::~VertexArray()
    {
        glCall(glDeleteVertexArrays(1, &m_RendererID));
    }

    void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) const
    {
        Bind();
        vb.Bind();
        const auto& elements = layout.GetElements();
        unsigned int offset = 0;
        for (unsigned int i = 0; i < elements.size(); i++)
        {
            const auto& element = elements[i];
            glCall(glEnableVertexAttribArray(i));
            glCall(glVertexAttribPointer(i, element.count, element.type,
                element.normalized, layout.GetStride(), (const void*)offset));
            offset += element.GetSize(element.type) * element.count;
        }
    }

    void VertexArray::Bind() const
    {
        glCall(glBindVertexArray(m_RendererID));
    }
    void VertexArray::Unbind() const
    {
        glCall(glBindVertexArray(0));
    }
}