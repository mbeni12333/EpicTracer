-- EPICTracer
workspace "EpicTracer"
	architecture "x64"
	startproject "EpicTracer"

	configurations{
		"Debug",
		"Release"
	}
	
	flags{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


project "EpicTracer"
   kind "ConsoleApp"
   language "C++"
   targetdir "bin/%{outputdir}"

   files { "**.h", "**.cpp" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"

