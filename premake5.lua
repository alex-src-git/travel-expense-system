TARGET_DIR = "%{prj.location}/bin/%{cfg.system}/%{cfg.buildcfg}"
OBJECT_DIR = TARGET_DIR .. "/obj"

workspace "travel-expense-system"
    architecture "x64"
    configurations { "debug", "release" }
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
        "%{prj.name}/thirdparty/**.hpp"
    }

project "travel-expense-system"
    location "travel-expense-system"
    
project "tests"
    location "tests"
    includedirs
    {
        "travel-expense-system/src",
        "%{prj.name}/thirdparty"
    }   
    libdirs
    {
        "travel-expense-system/bin/%{cfg.system}/%{cfg.buildcfg}/obj"
    }
    links
    {
        -- .obj files that we want to test.
        "receipt.obj",
        "receipt-config.obj",
        "receipt-reader-csv.obj"
    }
