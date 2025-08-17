include "../../Premake/common.lua"
print("Setting up editor")

project(EDITOR_NAME)
    location(directories.editor)
    language "C++"
    cppdialect(cppVersion)
    dependson{ CORE_NAME, EXTERNAL_NAME }

    links(LIBRARY_LIST)

    kind("StaticLib")

    pchheader("stdafx.h")
    pchsource("stdafx.cpp")

    shaderincludedirs(directories.coreShaders)

    targetdir(directories.intermediateLib)
    debugdir(directories.intermediateLib)
    objdir(directories.temp.."/"..EDITOR_NAME.."/%{cfg.buildcfg}")
    targetname(EDITOR_NAME.."/%{cfg.buildcfg}")

    files {
        directories.editor.."**.h",
        directories.editor.."**.cpp",

        directories.editorPch.."**",

        directories.editor.."**.hlsl",
        directories.editor.."**.hlsli",
    }

    includedirs {
        directories.externalInclude,
        directories.core,

        directories.editor,
        directories.editorPch,
    }

    libdirs {
        directories.externalLib,
        directories.intermediateLib
    }

    filter(CONFIG_FILTERS.DEBUG)
        defines(DEBUG_DEFINES)
        runtime "Debug"
        symbols "on"
        libdirs{directories.debugLib}

    filter(CONFIG_FILTERS.RELEASE)
        defines(RELEASE_DEFINES)
        runtime "Release"
        optimize "on"
        libdirs{directories.releaseLib}

    filter "system:windows"
        staticruntime "off"
        symbols "on"
        systemversion "latest"
        warnings "Extra"

        flags {
            "MultiProcessorCompile"
        }

        defines{
            "WIN32"
        }

        links{
            "DXGI"
        }