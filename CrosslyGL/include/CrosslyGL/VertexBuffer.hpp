#pragma once

namespace Crossly
{

	class VertexBuffer
	{
	public:
		VertexBuffer(const float* data, unsigned int elementCount);
		~VertexBuffer();
		void Bind() const;
		static void Unbind();
	private:
		unsigned int m_BufferID;
	};

}