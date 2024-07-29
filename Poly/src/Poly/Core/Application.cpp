#include "pch.h"
#include "Application.h"

namespace Poly
{

	Application* Application::s_Instance = nullptr;

	Application::Application(const ApplicationSpecification& specification)
		: m_Specification(specification)
	{
		PY_CORE_ASSERT(!s_Instance, "Application already exists");
		s_Instance = this;

		if (!m_Specification.WorkingDirectory.empty())
			std::filesystem::current_path(m_Specification.WorkingDirectory);
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_Running)
		{

		}
	}

}