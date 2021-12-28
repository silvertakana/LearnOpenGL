ProjectName = "LearnOpenGL" 

workspace (ProjectName)
	configurations { "Debug", "Release" ,"Dist"}
	platforms { "x86", "x64" }
	
	filter "platforms:x86"
		architecture "x86"
		defines { "x86" }

		
	filter "platforms:x64"
		architecture "x86_64"
		defines { "x64" }

	filter "configurations:Debug"
		defines { "_DEBUG" }
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		defines { "_NDEBUG" }
		runtime "Release"
		optimize "On"
		
	filter "configurations:Dist"
		defines { "_NDEBUG","_DIST" }
		runtime "Release"
		optimize "On"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
project (ProjectName)
	location (ProjectName)
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		 "%{prj.name}/src/**.hpp", 
		 "%{prj.name}/src/**.h", 
		 "%{prj.name}/src/**.cpp", 
		 "%{prj.name}/src/**.c", 
		 "%{prj.name}/res/**.**"
	}
	includedirs {
		 "vendor/GLFW/include",
		"vendor/Glad/include",
		"vendor/stb/include",
		"vendor/glm/include",
	}
	links{
		 "vendor/GLFW/bin/glfw3.lib",
		 "opengl32.lib"
	}
	vpaths {
		["Headers"] = { "**.h", "**.hpp" },
		["Sources"] = {"**.c", "**.cpp"},
		["Images"] = {"**.png","**.jpg","**.bmp","**.ppm","**.pgm","**.pbm","**.tga","**.gif","**.ico","**.icns","**.cur","**.xbm","**.xpm"},
		["Shaders"] = {"**.shader","**.frag","**.vert","**.glsl","**.hlsl"},
		["Docs"] = {"**.md","ReadMe.**","readme.**","Readme.**","readMe.**"}
	}
	systemversion "latest"
	filter "system:windows"
		postbuildcommands
		{
			"{COPY} res/ ../bin/" .. outputdir .. "/%{prj.name}/res/",
		}
		defines { "WIN32", "_WINDOWS" }

	filter "system:linux"
		defines { "LINUX" }

	filter "system:macosx"
		defines { "MACOSX" }