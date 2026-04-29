include "../../Premake/common.lua"
print("Setting up Core Tests")

local NAME = CORE_NAME.." Tests"

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
        directories.coreTest.."**.h",
        directories.coreTest.."**.cpp",
        externalDirectories.gtestSrc.."src\\gtest_main.cc",
        externalDirectories.gtestSrc.."src\\gtest-all.cc",
    }

    includedirs {
        directories.externalInclude,
        directories.core,

        externalDirectories.gtestInclude,
        externalDirectories.gtestSrc,

        directories.coreTest,
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
		
		disablewarnings {
            "4723" -- division by zero
        }
        
        fatalwarnings {
            "All"
        }
		

    links {
        "DXGI",
        "d3dcompiler",
    }