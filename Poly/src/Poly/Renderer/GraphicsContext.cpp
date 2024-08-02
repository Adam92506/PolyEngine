#include "pch.h"
#include "Poly/Renderer/GraphicsContext.h"

#ifdef PY_PLATFORM_WINDOWS
	#include "Platform/OpenGL/OpenGLContext.h"
#endif

namespace Poly
{

	Scope<GraphicsContext> GraphicsContext::Create(void* windowHandle)
	{
		#ifdef PY_PLATFORM_WINDOWS
			return CreateScope<OpenGLContext>((GLFWwindow*)windowHandle);
		#else
			PY_CORE_ERROR("Can not create Graphics Context: Platform not supported");
		#endif
	}

}