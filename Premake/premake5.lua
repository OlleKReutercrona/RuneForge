print("Starting premake process")
include "common.lua"

workspace(WORKSPACE_NAME)
    location(directories.root)
    startproject(PROJECT_NAME)
    architecture("x64")

    configurations {
        DEBUG_BUILD_NAME,
        RELEASE_BUILD_NAME
    }

print("Setting up folder structure")

MakeFolderStructure()

print("Including other directories")

include(directories.external)
include(directories.editor)
include(directories.core)

for i, arg in ipairs(_ARGS) do
    if(arg == "tests") then
        print("\nIncluding tests\n")
        include(directories.editorTest)
        include(directories.coreTest)
    end
end

include(directories.project)

print("\nBuild complete, happy developing!\n")