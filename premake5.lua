-- EPICTracer
workspace "EpicTracer"
	architecture "x64"
	startproject "EpicTracer"

	configurations{
		"Debug",
		"Release"
	}

	configuration { "vs*",  "release" }
		buildoptions { "/openmp" }
	configuration { "gmake",  "release" }
		buildoptions { "-fopenmp" }		
		links { "gomp" }
	flags{
		"MultiProcessorCompile"
	}

include "EpicTracer"


