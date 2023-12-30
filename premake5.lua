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
    }
}

filter "configurations:Debug"
    optimize "off"
    symbols "on"
    runtime "Debug"

filter "configurations:Release"
    optimize "on"
    runtime "Release"

workspace "CrosslyGL"
architecture "x64"
configurations {
    "Debug",
    "Release"
}
startproject "Sandbox"

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
        "%{prj.location}/include"
    }

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    targetdir "Bin/%{cfg.buildcfg}"
    files {
        "%{prj.location}/src/**.hpp",
        "%{prj.location}/src/**.cpp"
    }
    includedirs {
        "CrosslyGL/include"
    }
    links "CrosslyGL"