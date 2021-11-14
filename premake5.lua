workspace "ParticleSimulation3D"
	architecture "x64"
	startproject "ParticleSimulation3D"

	configurations
	{
		"Debug",
		"Release"		
	}	


outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "ParticleSimulation3D/vendor/GLFW/include"
IncludeDir["Glad"] = "ParticleSimulation3D/vendor/Glad/include"
IncludeDir["ImGui"] = "ParticleSimulation3D/vendor/imgui"
IncludeDir["glm"] = "ParticleSimulation3D/vendor/glm"
IncludeDir["stb_image"] = "ParticleSimulation3D/vendor/stb_image"

group "Dependencies"

include "ParticleSimulation3D/vendor/GLFW"
include "ParticleSimulation3D/vendor/Glad"
include "ParticleSimulation3D/vendor/imgui"
group ""


project "ParticleSimulation3D"
	location "ParticleSimulation3D"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	-- pchheader "hzpch.h"
	-- pchsource "ParticleSimulation3D/src/hzpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links 
	{ 
		"GLFW",
		"Glad",
		"ImGui",
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