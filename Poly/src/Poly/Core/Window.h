#pragma once

#include "Poly/Core/Base.h"

#include "Poly/Events/Event.h"

namespace Poly
{

	struct WindowSpecification
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;
		bool VSync;

		WindowSpecification(const std::string& title = "Poly Engine", uint32_t width = 1920, uint32_t height = 1080, bool vsync = true)
			: Title(title), Width(width), Height(height), VSync(vsync)
		{
		}
	};

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() = default;

		virtual void OnUpdate() = 0;
		
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		// Window Attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Scope<Window> Create(const WindowSpecification& spec = WindowSpecification());
	};

}