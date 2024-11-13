#include "BgColor.h"
#include "../Renderer/Macros.h"
namespace Tests
{
	BgColor::BgColor() :
		m_BgColor{ 0.2f, 0.4f, 0.8f, 1.0f }
	{
	}

	BgColor::~BgColor()
	{
		glCall(glClearColor(0.0f,0.0f,0.0f,1.0f));
		glCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void BgColor::OnRender()
	{
		glCall(glClearColor(m_BgColor[0], m_BgColor[1], m_BgColor[2], m_BgColor[3]));
		glCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void BgColor::OnImGuiRender()
	{
		ImGui::ColorEdit4("Bg_Color", &m_BgColor[0]);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}
