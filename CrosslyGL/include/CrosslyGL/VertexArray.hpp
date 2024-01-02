#pragma once

namespace Crossly
{

	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();
		void Bind() const;
		static void Unbind();
	private:
		unsigned int m_VertexArrayID;
	};

}