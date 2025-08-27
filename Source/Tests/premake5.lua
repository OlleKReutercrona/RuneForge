include "../../Premake/common.lua"
print("Setting up Tests")

project(TESTS_NAME)
    location(directories.temp)
    language("C++")
    cppdialect(cppVersion)
    kind("")