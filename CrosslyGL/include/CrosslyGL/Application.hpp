#pragma once

namespace Crossly
{

	class Application
	{
	public:
		inline Application(unsigned int width, unsigned int height, const char* title) : m_Width(width), m_Height(height), m_Title(title) {}
		virtual inline ~Application() {}

		virtual void OnCreate() = 0;
		virtual void OnUpdate(float dt) = 0;
		virtual void OnRender() = 0;
		virtual void OnDestroy() = 0;

		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }
		inline const char* GetTitle() const { return m_Title; }
	protected:
		unsigned int m_Width, m_Height;
		const char* m_Title;
	};

}