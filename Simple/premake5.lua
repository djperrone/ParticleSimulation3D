workspace "SimpleSim"
	architecture "x64"
	startproject "SimpleSim"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- include directories relative to root folder (solution directory)

IncludeDir = {}
IncludeDir["GLFW"] = "SimpleSim/vendor/GLFW/include"
IncludeDir["Glad"] = "SimpleSim/vendor/Glad/include"
IncludeDir["ImGui"] = "SimpleSim/vendor/localimgui"
IncludeDir["stb_image"] = "SimpleSim/vendor/stb_image"
IncludeDir["glm"] = "SimpleSim/vendor/glm"


include "SimpleSim/vendor/GLFW"
include "SimpleSim/vendor/Glad"
--include "SimpleSim/vendor/imgui"


project "SimpleSim"
	location "SimpleSim"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")	

	--pchheader "hzpch.h"
	--pchsource "SimpleSim/src/hzpch.cpp"

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"	
	}

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/localimgui/imgui/*.h",
		"%{prj.name}/vendor/localimgui/imgui/*.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",		
		"%{prj.name}/vendor/spdlog/include",		
		--"%{prj.name}/vendor/localimgui",		
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",	
		"%{IncludeDir.stb_image}",	
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
	--	"ImGui",		
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{			
			"GLFW_INCLUDE_NONE"		
		}

	filter "configurations:Debug"			
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
