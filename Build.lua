workspace "Light-OpenGL"
   
   -- Konfiguracje: Debug, Release
   configurations { "Debug", "Release" }
   platforms { "x64"}

   -- Projekt
project "Light-OpenGL"
   
   -- Rodzaj projektu: aplikacja konsolowa
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   
   -- Ścieżka wyjściowa: Build/<configuration>
   targetdir "Build/%{cfg.buildcfg}"
   objdir "Build/obj/%{cfg.buildcfg}"
   location "Light-OpenGL"
   
   -- Pliki źródłowe (wszystkie pliki .cpp i .h w folderze src)
   files {
   "Light-OpenGL/src/**.cpp", 
   "Light-OpenGL/src/**.h" ,
   "Light-OpenGL/src/**.shader",
   "Light-OpenGL/Resources/Shaders/**.shader",
   
   "Light-OpenGL/vendor/ImGui/*.cpp",
   "Light-OpenGL/vendor/ImGui/*.h",

   "Light-OpenGL/vendor/stb_image/*.cpp",
   "Light-OpenGL/vendor/stb_image/*.h"
   }

   -- Zewnętrzne zależności
   defines {"GLEW_STATIC"}
   includedirs {
   "Light-OpenGL/vendor",
   "Dependencies/glm"
   }

   filter "system:windows or system:macos"
   includedirs {
      "$(SolutionDir)Dependencies/GLFW/include",  
      "$(SolutionDir)Dependencies/GLEW/include"
   }
   
   -- Ustawienia dla systemu Windows
   filter "system:windows"
      defines { "PLATFORM_WINDOWS" }
      libdirs { 
         "$(SolutionDir)Dependencies/GLFW/lib-vc2022",
         "$(SolutionDir)Dependencies/GLEW/lib/Release/x64"
      }  
      links { 
      "opengl32",
      "glfw3",
      "glew32s",
      "User32",
      "Gdi32",
      "Shell32"
      }

   -- Ustawienia dla systemu Linux
   filter "system:linux"
      defines { "PLATFORM_LINUX" }
      links { "GL", "glfw", "GLEW"}
      buildoptions { "-fPIC" }  -- Opcja przydatna przy pracy z bibliotekami współdzielonymi

   
   
      -- Ustawienia dla konfiguracji Debug
   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"  -- Włączamy symbole debugowania
   
   -- Ustawienia dla konfiguracji Release
   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"  -- Optymalizacja
