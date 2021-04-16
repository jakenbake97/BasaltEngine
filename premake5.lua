workspace "BasaltEngine"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Basalt"
	location "Basalt"
	kind "SharedLib"
	language "C++"

	targetdir("bin/" .. outputDir .. "/%{prj.name}")
	objdir("bin-int/" .. outputDir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"BE_PLATFORM_WINDOWS",
			"BE_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputDir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "BE_DEBUG"
		symbols "On"
		buildoptions "/MDd"
		
	filter "configurations:Release"
		defines "BE_RELEASE"
		optimize "On"
		
	filter "configurations:Dist"
		defines "BE_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "WindowedApp"
	language "C++"

	targetdir("bin/" .. outputDir .. "/%{prj.name}")
	objdir("bin-int/" .. outputDir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"Basalt/vendor/spdlog/include",
		"Basalt/src"
	}

	links
	{
		"Basalt"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"BE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "BE_DEBUG"
		symbols "On"
		buildoptions "/MDd"
		
	filter "configurations:Release"
		defines "BE_RELEASE"
		optimize "On"
		
	filter "configurations:Dist"
		defines "BE_DIST"
		optimize "On"