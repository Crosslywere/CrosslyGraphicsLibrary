#pragma once

#include <vector>

namespace Crossly
{

	struct AttribPointer
	{
		unsigned int Index;
		int Size;
		int Stride;
		unsigned int Offset;
		bool Enable;
	};

	class VertexBufferLayout
	{
	public:
		inline VertexBufferLayout() = default;
		VertexBufferLayout(const std::initializer_list<AttribPointer>& attribPointers);
		void SetAttribs() const;
	private:
		std::vector<AttribPointer> m_AttribPointers;
	};

}