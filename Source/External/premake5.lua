include "../../Premake/common.lua"
print("Setting up external")

project(EXTERNAL_NAME)
    location(directories.temp)
    language("C++")
    cppdialect(cppVersion)

    targetdir(directories.intermediateLib)
    targetname(EXTERNAL_NAME.."_%{cfg.buildcfg}")
    objdir(directories.temp..EXTERNAL_NAME.."/%{cfg.buildcfg}")

    files {
		"**.h",
		"**.hpp",
		"**.inl",
		"**.c",
		"**.cpp",
	}

    includedirs {
        directories.externalInclude,
        directories.root,
    }

    libdirs { directories.intermediateLib }

    filter(CONFIG_FILTERS.DEBUG)
        defines { DEBUG_DEFINES }
        runtime "Debug"
        symbols "on"

    filter(CONFIG_FILTERS.RELEASE)
        defines {RELEASE_DEFINES }
        runtime "Release"
        optimize "on"

    filter "system:windows"
        kind "StaticLib"
        staticruntime "off"
        symbols "On"
        systemversion "latest"

        flags {
            "MultiProcessorCompile",
        }

        links {
            "DXGI",
            "dxguid",
        }