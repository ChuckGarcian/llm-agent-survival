
baseName = path.getbasename(os.getcwd());
print (os.getcwd())

folders = os.matchdirs("*")

for _, folderName in ipairs(folders) do
	if (string.starts(folderName, ".") == false) then
			print(folderName)  
			-- Get the example name from the directory path
			print (path.join (os.getcwd(), folderName))
			local exampleName = path.getname(folderName)

			-- Now you can use folderName and exampleName in your project configuration
			project(exampleName)
					kind "ConsoleApp"
					location "../_build"
					targetdir "../_bin/%{cfg.buildcfg}"
					targetname ("sim-exe")
					files { path.join(folderName, "**.c"), path.join(folderName, "**.cpp"), path.join(folderName, "**.h"), path.join(folderName, "**.hpp") }
					files {path.join ("../src", "**.c"), path.join ("../src", "**.h")}
					includedirs { path.join (os.getcwd(), folderName) , "./", "src", "include" }
					link_raylib()
		-- files { folderName .. "/**.c", folderName .. "/**.cpp", folderName .. "/**.h", folderName .. "/**.hpp" }
	end
end


-- local example_to_compile = _ARGS[1]

-- project (workspaceName)
--   	kind "ConsoleApp"
--     location "../_build"
--     targetdir "../_bin/%{cfg.buildcfg}"
	
--     filter "configurations:Release"
-- 		kind "WindowedApp"
-- 		entrypoint "mainCRTStartup"

-- 	filter "action:vs*"
--         debugdir "$(SolutionDir)"
		
-- 	filter {"action:vs*", "configurations:Release"}
-- 			kind "WindowedApp"
-- 			entrypoint "mainCRTStartup"
-- 	filter {}
	

	-- Get a table of all directories in the current directory
	-- local dirs = os.matchdirs("*")
	-- files {"**.c", "**.cpp", "**.h", "**.hpp"}
	-- -- -- Iterate over each directory
	-- -- for _, dir in ipairs(dirs) do
	-- -- 	if (string.starts(dir, ".") == false) then
	-- -- 		-- Include the files in the directory
	-- -- 		files { dir .. "/**.c", dir .. "/**.cpp", dir .. "/**.h", dir .. "/**.hpp" }
	-- -- 	end
	-- -- end

	-- includedirs { "/home/chuckg/Projects/llm-agent-survival/examples/agent-priority-walk" }
	-- includedirs { "src" }
	-- includedirs { "include" }

	-- link_raylib()
		
	-- To link to a lib use link_to("LIB_FOLDER_NAME")
	