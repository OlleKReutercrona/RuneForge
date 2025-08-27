print("Starting premake process")
include "common.lua"

-- a little bit janky but gets to job done
local includeTests = false

-- loops through the arguments and checks for matches
    for i, arg in ipairs(_ARGS) do
        if(arg == "tests") then
            includeTests = true
        end
    end

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

    
if(includeTests) then
    FetchGoogleTest()
    
    print("\nIncluding tests\n")
    include(directories.editorTest)
    include(directories.coreTest)
end
    
include(directories.project)

print("\nBuild complete, happy developing!\n")