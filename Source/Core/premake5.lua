include "../../Premake/common.lua"
print("Setting up core")

project(CORE_NAME)
    location(directories.core)
    language("C++")
    cppdialect(cppVersion)
    kind("StaticLib")

    debugdir(directories.intermediateLib)
    targetdir(directories.intermediateLib)
    targetname(CORE_NAME.."_%{cfg.buildcfg}")
    objdir(directories.temp.."/"..CORE_NAME.."/%{cfg.buildcfg}")

    pchheader(directories.corePch.."stdafx.h")
    pchsource(directories.corePch.."stdafx.cpp")

    files {
        directories.core.."**.h",
        directories.core.."**.cpp",
        
        directories.corePch.."**",

        directories.core.."**hlsl",
        directories.core.."**hlsli"
    }

    includedirs {
        directories.externalInclude,
        directories.coreSource,
    }

    filter(CONFIG_FILTERS.DEBUG)
        defines {"_DEBUG"}
        runtime "Debug"
        symbols "on"

    filter(CONFIG_FILTERS.RELEASE)
        defines {"_RELEASE"}
        runtime "Release"
        optimize "on"

    filter "system:windows"
        staticruntime "off"
        symbols "on"
        systemversion "latest"
        warnings "Extra"

        flags {
            --"FatalCompileWarnings",
			"MultiProcessorCompile"
        }
        
        fatalwarnings {
            "All"
        }

    links {
        "DXGI",
        "d3dcompiler",
    }

    shadermodel("5.0")
    filter("files:**hlsl")
        flags("ExcludeFromBuild")
        shaderobjectfileoutput(directories.shaders.."%{file.basename}"..".cso")

    filter("files:**PS.hlsl")
        removeflags("ExcludeFromBuild")
        shadertype("Pixel")

    filter("files:**VS.hlsl")
        removeflags("ExcludeFromBuild")
        shadertype("Vertex")

    filter("files:**CS.hlsl")
        removeflags("ExcludeFromBuild")
        shadertype("Compute")

    -- Warnings as errors
	shaderoptions({"/WX"})