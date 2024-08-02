include "Dependencies.lua"

workspace "PolyEngine"
	architecture "x86_64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
	include "Poly/vendor/glfw"
	include "Poly/vendor/glad"
group ""

group "Core"
	include "Poly/premake5.lua"
group ""

group "Misc"
	include "Sandbox/premake5.lua"
group ""