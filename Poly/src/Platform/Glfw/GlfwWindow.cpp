#include "pch.h"
#include "Platform/Glfw/GLFWWindow.h"

#include "Poly/Events/ApplicationEvent.h"
#include "Poly/Events/MouseEvent.h"
#include "Poly/Events/KeyEvent.h"

namespace Poly
{
	static uint8_t s_GLFWWindowCount = 0;

	static void GLFWErrorCallback(int32_t error, const char* description)
	{
		PY_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	GLFWWindow::GLFWWindow(const WindowSpecification& spec)
	{
		Init(spec);
	}

	GLFWWindow::~GLFWWindow()
	{
		Shutdown();
	}

	void GLFWWindow::Init(const WindowSpecification& spec)
	{
		m_Data.Title = spec.Title;
		m_Data.Width = spec.Width;
		m_Data.Height = spec.Height;
		m_Data.VSync = spec.VSync;

		PY_CORE_INFO("Creating window '{0}' ({1}, {2})", m_Data.Title, m_Data.Width, m_Data.Height);

		if (s_GLFWWindowCount == 0)
		{
			int32_t success = glfwInit();
			PY_CORE_ASSERT(success, "Could not initialize GLFW");
			glfwSetErrorCallback(GLFWErrorCallback);
		}

		// Creating GLFW Window
		#ifdef PY_DEBUG
				glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
		#endif

		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);

		// TODO: Create thread-safe context manager
		glfwMakeContextCurrent(m_Window);

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(m_Data.VSync);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int32_t width, int32_t height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				WindowCloseEvent event;
				data.EventCallback(event);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent event(key, false);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key);
						data.EventCallback(event);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent event(key, true);
						data.EventCallback(event);
						break;
					}
				}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, uint32_t keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event(keycode);
				data.EventCallback(event);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int32_t button, int32_t action, int32_t mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event(button);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event(button);
						data.EventCallback(event);
						break;
					}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			});
	}

	void GLFWWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
		--s_GLFWWindowCount;

		if (s_GLFWWindowCount == 0)
		{
			glfwTerminate();
		}
	}

	void GLFWWindow::OnUpdate()
	{
		glfwPollEvents();
	}

	void GLFWWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}
}