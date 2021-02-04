outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


project "EpicTracer"
   kind "ConsoleApp"
   language "C++"
   targetdir "../bin/%{outputdir}"
   objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

   files { "src/**.h", "src/**.cpp" }

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"


   filter "system:windows"
      systemversion "latest"

