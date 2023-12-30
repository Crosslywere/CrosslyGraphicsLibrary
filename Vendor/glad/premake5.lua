project "glad"
kind "StaticLib"
language "C"

targetdir "bin/%{cfg.buildcfg}"
objdir "obj/%{cfg.buildcfg}"

files {
    "src/glad.c"
}
includedirs {
    "include"
}