GameName = "App"

workspace (GameName)
	configurations {
		"Debug",
		"Release"
	}

	platforms {
		"Win64"
	}

	system "windows"
	systemversion "latest"
	architecture "x64"

	flags {
		"MultiProcessorCompile"
	}

OutputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Libraries --
Libraries = {}

project (GameName)
	location (GameName)
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++latest"
	staticruntime "on"

	targetdir ("bin/"..OutputDir.."/%{prj.name}")
	objdir ("bin-int/"..OutputDir.."/%{prj.name}")

	pchheader "pch.h"
	pchsource "%{prj.name}/Source/pch.cpp"

	files {
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp"
	}

	includedirs {
		"%{prj.name}/Source",
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS",
	}

	filter "configurations:Debug"
		defines "DEBUG"
		buildoptions "/MTd"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "NDEBUG"
		buildoptions "/MT"
		runtime "Release"
		optimize "on"