#pragma once
#include <vector>
#include <functional>
#include <string>

namespace Tests
{
	class Test
	{
	public:
		Test() {}
		virtual ~Test() {};

		virtual void OnUpdate(float deltaTime) {}
		virtual void OnRender() {}
		virtual void OnImGuiRender() {}
	};

	class Menu :
		public Test
	{
	private:
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_Tests;
		Test*& m_CurrentTest;
	public:
		Menu(Test*& currentTest);
		~Menu();

		void OnImGuiRender() override;

		template<typename T>
		void RegisterTest(const std::string& name)
		{
			m_Tests.push_back(std::make_pair(name, []() {return new T(); }));
		}
		inline void SetTest(int id) { if(id < m_Tests.size() && id >= 0) m_CurrentTest = m_Tests[id].second(); };
	};
}
