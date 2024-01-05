#include <CrosslyGL/VertexBufferLayout.hpp>

#include <glad/glad.h>

namespace Crossly
{

	VertexBufferLayout::VertexBufferLayout(const std::initializer_list<AttribPointer>& attribPointers)
		: m_AttribPointers(attribPointers)
	{
	}

	void VertexBufferLayout::SetAttribs() const
	{
		for (const auto& attrib : m_AttribPointers)
		{
			if (attrib.Enable)
				glEnableVertexAttribArray(attrib.Index);
			else
				continue;
			glVertexAttribPointer(attrib.Index, attrib.Size, GL_FLOAT, GL_FALSE, attrib.Stride, reinterpret_cast<void*>(attrib.Offset));
		}
	}

}