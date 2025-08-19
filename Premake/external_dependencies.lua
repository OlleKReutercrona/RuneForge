function FetchGoogleTest() 
    local gtestPath = directories.externalInclude.."gtest\\"
    local gitFolderPath = gtestPath..".git\\"

    if os.isdir(gtestPath) and os.isdir(gitFolderPath) then
        print("\nUpdating GoogleTest in " .. gtestPath .. " ...")
        os.execute("cd " .. gtestPath .. " && git pull")
        return
    else if(os.isdir(gtestPath)) then
        print("\ngtest dir exist but is empty, removing...["..gtestPath.."]")
        os.rmdir(gtestPath)
    end
    
    print("\nCloning GoogleTest into " .. gtestPath .. " ...")
    os.execute("git clone --depth 1 https://github.com/google/googletest.git " .. gtestPath)
end
end