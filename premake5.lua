if (os.target ~= nil and os.target("windows")) then
    systemversion "latest"
end

vpaths {
    ["Source Files"] = {
        "**.c",
        "**.cpp"
    },
    ["Header Files"] = {
        "**.h",
        "**.hpp"
    },
    ["Resource Files"] = {
        "**.vert",
        "**.frag"
    }
}

IncludeDirs = {}
IncludeDirs["glfw"] = "Vendor/glfw/include"
IncludeDirs["glad"] = "Vendor/glad/include"
IncludeDirs["glm"] = "Vendor/glm"

filter "configurations:Debug"
    defines "_DEBUG"
    optimize "off"
    symbols "on"
    runtime "Debug"

filter "configurations:Release"
    defines "NDEBUG"    
    optimize "on"
    runtime "Release"

filter "system:windows"
    cppdialect "C++17"
    cdialect "C17"

workspace "CrosslyGL"
architecture "x64"
configurations {
    "Debug",
    "Release"
}
startproject "Sandbox"

include "Vendor/glfw"
include "Vendor/glad"

project "CrosslyGL"
    location "CrosslyGL"
    kind "StaticLib"
    language "C++"
    targetdir "Lib/%{cfg.buildcfg}"
    files {
        "%{prj.location}/include/**.hpp",
        "%{prj.location}/src/**.hpp",
        "%{prj.location}/src/**.cpp"
    }
    includedirs {
        "%{prj.location}/include",
        "%{IncludeDirs.glfw}",
        "%{IncludeDirs.glad}"
    }
    links {
        "glfw",
        "glad"
    }

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    targetdir "Bin/%{cfg.buildcfg}"
    files {
        "%{prj.location}/src/**.hpp",
        "%{prj.location}/src/**.cpp",
        "%{prj.location}/res/**.vert",
        "%{prj.location}/res/**.frag"
    }
    includedirs {
        "CrosslyGL/include",
        "%{IncludeDirs.glfw}",
        "%{IncludeDirs.glad}",
        "%{IncludeDirs.glm}"
    }
    links "CrosslyGL"
    postbuildcommands { "{COPYDIR} res %{cfg.buildtarget.directory}/res" }