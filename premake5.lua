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
Libraries["ImGui"] = "%{GameName}/Library/ImGui"

include "App/Library/glad"

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

		"%{Libraries.ImGui}/imgui.cpp",
		"%{Libraries.ImGui}/imgui_draw.cpp",
		"%{Libraries.ImGui}/imgui_tables.cpp",
		"%{Libraries.ImGui}/imgui_widgets.cpp",

	}

	includedirs {
		"%{prj.name}/Source",
		"%{Libraries.glad}",
		"%{Libraries.SFML}/include",
		"%{Libraries.ImGui}",
	}

	filter "files:App/Library/ImGui/**.cpp"
        flags {"NoPCH"}

	defines {
		"_CRT_SECURE_NO_WARNINGS",
	}

	filter "configurations:Debug"
		defines "DEBUG"
		buildoptions "/MTd"
		runtime "Debug"
		symbols "on"

		links {
			"glad",
		}

	filter "configurations:Release"
		defines "NDEBUG"
		buildoptions "/MT"
		runtime "Release"
		optimize "on"

		links {
			"glad",
		}