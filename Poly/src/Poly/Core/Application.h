#pragma once

#include "Base.h"

#include "Poly/Core/Window.h"
#include "Poly/Core/Timestep.h"
#include "Poly/Core/LayerStack.h"

#include "Poly/Events/Event.h"
#include "Poly/Events/ApplicationEvent.h"


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

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		void Close();

		ApplicationSpecification& GetSpecification() { return m_Specification; }

		static Application& Get() { return *s_Instance; }
	private:
		void Run();

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		ApplicationSpecification m_Specification;
		Scope<Window> m_Window;
		LayerStack m_LayerStack;
		bool m_Running = true;
		bool m_Minimized = false;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	// To be define by Client
	Application* CreateApplication(ApplicationCommandLineArgs args);
}

