-- COMMON VARIABLES --
WORKSPACE_NAME = "RuneForge"

PROJECT_NAME = "RuneForge"
CORE_NAME = WORKSPACE_NAME .. " Core"
EDITOR_NAME = WORKSPACE_NAME .. " Editor"
EXTERNAL_NAME = "External"

cppVersion = "C++20"

DEBUG_BUILD_NAME = "Debug"
RELEASE_BUILD_NAME = "Release"

CONFIG_FILTERS = {
    DEBUG = "configurations:"..tostring(DEBUG_BUILD_NAME),
    RELEASE = "configurations:"..tostring(RELEASE_BUILD_NAME),
}

DEBUG_DEFINES = {
    "_DEBUG"
}

RELEASE_DEFINES = {
    "_RELEASE"
}
-- DIRECTORIES --

local basePath = os.realpath("..\\")
local sourcePath = basePath.."Source\\"

directories = {
    root            = basePath,
    bin             = basePath .. "Bin\\",
    temp            = basePath .. "Temp\\",
    shaders         = basePath .. "Bin\\Shaders\\",

    intermediateLib = basePath .. "Temp\\IntermediateLib",

    -- Project, maybe remove if editor can create new projects
    project         = sourcePath .. "Project\\",
    projectPch      = sourcePath .. "Project\\pch\\",

    -- Core
    core            = sourcePath .. "Core\\",
    coreGraphics    = sourcePath .. "Core\\Graphics\\",
    coreShaders     = sourcePath .. "Core\\Graphics\\Shaders\\",
    coreEngine      = sourcePath .. "Core\\Engine\\",
    corePch         = sourcePath .. "Core\\pch\\",

    coreTest        = sourcePath .. "CoreTests\\",

    -- Editor
    editor          = sourcePath .. "Editor\\",
    editorPch       = sourcePath .. "Editor\\pch\\",

    editorTest      = sourcePath .. "EditorTests\\",

    -- External
    external        = sourcePath .. "External\\",
    externalDLL     = sourcePath .. "External\\dll\\",
    externalInclude = sourcePath .. "External\\Include\\",
    externalLib     = sourcePath .. "External\\Lib\\",
    debugLib        = sourcePath .. "External\\Lib\\Debug\\",
    releaseLib      = sourcePath .. "External\\Lib\\Release\\",


    premake         = basePath .. "Premake",
 }

 externalDirectories = {
    -- gtest
    gtestInclude    = sourcePath .. "External\\Include\\googleTest\\googletest\\include\\",
    gtestSrc        = sourcePath .. "External\\Include\\googleTest\\googletest\\",

 }

function MakeFolderStructure()
    for _, dir in pairs(directories) do
        if not os.isdir(dir) then
            os.mkdir(dir)
        end
    end
end

local function FindLibraries()
    print("\nFinding Libraries to link:")

    local foundNames = {}
    local out = {}
    for _, lib in pairs(os.matchfiles(directories.externalLib.."**")) do        
        if (path.getextension(lib) == ".lib") then
            local name = path.getname(lib)
            if not foundNames[name] then
                out[#out+1] = path.getname(lib)
                foundNames[name] = true
                print(name)
            end
        end
    end
    
    print("\n")

    return out
end

LIBRARY_LIST = FindLibraries()
