#pragma once

#include "Poly/Core/Base.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Poly
{
	class Log
	{
	public:
		static void Init();

		static Ref<spdlog::logger> GetCoreLogger() { return s_CoreLogger; }
		static Ref<spdlog::logger> GetClientLogger() { return s_ClientLogger; }
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};

	// Core log macros
	#define PY_CORE_TRACE(...)		::Poly::Log::GetCoreLogger()->trace(__VA_ARGS__);
	#define PY_CORE_INFO(...)		::Poly::Log::GetCoreLogger()->info(__VA_ARGS__);
	#define PY_CORE_WARN(...)		::Poly::Log::GetCoreLogger()->warn(__VA_ARGS__);
	#define PY_CORE_ERROR(...)		::Poly::Log::GetCoreLogger()->error(__VA_ARGS__);
	#define PY_CORE_CRITICAL(...)	::Poly::Log::GetCoreLogger()->critical(__VA_ARGS__);
	
	// Client log macros
	#define PY_CLIENT_TRACE(...)	::Poly::Log::GetClientLogger()->trace(__VA_ARGS__);
	#define PY_CLIENT_INFO(...)		::Poly::Log::GetClientLogger()->info(__VA_ARGS__);
	#define PY_CLIENT_WARN(...)		::Poly::Log::GetClientLogger()->warn(__VA_ARGS__);
	#define PY_CLIENT_ERROR(...)	::Poly::Log::GetClientLogger()->error(__VA_ARGS__);
	#define PY_CLIENT_CRITICAL(...)	::Poly::Log::GetClientLogger()->critical(__VA_ARGS__);
}