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

project "Basalt"
	location "Basalt"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir("bin/" .. outputDir .. "/%{prj.name}")
	objdir("bin-int/" .. outputDir .. "/%{prj.name}")

	pchheader "BEpch.h"
	pchsource "Basalt/src/BEpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.glm}"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"BE_PLATFORM_WINDOWS",
			"BE_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputDir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "BE_DEBUG"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		defines "BE_RELEASE"
		runtime "Release"
		optimize "On"
		
	filter "configurations:Dist"
		defines "BE_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "WindowedApp"
	language "C++"
	staticruntime "off"

	targetdir("bin/" .. outputDir .. "/%{prj.name}")
	objdir("bin-int/" .. outputDir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{IncludeDir.spdlog}",
		"Basalt/src",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Basalt"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"BE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "BE_DEBUG"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		defines "BE_RELEASE"
		runtime "Release"
		optimize "On"
		
	filter "configurations:Dist"
		defines "BE_DIST"
		runtime "Release"
		optimize "On"