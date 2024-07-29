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

group "Core"
	include "Poly/premake5.lua"
group ""

group "Misc"
	include "Sandbox/premake5.lua"
group ""