#include "Test.h"
#include "ImGui/imgui.h"

namespace Tests
{
	Menu::Menu(Test*& currentTest):
		m_CurrentTest(currentTest)
	{

	}
	Menu::~Menu()
	{
	}

	void Menu::OnImGuiRender()
	{
		for (auto& test : m_Tests)
		{
			if (ImGui::Button(test.first.c_str()))
			{
				m_CurrentTest = test.second();
			}
		}
	}
}

