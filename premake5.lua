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

-- include "App/Library/glad"
include "App/Library/glfw"

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
		--"%{Libraries.glad}",
		"%{Libraries.glfw}/include",
	}

	libdirs {
		"%{Libraries.glfw}/lib",
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS",

	}

	filter "configurations:Debug"
		defines "DEBUG"
		buildoptions "/MTd"
		runtime "Debug"
		symbols "on"

		links {
			-- "glad",
			"GLFW",
			"opengl32.lib",
			"gdi32.lib",
			"user32.lib",
			"shell32.lib"
		}

	filter "configurations:Release"
		defines "NDEBUG"
		buildoptions "/MT"
		runtime "Release"
		optimize "on"

		links {
			-- "glad",
			"glfw3.lib"
		}