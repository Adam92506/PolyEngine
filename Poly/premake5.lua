project "Poly"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "src/pch.cpp"

	files
	{
		"src/**.h",
		"src/**.cpp",
	}

	includedirs
	{
		"src",
		"vendor/spdlog/include"
	}

	links
	{
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