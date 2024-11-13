#include "DynamicBuffers.h"

namespace Graphics
{
	dVertexBuffer::dVertexBuffer(unsigned int max_size)
	{
		m_MaxSize = max_size;
		glCall(glGenBuffers(1, &m_RendererID));
		glCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
		glCall(glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * max_size, nullptr, GL_DYNAMIC_DRAW));
	}
	dVertexBuffer::~dVertexBuffer()
	{
		glCall(glDeleteBuffers(1, &m_RendererID));
	}
	void dVertexBuffer::AddVertices(const Vertex* data, unsigned int count)
	{
		Bind();
		glCall(glBufferSubData(GL_ARRAY_BUFFER, 0, count * sizeof(Vertex), data));
	}

	void dVertexBuffer::Bind() const
	{
		glCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	}

	void dVertexBuffer::Unbind() const
	{
		glCall(glDeleteBuffers(0, &m_RendererID));
	}

	dIndexBuffer::dIndexBuffer(unsigned int max_count):
		m_RendererID(0), m_MaxCount(max_count), m_Count(0)
	{
		glGenBuffers(1, &m_RendererID);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, max_count * sizeof(unsigned int), nullptr, GL_DYNAMIC_DRAW);
	}
	dIndexBuffer::~dIndexBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}
	void dIndexBuffer::AddIndices(const unsigned int* data, unsigned int count, unsigned int repet, unsigned int space)
	{
		unsigned int* indecies;
		indecies = new unsigned int[count * repet];
		std::memcpy(indecies, data, count * sizeof(unsigned int));

		for (unsigned int i = 1; i < repet; i++)
		{
			for (unsigned int j = 0; j < count; j++)
			{
				unsigned int index = i * count + j;
				indecies[index] = indecies[index - count] + space;
			}
		}

		Bind();
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(unsigned int), repet * count * sizeof(unsigned int), data);
		m_Count += count;
	}

	void dIndexBuffer::Bind() const
	{
		glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	}

	void dIndexBuffer::Unbind() const
	{
		glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
	}



	dVertexArray::dVertexArray(const VertexBufferLayout& layout) :
		m_RendererID(0), m_Layout(layout), m_Offset(0)
	{
		glCall(glGenVertexArrays(1, &m_RendererID));
	}

	dVertexArray::~dVertexArray()
	{
		glCall(glDeleteVertexArrays(1, &m_RendererID));
	}

	void dVertexArray::AddBuffer(const dVertexBuffer& vb) const
	{
		Bind();
		vb.Bind();
		const auto& elements = m_Layout.GetElements();
		for (unsigned int i = 0; i < elements.size(); i++)
		{
			const auto& element = elements[i];
			glCall(glEnableVertexAttribArray(i));
			glCall(glVertexAttribPointer(i, element.count, element.type,
				element.normalized, m_Layout.GetStride(), (const void*)m_Offset));
			m_Offset += element.GetSize(element.type) * element.count;
		}
	}

	void dVertexArray::Bind() const
	{
		glCall(glBindVertexArray(m_RendererID));
	}
	void dVertexArray::Unbind() const
	{
		glCall(glBindVertexArray(0));
	}
}
