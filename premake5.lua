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
Libraries["SFML"] = "%{GameName}/Library/SFML"
Libraries["glad"] = "%{GameName}/Library/glad"

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
		"%{prj.name}/Source/**.cpp"
	}

	includedirs {
		"%{prj.name}/Source",
		"%{Libraries.glad}",
		"%{Libraries.SFML}/include",
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS",
		"SFML_STATIC"
	}

	filter {"platforms:Win64", "configurations:Debug"}
		libdirs {
			"%{Libraries.SFML}/lib"
	    }

    postbuildcommands {
        ("{COPY} %{prj.location}Library/SFML/bin/openal32.dll %{wks.location}Binaries/"..OutputDir.. "/%{GameName}")
    }


	filter "configurations:Debug"
		defines "DEBUG"
		buildoptions "/MDd"
		runtime "Debug"
		symbols "on"

		links {
			"glad",
			"opengl32.lib",
            "freetype.lib",
            "winmm.lib",
            "gdi32.lib",
            "openal32.lib",
            "flac.lib",
            "vorbisenc.lib",
            "vorbisfile.lib",
            "vorbis.lib",
            "ogg.lib",
            "sfml-audio-s-d.lib",
            "sfml-graphics-s-d.lib",
            "sfml-window-s-d.lib",
            "sfml-system-s-d.lib"
		}

	filter "configurations:Release"
		defines "NDEBUG"
		buildoptions "/MD"
		runtime "Release"
		optimize "on"

		links {
			"glad",
			"opengl32.lib",
            "freetype.lib",
            "winmm.lib",
            "gdi32.lib",
            "openal32.lib",
            "flac.lib",
            "vorbisenc.lib",
            "vorbisfile.lib",
            "vorbis.lib",
            "ogg.lib",
            "sfml-audio-s.lib",
            "sfml-graphics-s.lib",
            "sfml-window-s.lib",
            "sfml-system-s.lib"
		}