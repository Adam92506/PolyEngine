#include "pch.h"
#include "Poly/Core/Window.h"

#ifdef PY_PLATFORM_WINDOWS
	#include "Platform/Glfw/GlfwWindow.h"
#endif

namespace Poly
{

	Scope<Window> Window::Create(const WindowSpecification& spec)
	{
		#ifdef PY_PLATFORM_WINDOWS
			return CreateScope<GLFWWindow>(spec);
		#else
		#endif
	}

}