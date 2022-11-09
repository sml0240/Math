workspace "Math"
    architecture "x86_64"
    configurations {"Debug", "Release"}
    
    filter { "configurations:Debug" }
        symbols "On"

    filter { "configurations:Release" }
        optimize "On"

    flags
	{
		"MultiProcessorCompile"
	}

    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Tests"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"

    files
    {
        "tests/**.h",
        "tests/**.cpp",
    }

    includedirs
    {
        "include",
    }
    
    filter { "system:linux", "action:gmake2" }
        linkoptions { "-fsanitize=leak", "-Wall" }

    links { "g" }
    
    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("obj/" .. outputdir .. "/%{prj.name}")