include "../../Premake/common.lua"
print("Setting up Editor Tests")

local NAME = EDITOR_NAME.." Tests"

project(NAME)
    location(directories.temp)
    language("C++")
    cppdialect(cppVersion)
    kind("ConsoleApp")

    dependson{ CORE_NAME, EXTERNAL_NAME }

    debugdir(directories.bin)
    targetdir(directories.bin)
    targetname(NAME.."_%{cfg.buildcfg}")
    objdir(directories.temp.."/"..NAME.."/%{cfg.buildcfg}")

    files {
        directories.editorTest.."**.h",
        directories.editorTest.."**.cpp",
        directories.gtestSrc.."src\\gtest_main.cc",
        directories.gtestSrc.."src\\gtest-all.cc",
    }

    includedirs {
        directories.externalInclude,
        directories.core,

        directories.gtestInclude,
        directories.gtestSrc,

        directories.editor,
        directories.editorTest,
    }

    libdirs {
        directories.externalLib,
        directories.intermediateLib,
    }

    filter(CONFIG_FILTERS.DEBUG)
        defines {"_DEBUG"}
        runtime "Debug"
        symbols "on"
        libdirs {directories.debugLib}

    filter(CONFIG_FILTERS.RELEASE)
        defines {"_RELEASE"}
        runtime "Release"
        optimize "on"
        libdirs {directories.releaseLib}

    filter "system:windows"
        staticruntime "off"
        symbols "on"
        systemversion "latest"
        warnings "Extra"

        flags {
			"MultiProcessorCompile"
        }
        
        fatalwarnings {
            "All"
        }

    links {
        "DXGI",
        "d3dcompiler",
    }