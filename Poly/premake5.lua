project "Poly"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "src/pch.cpp"

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	files
	{
		"src/**.h",
		"src/**.cpp",
	}

	includedirs
	{
		"src",
		"vendor/spdlog/include",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.glad}"
	}

	links
	{
		"GLFW",
		"Glad"
	}

	filter "system:windows"
		systemversion "latest"
		defines "PY_PLATFORM_WINDOWS"

	filter "configurations:Debug"
		defines "PY_DEBUG"
		symbols "on"

	filter "configurations:Release"
		defines "PY_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "PY_DIST"
		runtime "Release"
		optimize "on"