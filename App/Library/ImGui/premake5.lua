project "ImGui"
	kind "StaticLib"
	language "C++"

	targetdir ("Binaries/" .. OutputDir .. "/%{prj.name}")
	objdir ("Intermediates/" .. OutputDir .. "/%{prj.name}")

	files {
		"include/ImGui/imconfig.h",
		"include/ImGui/imgui.h",
		"include/ImGui/imgui_internal.h",
		"include/ImGui/imstb_rectpack.h",
		"include/ImGui/imstb_textedit.h",
		"include/ImGui/imstb_truetype.h",
		"include/ImGui/imgui_impl_glfw.h",
		"include/ImGui/imgui_impl_opengl3.h",

		"src/imgui.cpp",
		"src/imgui_demo.cpp",
		"src/imgui_draw.cpp",
		"src/imgui_widgets.cpp",
		"src/imgui_tables.cpp",
		"src/imgui_impl_glfw.cpp",
		"src/imgui_impl_opengl3.cpp",
	}

	includedirs {
		"include/ImGui",
        "../glfw/include",
        "../glad",
	}

	filter "system:windows"
		systemversion "latest"
		cppdialect "C++latest"
		staticruntime "On"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
