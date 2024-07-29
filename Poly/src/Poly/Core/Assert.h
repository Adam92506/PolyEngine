#pragma once

#include "Poly/Core/Base.h"
#include "Poly/Core/Log.h"
#include <filesystem>

#ifdef PY_ENABLE_ASSERTS
	#define PY_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { PY##type##ERROR(msg, __VA_ARGS__); PY_DEBUGBREAK(); } }
	#define PY_INTERNAL_ASSERT_WITH_MSG(type, check, ...) PY_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define PY_INTERNAL_ASSERT_NO_MSG(type, check) PY_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", PY_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)
	
	#define PY_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define PY_INTERNAL_ASSERT_GET_MACRO(...) PY_EXPAND_MACRO( PY_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, PY_INTERNAL_ASSERT_WITH_MSG, PY_INTERNAL_ASSERT_NO_MSG) )
	
	#define PY_ASSERT(...) PY_EXPAND_MACRO( PY_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
	#define PY_CORE_ASSERT(...) PY_EXPAND_MACRO( PY_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else
	#define PY_ASSERT(...)
	#define PY_CORE_ASSERT(...)
#endif