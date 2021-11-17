workspace "BasaltEngine"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["spdlog"] = "Basalt/vendor/spdlog/include"
IncludeDir["glm"] = "Basalt/vendor/glm"
IncludeDir["ImGui"] = "Basalt/vendor/imgui"

include "Basalt/vendor/imgui"

project "Basalt"
	location "Basalt"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir("bin/" .. outputDir .. "/%{prj.name}")
	objdir("bin-int/" .. outputDir .. "/%{prj.name}")

	pchheader "BEpch.h"
	pchsource "Basalt/src/BEpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.tpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"%{prj.name}/src/**.hlsl"
	}

	defines
	{	
		"_CRT_SECURE_NO_WARNINGS",
		"BE_STATIC_LIB",
		"MAJOR_VERSION=%{os.getversion().majorversion}",
		"MINOR_VERSION=%{os.getversion().minorversion}"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"ImGui"
	}

	filter {"files:**-p.hlsl"}
		shadertype "Pixel"
		shadermodel "4.0"

	filter {"files:**-v.hlsl"}
		shadertype "Vertex"
		shadermodel "4.0"

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"BE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "BE_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "BE_RELEASE"
		runtime "Release"
		optimize "on"
		
	filter "configurations:Dist"
		defines "BE_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "WindowedApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir("bin/" .. outputDir .. "/%{prj.name}")
	objdir("bin-int/" .. outputDir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.hlsl"
	}

	includedirs
	{
		"%{IncludeDir.spdlog}",
		"Basalt/src",
		"%{IncludeDir.glm}",
		"Basalt/vendor"
	}

	links
	{
		"Basalt"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"BE_PLATFORM_WINDOWS"
		}

		links
		{
			"d3d11",
			"D3DCompiler",
			"dxgi"
		}

		filter "configurations:Debug"

			links
			{
				"dxguid"
			}

	filter "configurations:Debug"
		defines "BE_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "BE_RELEASE"
		runtime "Release"
		optimize "on"
		
	filter "configurations:Dist"
		defines "BE_DIST"
		runtime "Release"
		optimize "on"