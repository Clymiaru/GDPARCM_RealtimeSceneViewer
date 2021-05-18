project "GLAD"
    kind "StaticLib"
    language "C"
    staticruntime "on"
    
    targetdir ("Binaries/" .. OutputDir .. "/%{prj.name}")
    objdir ("Intermediates/" .. OutputDir .. "/%{prj.name}")

    files
    {
        "glad.h",
        "khrplatform.h",
        "glad.c"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"