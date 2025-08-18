function FetchGoogleTest() 
    local gtestPath = directories.externalInclude.."gtest/"

    if not os.isdir(gtestPath) then
        print("\nCloning GoogleTest into " .. gtestPath .. " ...")
        os.execute("git clone --depth 1 https://github.com/google/googletest.git " .. gtestPath)
    else
        print("\nUpdating GoogleTest in " .. gtestPath .. " ...")
        os.execute("cd " .. gtestPath .. " && git pull")
    end
end
