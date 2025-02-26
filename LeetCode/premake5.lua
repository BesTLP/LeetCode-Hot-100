workspace "LeetCode"
	architecture "x64"
	startproject "LeetCode"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
	-- include directories relative to root folder(solution directory)
	IncludeDir = {}

project "LeetCode"
	location "LeetCode"
	kind "ConsoleApp"
	language "C++"

		targetdir("bin/" .. outputdir .. "/%{prj.name}")
		objdir("bin-int/" .. outputdir .. "/%{prj.name}")

		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"

		}
		filter "system:windows"
			cppdialect "C++17"
			systemversion "latest"

			defines
			{
			}

			buildoptions "/utf-8"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		runtime "Release"
		optimize "On"