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
Libraries["glad"] = "%{GameName}/Library/glad"
Libraries["glfw"] = "%{GameName}/Library/glfw"
Libraries["glm"] = "%{GameName}/Library/glm"
Libraries["ImGui"] = "%{GameName}/Library/ImGui"

include "App/Library/glad"
include "App/Library/glfw"
include "App/Library/ImGui"

project (GameName)
	location (GameName)
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++latest"
	staticruntime "on"

	targetdir ("Binaries/"..OutputDir.."/%{prj.name}")
	objdir ("Intermediates/"..OutputDir.."/%{prj.name}")

	pchheader "pch.h"
	pchsource "%{prj.name}/Source/pch.cpp"

	files {
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp",
	}

	includedirs {
		"%{prj.name}/Source",
		"%{Libraries.glad}",
		"%{Libraries.glfw}/include",
		"%{Libraries.glm}",
		"%{Libraries.ImGui}/include",
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	filter "configurations:Debug"
		defines "DEBUG"
		buildoptions "/MTd"
		runtime "Debug"
		symbols "on"

		links {
			"glad",
			"GLFW",
			"ImGui"
		}

	filter "configurations:Release"
		defines "NDEBUG"
		buildoptions "/MT"
		runtime "Release"
		optimize "on"

		links {
			"glad",
			"GLFW",
			"ImGui"
		}