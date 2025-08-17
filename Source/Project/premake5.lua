include "../../Premake/common.lua"
print("Setting up Project")

project(PROJECT_NAME)
    location(directories.temp)
    language("C++")
    cppdialect(cppVersion)
    kind("WindowedApp")

    debugdir(directories.bin)
    targetdir(directories.bin)
    targetname(PROJECT_NAME.."_%{cfg.buildcfg}")
    objdir(directories.temp.."/"..PROJECT_NAME.."/%{cfg.buildcfg}")

    pchheader(directories.projectPch.."stdafx.h")
    pchsource(directories.projectPch.."stdafx.cpp")

    files {
        directories.project.."**.h",
        directories.project.."**.cpp",

        directories.projectPch.."**"
    }

    includedirs {
        directories.externalInclude,
        directories.coreSource,
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