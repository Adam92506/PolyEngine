#include "pch.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Poly
{

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		PY_CORE_ASSERT(windowHandle, "Can not create OpenGL Context: Window handle is null");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		
		// Initialize Glad
		int32_t status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PY_CORE_ASSERT(status, "Failed to initialize Glad");

		// Log OpenGL Info
		PY_CORE_INFO("OpenGL Info:");
		PY_CORE_INFO("    Vendor: {0}", (char*)glGetString(GL_VENDOR));
		PY_CORE_INFO("    Renderer: {0}", (char*)glGetString(GL_RENDERER));
		PY_CORE_INFO("    Version: {0}", (char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}