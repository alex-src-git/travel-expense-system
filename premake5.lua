TARGET_DIR = "%{prj.location}/bin/%{cfg.system}/%{cfg.buildcfg}"
OBJECT_DIR = TARGET_DIR .. "/obj"

workspace "travel-expense-system"
    architecture "x64"
    configurations { "debug", "release" }


project "travel-expense-system"
    location "travel-expense-system"
    systemversion "latest"
    cppdialect "C++latest"
    staticruntime "Off"
    kind "ConsoleApp"
    targetdir (TARGET_DIR)
    objdir (OBJECT_DIR)
    files
    {
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp",
    }
