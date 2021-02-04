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

include "EpicTracer"


