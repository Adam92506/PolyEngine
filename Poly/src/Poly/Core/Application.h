#pragma once

#include "Base.h"

int main(int argc, char** argv);

namespace Poly
{

	struct ApplicationCommandLineArgs
	{
		int Count = 0;
		char** Args = nullptr;

		const char* operator[](int index) const
		{
			PY_CORE_ASSERT(index < Count);
			return Args[index];
		}
	};

	struct ApplicationSpecification
	{
		std::string Name = "Poly Application";
		std::string WorkingDirectory;
		ApplicationCommandLineArgs CommandLineArgs;
	};

	class Application
	{
	public:
		Application(const ApplicationSpecification& specification);
		virtual ~Application();

		static Application& Get() { return *s_Instance; }
	private:
		void Run();
	private:
		ApplicationSpecification m_Specification;

		bool m_Running = true;
		bool m_Minimized = false;
	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	// To be define by Client
	Application* CreateApplication(ApplicationCommandLineArgs args);
}

