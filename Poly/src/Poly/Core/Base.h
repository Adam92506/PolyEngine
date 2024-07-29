#pragma once

#include <memory>

#ifdef PY_DEBUG
	#ifdef PY_PLATFORM_WINDOWS
		#define PY_DEBUGBREAK() __debugbreak();
	#else
		#error "Platform does not support debugbreak"
	#endif
	#define PY_ENABLE_ASSERTS
#else
	#define PY_DEBUGBREAK()
#endif

#define PY_EXPAND_MACRO(x) x
#define PY_STRINGIFY_MACRO(x) #x

namespace Poly
{

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}

#include "Poly/Core/Assert.h"
